
#include "PreCom.h"
#ifdef WINDOWS
#include <process.h>
#else
	#include <sys/syscall.h>
	#include <sys/types.h>
	#include <linux/unistd.h>
#endif
#include <cassert>

#include "Thread.h"


namespace okey
{
	namespace CurrentThread
	{
		const char* t_threadName = "unknown";
	}


	namespace Private
	{
		ProcessID t_cachedTid = 0;

		ProcessID gettid()
		{
		#ifdef WINDOWS
			return GetCurrentProcessId();
		#else
			return static_cast<ProcessID>(::syscall(SYS_gettid));
		#endif
		}


		class ThreadNameInitializer
		{
		 public:
		  ThreadNameInitializer()
		  {
			okey::CurrentThread::t_threadName = "main";
		  }
		};

		ThreadNameInitializer init;
	}




	ProcessID CurrentThread::tid()
	{
		if (Private::t_cachedTid == 0)
		{
#ifdef WINDOWS
			Private::t_cachedTid = GetCurrentProcessId();
#else
			Private::t_cachedTid = gettid();
#endif
		}
		return Private::t_cachedTid;
	}

	const char* CurrentThread::name()
	{
		return t_threadName;
	}

	AtomicCounter Thread::m_numCreated;
	std::map<std::string,Thread*> Thread::threadList;


	Thread::Thread(const std::string& name ,ThreadFunctor* func)
		: m_bstarted(false),
			m_threadId(0),
			m_tid(0),
			m_func(func),
			m_name(name)
	{
#ifdef WINDOWS
			m_handle = NULL;
#else

#endif
			threadList.insert(std::make_pair(name,this));
			++m_numCreated;
	}
	
	Thread::~Thread()
	{
		if (isstarted())
		{
			std::terminate();
		}
		if (m_func)
		{
			delete m_func;
		}
	}

	void Thread::start()
	{
		assert(!m_bstarted);
		m_bstarted = true;
#ifdef WINDOWS
		m_handle =(HANDLE) _beginthreadex(NULL,0,&startThread,(LPVOID)this,0,(uint32*)&m_threadId );
#else
		pthread_create(&m_threadId, NULL, &startThread, this);
#endif

	}

	void Thread::wait()
	{
		if (isstarted())
		{
#ifdef WINDOWS
			WaitForSingleObject( m_handle, INFINITE );
#else
			pthread_join(m_threadId, NULL);
#endif
		}
	}

#ifdef WINDOWS
	uint32  __stdcall Thread::startThread(void* obj)
#else
	void* Thread::startThread(void* obj);
#endif
	{
		Thread* thread = static_cast<Thread*>(obj);
		thread->runInThread();
		return NULL;
	}

	void Thread::runInThread()
	{
		m_tid = CurrentThread::tid();
		okey::CurrentThread::t_threadName = m_name.c_str();
		(*m_func)();
		MutexGuard tGuard(m_Lock);
		m_bstarted = false;
	}

	void Thread::stop()
	{
#ifdef WINDOWS
		TerminateThread(m_handle,0);
		CloseHandle(m_handle);
#else
		pthread_cancel(m_tid);
#endif
	}

	bool Thread::isstarted() const
	{
		m_Lock.Lock();
		bool result = m_bstarted;
		m_Lock.UnLock();
		return result;
	}

	void Thread::StopAllThread()
	{
		std::map<std::string, Thread*>::iterator itr = threadList.begin();
		for (; itr != threadList.end(); ++itr)
		{
			itr->second->wait();
		}
	}
}