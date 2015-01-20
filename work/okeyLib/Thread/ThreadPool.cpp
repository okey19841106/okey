#include "PreCom.h"
#include "ThreadPool.h"
#include <sstream>
#include "Event.h"
#include "Runnable.h"
#include <ctime>
#include "ErrorHandler.h"
#include "ThreadLocal.h"

namespace okey
{
	class PooledThread: public Runnable
	{
	public:
		PooledThread(const std::string& name, int stackSize = THREAD_STACK_SIZE);
		~PooledThread();
		void Start();
		void Start(Thread::Priority priority, Runnable& target);
		void Start(Thread::Priority priority, Runnable& target, const std::string& name);
		bool Idle();
		void Release();
		void Join();
		void Activate();
		int32 IdleTime();
		virtual void Run();
	private:
		volatile bool        _idle;
		volatile std::time_t _idleTime;
		Runnable*            _pTarget;
		std::string          _name;
		Thread               _thread;
		Event                _targetReady;//目标准备完成。
		Event                _targetCompleted;//执行完毕。
		Event                _started; //run已经完成。
		FastMutex            _mutex;
	};

	PooledThread::PooledThread(const std::string& name, int stackSize):
	_idle(true), 
	_idleTime(0), 
	_pTarget(NULL), 
	_name(name), 
	_thread(name),
	_targetCompleted(false)
	{
		_idleTime = std::time(NULL);
	}
	PooledThread::~PooledThread()
	{
		
	}
	void PooledThread::Start()
	{
		_thread.Start(*this);
		_started.Wait();//等待执行完毕。
	}

	void PooledThread::Start(Thread::Priority priority, Runnable& target)
	{
		FastMutex::ScopedLock lock(_mutex);
		_pTarget = &target;
		_thread.SetPriority(priority);
		_targetReady.Set();
	}

	void PooledThread::Start(Thread::Priority priority, Runnable& target, const std::string& name)
	{
		FastMutex::ScopedLock lock(_mutex);
		std::string fullName(name);
		if (name.empty())
		{
			fullName = _name;
		}
		else
		{
			fullName.append(" (");
			fullName.append(_name);
			fullName.append(")");
		}
		_thread.SetName(fullName);
		_pTarget = &target;
		_thread.SetPriority(priority);
		_targetReady.Set();
	}

	bool PooledThread::Idle()
	{
		return _idle;
	}

	void PooledThread::Release()
	{
		const long JOIN_TIMEOUT = 10000;
		_mutex.Lock();
		_pTarget = 0;
		_mutex.UnLock();
		_targetReady.Set();
		if (_thread.TryJoin(JOIN_TIMEOUT))
		{
			delete this;
		}
	}
	void PooledThread::Join()
	{
		_mutex.Lock();
		Runnable* pTarget = _pTarget;
		_mutex.UnLock();
		if (pTarget)
			_targetCompleted.Wait();
	}

	void PooledThread::Activate()
	{
		FastMutex::ScopedLock lock(_mutex);

		//poco_assert (_idle);
		_idle = false;
		_targetCompleted.Reset(); //没完成。。
	}

	int32 PooledThread::IdleTime()
	{
		FastMutex::ScopedLock lock(_mutex);
		return (int) (time(NULL) - _idleTime);

	}
	void PooledThread::Run()
	{
		_started.Set();
		for (;;)
		{
			_targetReady.Wait();//等待目标完成。
			_mutex.Lock();
			if (_pTarget) // a NULL target means kill yourself
			{
				_mutex.UnLock();
				try
				{
					_pTarget->Run();
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
				FastMutex::ScopedLock lock(_mutex);
				_pTarget  = NULL;
				_idleTime = time(NULL);
				_idle     = true;
				_targetCompleted.Set();//完成了。
				ThreadLocalStorage::Clear();
				_thread.SetName(_name);
				_thread.SetPriority(Thread::PRIO_NORMAL);
			}
			else
			{
				_mutex.UnLock();
				break;
			}
		}
	}

	ThreadPool::ThreadPool(int32 minCapacity, int32 maxCapacity, int32 idleTime, int32 stackSize ):
	_minCapacity(minCapacity),
	_maxCapacity(maxCapacity),
	_idleTime(idleTime),
	_stackSize(stackSize),
	_serial(0),
	_age(0)
	{
		for (int i = 0; i < _minCapacity; i++)
		{
			PooledThread* pThread = createThread();
			_threads.push_back(pThread);
			pThread->Start();
		}
	}

	ThreadPool::ThreadPool(const std::string& name,	int32 minCapacity, int32 maxCapacity, int32 idleTime ,	int32 stackSize):
	_minCapacity(minCapacity),
		_maxCapacity(maxCapacity),
		_idleTime(idleTime),
		_stackSize(stackSize),
		_name(name),
		_serial(0),
		_age(0)
	{
		for (int i = 0; i < _minCapacity; i++)
		{
			PooledThread* pThread = createThread();
			_threads.push_back(pThread);
			pThread->Start();
		}
	}
	ThreadPool::~ThreadPool()
	{
		StopAll();
	}
	void ThreadPool::AddCapacity(int32 n)
	{
		FastMutex::ScopedLock lock(_mutex);

		//poco_assert (_maxCapacity + n >= _minCapacity);
		_maxCapacity += n;
		housekeep();
	}
	int32 ThreadPool::Capacity() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _maxCapacity;
	}

	int32 ThreadPool::Getused() const
	{
		FastMutex::ScopedLock lock(_mutex);
		int32 count = 0;
		for (ThreadVec::const_iterator it = _threads.begin(); it != _threads.end(); ++it)
		{
			if (!(*it)->Idle()) 
				++count;
		}
		return (int32) (count + _maxCapacity - _threads.size());
	}

	int32 ThreadPool::GetAllocated() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return int32(_threads.size());
	}

	int32 ThreadPool::GetAvailable() const
	{
		FastMutex::ScopedLock lock(_mutex);

		int32 count = 0;
		for (ThreadVec::const_iterator it = _threads.begin(); it != _threads.end(); ++it)
		{
			if ((*it)->Idle()) 
				++count;
		}
		return count;
	}
	void ThreadPool::Start(Runnable& target)
	{
		getThread()->Start(Thread::PRIO_NORMAL, target);
	}
	void ThreadPool::Start(Runnable& target, const std::string& name)
	{
		getThread()->Start(Thread::PRIO_NORMAL, target, name);
	}
	void ThreadPool::StartWithPriority(Thread::Priority priority, Runnable& target)
	{
		getThread()->Start(priority, target);
	}
	void ThreadPool::StartWithPriority(Thread::Priority priority, Runnable& target, const std::string& name)
	{
		getThread()->Start(priority, target, name);
	}
	void ThreadPool::StopAll()
	{
		FastMutex::ScopedLock lock(_mutex);
		for (ThreadVec::iterator it = _threads.begin(); it != _threads.end(); ++it)
		{
			(*it)->Release();
		}
		_threads.clear();
	}
	void ThreadPool::JoinAll()
	{
		FastMutex::ScopedLock lock(_mutex);

		for (ThreadVec::iterator it = _threads.begin(); it != _threads.end(); ++it)
		{
			(*it)->Join();
		}
		housekeep();
	}
	void ThreadPool::Collect()
	{
		FastMutex::ScopedLock lock(_mutex);
		housekeep();
	}

	

	PooledThread* ThreadPool::getThread()
	{
		FastMutex::ScopedLock lock(_mutex);
		if (++_age == 32)
			housekeep();
		PooledThread* pThread = 0;
		for (ThreadVec::iterator it = _threads.begin(); !pThread && it != _threads.end(); ++it)
		{
			if ((*it)->Idle())
			{
				pThread = *it;
				break;
			}
		}
		if (!pThread)
		{
			if ((int32)_threads.size() < _maxCapacity)
			{
				pThread = createThread();
				try
				{
					pThread->Start();
					_threads.push_back(pThread);
				}
				catch (...)
				{
					delete pThread;
					throw;
				}
			}
			else 
				throw NoThreadAvailableException();
		}
		pThread->Activate();
		return pThread;
	}

	PooledThread* ThreadPool::createThread()
	{
		std::ostringstream name;
		name << _name << "[#" << ++_serial << "]";
		return new PooledThread(name.str(), _stackSize);
	}

	void ThreadPool::housekeep() //重新排序， idle expired active。。
	{
		_age = 0;
		if ((int32)_threads.size() <= _minCapacity)
			return;
		ThreadVec idleThreads;
		ThreadVec expiredThreads;
		ThreadVec activeThreads;
		idleThreads.reserve(_threads.size());
		activeThreads.reserve(_threads.size());
		for (ThreadVec::iterator it = _threads.begin(); it != _threads.end(); ++it)
		{
			if ((*it)->Idle())
			{
				if ((*it)->IdleTime() < _idleTime)
					idleThreads.push_back(*it);
				else 
					expiredThreads.push_back(*it);	
			}
			else activeThreads.push_back(*it);
		}
		int32 n = (int) activeThreads.size();
		int32 limit = (int) idleThreads.size() + n;
		if (limit < _minCapacity) 
			limit = _minCapacity;
		idleThreads.insert(idleThreads.end(), expiredThreads.begin(), expiredThreads.end());
		_threads.clear();
		for (ThreadVec::iterator it = idleThreads.begin(); it != idleThreads.end(); ++it)
		{
			if (n < limit)
			{
				_threads.push_back(*it);
				++n;
			}
			else (*it)->Release();
		}
		_threads.insert(_threads.end(), activeThreads.begin(), activeThreads.end());
	}

	class ThreadPoolSingletonHolder
	{
	public:
		ThreadPoolSingletonHolder()
		{
			_pPool = 0;
		}
		~ThreadPoolSingletonHolder()
		{
			delete _pPool;
		}
		ThreadPool* Pool()
		{
			FastMutex::ScopedLock lock(_mutex);
			if (!_pPool)
			{
				_pPool = new ThreadPool("default");
				if (THREAD_STACK_SIZE > 0)
					_pPool->SetStackSize(THREAD_STACK_SIZE);
			}
			return _pPool;
		}

	private:
		ThreadPool* _pPool;
		FastMutex   _mutex;
	};

	namespace
	{
		static ThreadPoolSingletonHolder sh;
	}

	ThreadPool& ThreadPool::defaultPool()
	{
		return *sh.Pool();
	}
}