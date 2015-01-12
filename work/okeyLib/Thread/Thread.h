/********************************************************************
	created:	2015/01/12
	created:	14:42
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_THREAD_H__
#define __OKEY_THREAD_H__



namespace okey{


	class Runnable;
	class ThreadLocalStorage;

	

	class Thread
	{
	public:	
		using ThreadImpl::Callable;

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
			PRIO_LOWEST , /// The lowest thread priority.
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

	public:
		struct ThreadData: public CRefCounter
		{
			ThreadData():
			pRunnableTarget(0),
			pCallbackTarget(0),
			thread(NULL),
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
	

		void start(Runnable& target);
		void start(Callable target, void* pData = 0);


		void Join();
		void Join(long milliseconds);
		bool TryJoin(long milliseconds);

		bool IsRunning() const;
		

		static void Sleep(long milliseconds);
		static void Yields();
			/// Yields cpu to other threads.

		static Thread* Current();
 		static ThreadID GetCurrentTID();

	protected:
		ThreadLocalStorage& GetTLS(); //TLS
		void ClearTLS();

		std::string makeName();
		static int uniqueId();//创建一个全局唯一码。
		
	private:
		Thread(const Thread&);
		Thread& operator = (const Thread&);

		int                 _id;
		std::string         _name;
		ThreadLocalStorage* _pTLS;
		mutable Mutex   _mutex;

		friend class ThreadLocalStorage;
		friend class PooledThread;
	};

} 
#endif 
