/********************************************************************
	created:	2015/01/12
	created:	14:42
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_THREAD_H__
#define __OKEY_THREAD_H__

#include "CRefcounter.h"
#include "Mutex.h"
#include "Exception.h"

namespace okey{


	class Runnable;
	class ThreadLocalStorage;

	

	class Thread
	{
	public:	
		typedef void (*Callable)(void*);

		struct CallbackData: public CRefCounter
		{
			CallbackData(): callback(NULL), pData(NULL)
			{
			}

			Callable  callback;
			void*     pData; 
		};
		
		enum Priority
		{
#ifdef WINDOWS
			PRIO_LOWEST  = THREAD_PRIORITY_LOWEST,
			PRIO_LOW     = THREAD_PRIORITY_BELOW_NORMAL,
			PRIO_NORMAL  = THREAD_PRIORITY_NORMAL,
			PRIO_HIGH    = THREAD_PRIORITY_ABOVE_NORMAL,
			PRIO_HIGHEST = THREAD_PRIORITY_HIGHEST
#else
			PRIO_LOWEST = 0, /// The lowest thread priority.
			PRIO_LOW ,    /// A lower than normal thread priority.
			PRIO_NORMAL , /// The normal thread priority.
			PRIO_HIGH,   /// A higher than normal thread priority.
			PRIO_HIGHEST, /// The highest thread priority.
#endif
			
		};
		enum Policy
		{
#ifdef WINDOWS
			POLICY_DEFAULT = 0,
#else
			POLICY_DEFAULT = SCHED_OTHER,
#endif
			
		};

	private:
#ifndef WINDOWS
		struct ThreadData: public CRefCounter
		{
			ThreadData():
			pRunnableTarget(NULL),
			pCallbackTarget(NULL),
			thread(0),
			prio(PRIO_NORMAL),
			policy(POLICY_DEFAULT),
			done(false),
			stackSize(0)
			{

			}
			Runnable*     pRunnableTarget;
			AutoPtr<CallbackData> pCallbackTarget;
			ThreadID     thread;
			int           prio;
			int           osPrio;
			int           policy;
			Event         done;
			std::size_t   stackSize;
		};
#endif
		class CurrentThreadHolder
		{
		public:
			CurrentThreadHolder()
			{
#ifdef WINDOWS
				_slot = TlsAlloc();
				if (_slot == TLS_OUT_OF_INDEXES)
					throw SystemException("cannot allocate thread context key");
#else
				if (pthread_key_create(&_key, NULL))
					throw SystemException("cannot allocate thread context key");
#endif
			}
			~CurrentThreadHolder()
			{
#ifdef WINDOWS
				TlsFree(_slot);
#else
				pthread_key_delete(_key);
#endif
			}
			Thread* Get() const
			{
#ifdef WINDOWS
				return reinterpret_cast<Thread*>(TlsGetValue(_slot));
#else
				return reinterpret_cast<Thread*>(pthread_getspecific(_key));
#endif
				
			}
			void Set(Thread* pThread)
			{
#ifdef WINDOWS
				TlsSetValue(_slot, pThread);
#else
				pthread_setspecific(_key, pThread);
#endif
			}

		private:
#ifdef WINDOWS
			DWORD _slot;
#else
			pthread_key_t _key;
#endif
			
		};
	public:
		Thread();
		Thread(const std::string& name);
		~Thread();
		int GetID() const{return _id;}
		ThreadID GetTID() const; //局部id
		std::string GetName() const;
		void SetName(const std::string& name);
		void SetPriority(Priority prio); //优先级
		Priority GetPriority() const;
		void SetOSPriority(int prio, int policy = POLICY_DEFAULT);
		int GetOSPriority() const;
		static int GetMinOSPriority(int policy = POLICY_DEFAULT);
		static int GetMaxOSPriority(int policy = POLICY_DEFAULT);
		void SetStackSize(int size);//设置线程堆栈大小
		int GetStackSize() const;
		void Start(Runnable& target);
		void Start(Callable target, void* pData = NULL);
		void Join();
		bool Join(uint32 milliseconds);
		bool TryJoin(uint32 milliseconds);
		bool IsRunning() const;
		static void Sleep(long milliseconds);
		static void Yields();/// Yields cpu to other threads.
		static Thread* Current();
 		static ThreadID GetCurrentTID();
		virtual uint32 GetLoad()const{return 1;} //负载量。
		virtual void Stop();
	protected:
		ThreadLocalStorage& GetTLS(); //TLS
		void ClearTLS();

		std::string makeName();
		static int uniqueId();//创建一个全局唯一码。

#ifndef WINDOWS
		static int mapPrio(int prio, int policy);
		static int reverseMapPrio(int osPrio, int policy = SCHED_OTHER);
		static void* runnableEntry(void* pThread);
		static void* callableEntry(void* pThread);
#else
		static unsigned __stdcall runnableEntry(void* pThread);
		static unsigned __stdcall callableEntry(void* pThread);
		void threadCleanup();
#endif
		
	private:
		Thread(const Thread&);
		Thread& operator = (const Thread&);
	private:
#ifdef WINDOWS
		Runnable*    _pRunnableTarget;
		CallbackData _callbackTarget;
		HANDLE       _thread;
		DWORD        _threadId;
		int          _prio;
		int          _stackSize;
#else
		AutoPtr<ThreadData> _pData;
#endif
		static CurrentThreadHolder _currentThreadHolder;

		int                 _id;
		std::string         _name;
		ThreadLocalStorage* _pTLS;
		mutable FastMutex   _mutex;
		friend class ThreadLocalStorage;
		friend class PooledThread;
	};

	inline std::string Thread::GetName() const
	{
		FastMutex::ScopedLock m(_mutex);
		return _name;
	}

	inline void Thread::SetName(const std::string& name)
	{
		FastMutex::ScopedLock m(_mutex);
		_name = name;
	}

	inline int Thread::GetOSPriority() const
	{
#ifdef WINDOWS
		return _prio;
#else
		return _pData->osPrio;
#endif
	}

	inline 	ThreadID Thread::GetTID() const
	{
#ifdef WINDOWS
		return _threadId;
#else
		return _pData->thread;
#endif

	}

	inline 	Thread::Priority Thread::GetPriority() const
	{
#ifdef WINDOWS
		return Priority(_prio);
#else
		return Priority(_pData->prio);
#endif
	}

	inline int Thread::GetStackSize() const
	{
#ifdef WINDOWS
		return _stackSize;
#else
		return _pData->stackSize;
#endif
	}
} 
#endif 
