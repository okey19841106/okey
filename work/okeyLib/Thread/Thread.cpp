#include "PreCom.h"
#include "Thread.h"
#ifdef WINDOWS
#include <process.h>
#else
	#include <sys/syscall.h>
	#include <sys/types.h>
	#include <linux/unistd.h>
#endif
#include <cassert>
#include "Exception.h"
#include "ThreadLocal.h"
#include <sstream>
#include "ErrorHandler.h"
#include "Runnable.h"


namespace okey
{
	Thread::CurrentThreadHolder Thread::_currentThreadHolder;
	Thread::Thread():	
#ifdef WINDOWS
		_pRunnableTarget(NULL),
		_thread(0),
		_threadId(0),
		_prio(PRIO_NORMAL),
		_stackSize(THREAD_STACK_SIZE),
#else
		_pData(new ThreadData)
#endif
		_id(uniqueId()), 
		_name(makeName()), 
		_pTLS(NULL)
	{

	}
	Thread::Thread(const std::string& name):
#ifdef WINDOWS
		_pRunnableTarget(NULL),
		_thread(0),
		_threadId(0),
		_prio(PRIO_NORMAL),
		_stackSize(THREAD_STACK_SIZE),
#else
		_pData(new ThreadData)
#endif
		_id(uniqueId()), 
		_name(name), 
		_pTLS(NULL)
	{

	}

	Thread::~Thread()
	{
		delete _pTLS;
		_pTLS = NULL;
#ifdef WINDOWS
		if (_thread) 
		{
			CloseHandle(_thread);
		}
#else
		if (IsRunning())
			pthread_detach(_pData->thread);
#endif
	}
	
	void Thread::SetPriority(Priority prio)
	{
#ifdef WINDOWS
		if (prio != _prio)
		{
			_prio = prio;
			if (_thread)
			{
				if (SetThreadPriority(_thread, _prio) == 0)
					throw SystemException("cannot set thread priority");
			}
		}
#else
		if (prio != _pData->prio)
		{
			_pData->prio = prio;
			_pData->policy = SCHED_OTHER;
			if (IsRunning())
			{
				struct sched_param par;
				par.sched_priority = mapPrio(_pData->prio, SCHED_OTHER);
				if (pthread_setschedparam(_pData->thread, SCHED_OTHER, &par))
					throw SystemException("cannot set thread priority");
			}
		}
#endif
	}



	void Thread::SetOSPriority(int prio, int policy)
	{
#ifdef WINDOWS
		SetPriority(Priority(prio));
#else
		if (prio != _pData->osPrio || policy != _pData->policy)
		{
			if (_pData->pRunnableTarget || _pData->pCallbackTarget)
			{
				struct sched_param par;
				par.sched_priority = prio;
				if (pthread_setschedparam(_pData->thread, policy, &par))
					throw SystemException("cannot set thread priority");
			}
			_pData->prio   = reverseMapPrio(prio, policy);
			_pData->osPrio = prio;
			_pData->policy = policy;
		}
#endif
	}


	int Thread::GetMinOSPriority(int policy)
	{
#ifdef WINDOWS
		return PRIO_LOWEST;
#else
		return sched_get_priority_min(policy);
#endif
	}

	int Thread::GetMaxOSPriority(int policy )
	{
#ifdef WINDOWS
		return PRIO_HIGHEST;
#else
		return sched_get_priority_max(policy);
#endif
	}

	void Thread::SetStackSize(int size)
	{
#ifdef WINDOWS
		_stackSize = size;
#else
		_pData->stackSize = size;
#endif
	}
	
	void Thread::Start(Runnable& target)
	{
#ifdef WINDOWS
		if (IsRunning())
			throw SystemException("thread already running");
		_pRunnableTarget = &target;
		unsigned threadId;
		_thread = (HANDLE)_beginthreadex(NULL, _stackSize, runnableEntry, this, 0, &threadId);
		_threadId = static_cast<DWORD>(threadId);
		if (!_thread)
			throw SystemException("cannot create thread");
		if (_prio != PRIO_NORMAL && !SetThreadPriority(_thread, _prio))
			throw SystemException("cannot set thread priority");
#else
		if (_pData->pRunnableTarget)
			throw SystemException("thread already running");
		pthread_attr_t attributes;
		pthread_attr_init(&attributes);

		if (_pData->stackSize != 0)
		{
			if (0 != pthread_attr_setstacksize(&attributes, _pData->stackSize))
			{
				pthread_attr_destroy(&attributes);	
				throw SystemException("cannot set thread stack size");
			}
		}
		_pData->pRunnableTarget = &target;
		if (pthread_create(&_pData->thread, &attributes, runnableEntry, this))
		{
			_pData->pRunnableTarget = 0;
			pthread_attr_destroy(&attributes);	
			throw SystemException("cannot start thread");
		}
		pthread_attr_destroy(&attributes);

		if (_pData->policy == SCHED_OTHER)
		{
			if (_pData->prio != PRIO_NORMAL_IMPL)
			{
				struct sched_param par;
				par.sched_priority = mapPrio(_pData->prio, SCHED_OTHER);
				if (pthread_setschedparam(_pData->thread, SCHED_OTHER, &par))
					throw SystemException("cannot set thread priority");
			}
		}
		else
		{
			struct sched_param par;
			par.sched_priority = _pData->osPrio;
			if (pthread_setschedparam(_pData->thread, _pData->policy, &par))
				throw SystemException("cannot set thread priority");
		}
#endif
	}

	void Thread::Start(Callable target, void* pData)
	{
#ifdef WINDOWS
		if (IsRunning())
			throw SystemException("thread already running");
		threadCleanup();
		_callbackTarget.callback = target;
		_callbackTarget.pData = pData;
		unsigned threadId;
		_thread = (HANDLE)_beginthreadex(NULL, _stackSize, callableEntry, this, 0, &threadId);
		_threadId = static_cast<DWORD>(threadId);
		if (!_thread)
			throw SystemException("cannot create thread");
		if (_prio != PRIO_NORMAL && !SetThreadPriority(_thread, _prio))
			throw SystemException("cannot set thread priority");
#else

		if (_pData->pCallbackTarget && _pData->pCallbackTarget->callback)
			throw SystemException("thread already running");

		pthread_attr_t attributes;
		pthread_attr_init(&attributes);

		if (_pData->stackSize != 0)
		{
			if (0 != pthread_attr_setstacksize(&attributes, _pData->stackSize))
				throw SystemException("can not set thread stack size");
		}

		if (0 == _pData->pCallbackTarget.get())
			_pData->pCallbackTarget = new CallbackData;

		_pData->pCallbackTarget->callback = target;
		_pData->pCallbackTarget->pData = pData;

		if (pthread_create(&_pData->thread, &attributes, callableEntry, this))
		{
			_pData->pCallbackTarget->callback = 0;
			_pData->pCallbackTarget->pData = 0;
			throw SystemException("cannot start thread");
		}

		if (_pData->policy == SCHED_OTHER)
		{
			if (_pData->prio != PRIO_NORMAL_IMPL)
			{
				struct sched_param par;
				par.sched_priority = mapPrio(_pData->prio, SCHED_OTHER);
				if (pthread_setschedparam(_pData->thread, SCHED_OTHER, &par))
					throw SystemException("cannot set thread priority");
			}
		}
		else
		{
			struct sched_param par;
			par.sched_priority = _pData->osPrio;
			if (pthread_setschedparam(_pData->thread, _pData->policy, &par))
				throw SystemException("cannot set thread priority");
		}
#endif
	}

	void Thread::Stop()
	{
		if (!IsRunning())
		{
			return;
		}
#ifdef WINDOWS
		TerminateThread(_thread, 0);
		CloseHandle(_thread);
#else
		pthread_cancel(_thread);
#endif
	}

	void Thread::Join() //wait thread..
	{
#ifdef WINDOWS
		if (!_thread) 
			return;
		switch (WaitForSingleObject(_thread, INFINITE))
		{
		case WAIT_OBJECT_0:
			threadCleanup();
			return;
		default:
			throw SystemException("cannot join thread");
		}
#else
		_pData->done.wait();
		void* result;
		if (pthread_join(_pData->thread, &result))
			throw SystemException("cannot join thread"); 
#endif
	}
	bool Thread::Join(uint32 milliseconds)
	{
#ifdef WINDOWS
		if (!_thread) 
			return true;
		switch (WaitForSingleObject(_thread, milliseconds + 1))
		{
		case WAIT_TIMEOUT:
			return false;
		case WAIT_OBJECT_0:
			threadCleanup();
			return true;
		default:
			throw SystemException("cannot join thread");
		}
#else
		if (_pData->done.tryWait(milliseconds))
		{
			void* result;
			if (pthread_join(_pData->thread, &result))
				throw SystemException("cannot join thread");
			return true;
		}
		else return false;
#endif
	}
	bool Thread::TryJoin(uint32 milliseconds)
	{
		return Join(milliseconds);
	}

	bool Thread::IsRunning() const
	{
#ifdef WINDOWS
		if (_thread)
		{
			DWORD ec = 0;
			return GetExitCodeThread(_thread, &ec) && ec == STILL_ACTIVE;
		}
		return false;
#else
		return _pData->pRunnableTarget != 0 ||
			(_pData->pCallbackTarget.get() != 0 && _pData->pCallbackTarget->callback != 0);
#endif
	}


	void Thread::Sleep(long milliseconds)
	{
#ifdef WINDOWS
		::Sleep(DWORD(milliseconds));
#else
		usleep( milliseconds * 1000);
#endif
	}

	static void Yields()
	{
#ifdef WINDOWS
		::Sleep(0);
#else
		sched_yield();
#endif
	}

	Thread* Thread::Current()
	{
		return _currentThreadHolder.Get();
	}
	ThreadID GetCurrentTID()
	{
#ifdef WINDOWS
		return GetCurrentThreadId();
#else
		return pthread_self();
#endif
	}

	ThreadLocalStorage& Thread::GetTLS()
	{
		if (!_pTLS)
			_pTLS = new ThreadLocalStorage;
		return *_pTLS;
	}
	void Thread::ClearTLS()
	{
		if (_pTLS)
		{
			delete _pTLS;
			_pTLS = NULL;
		}
	}

	std::string Thread::makeName()
	{
		std::ostringstream name;
		name << '#' << _id;
		return name.str();
	}

	namespace
	{
		static FastMutex uniqueIdMutex;
	}
	int Thread::uniqueId()
	{
		FastMutex::ScopedLock lock(uniqueIdMutex);

		static unsigned count = 0;
		++count;
		return count;
	}
#ifdef WINDOWS
	unsigned __stdcall Thread::runnableEntry(void* pThread)
	{
		Thread* p = reinterpret_cast<Thread*>(pThread);
		_currentThreadHolder.Set(p);
		try
		{
			p->_pRunnableTarget->Run();
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}
		return 0;
	}

	unsigned __stdcall Thread::callableEntry(void* pThread)
	{
		Thread* p = reinterpret_cast<Thread*>(pThread);
		_currentThreadHolder.Set(p);
		try
		{
			p->_callbackTarget.callback(p->_callbackTarget.pData);
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}
		return 0;
	}

	void Thread::threadCleanup()
	{
		if (!_thread) return;
		if (CloseHandle(_thread)) _thread = 0;
	}
#else
	int Thread::mapPrio(int prio, int policy)
	{
		int pmin = GetMinOSPriority(policy);
		int pmax = GetMaxOSPriority(policy);

		switch (prio)
		{
		case PRIO_LOWEST:
			return pmin;
		case PRIO_LOW:
			return pmin + (pmax - pmin)/4;
		case PRIO_NORMAL:
			return pmin + (pmax - pmin)/2;
		case PRIO_HIGH:
			return pmin + 3*(pmax - pmin)/4;
		case PRIO_HIGHEST:
			return pmax;
		default:
			//poco_bugcheck_msg("invalid thread priority");
			return -1;
		}
		return -1; // just to satisfy compiler - we'll never get here anyway
	}
	int Thread::reverseMapPrio(int osPrio, int policy)
	{
		if (policy == SCHED_OTHER)
		{
			int pmin = GetMinOSPriority(policy);
			int pmax = GetMaxOSPriority(policy);
			int normal = pmin + (pmax - pmin)/2;
			if (prio == pmax)
				return PRIO_HIGHEST;
			if (prio > normal)
				return PRIO_HIGH;
			else if (prio == normal)
				return PRIO_NORMAL;
			else if (prio > pmin)
				return PRIO_LOW;
			else
				return PRIO_LOWEST;
		}
		else return PRIO_HIGHEST;
	}

	void* Thread::runnableEntry(void* pThread)
	{
		Thread* pThreadImpl = reinterpret_cast<Thread*>(pThread);
		_currentThreadHolder.set(pThreadImpl);
		//增加这么多的信号量
// 		sigset_t sset;
// 		sigemptyset(&sset);
// 		sigaddset(&sset, SIGQUIT);
// 		sigaddset(&sset, SIGTERM);
// 		sigaddset(&sset, SIGPIPE); 
// 		pthread_sigmask(SIG_BLOCK, &sset, 0);
		AutoPtr<ThreadData> pData = pThreadImpl->_pData;
		try
		{
			pData->pRunnableTarget->Run();
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}

		pData->pRunnableTarget = 0;
		pData->done.set();
		return 0;
	}

	void* Thread::callableEntry(void* pThread)
	{
		Thread* pThreadImpl = reinterpret_cast<Thread*>(pThread);
		_currentThreadHolder.set(pThreadImpl);
		//增加这么多的信号量
// 		sigset_t sset;
// 		sigemptyset(&sset);
// 		sigaddset(&sset, SIGQUIT);
// 		sigaddset(&sset, SIGTERM);
// 		sigaddset(&sset, SIGPIPE); 
// 		pthread_sigmask(SIG_BLOCK, &sset, 0);

		AutoPtr<ThreadData> pData = pThreadImpl->_pData;
		try
		{

			pData->pCallbackTarget->callback(pData->pCallbackTarget->pData);
		}
		catch (Exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (std::exception& exc)
		{
			ErrorHandler::handle(exc);
		}
		catch (...)
		{
			ErrorHandler::handle();
		}
		pData->pCallbackTarget->callback = 0;
		pData->pCallbackTarget->pData = 0;
		pData->done.set();
		return 0;
	}
#endif
	
}