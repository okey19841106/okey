/********************************************************************
	created:	2014/08/22
	created:	16:46
	author:		
	purpose:	
*********************************************************************/


#ifndef OKEY_BASE_THREADPOOL_H
#define OKEY_BASE_THREADPOOL_H



#include "Types.h"
#include <vector>
#include <string>
#include "Thread.h"
#include "Mutex.h"



namespace okey
{
	class Runnable;
	class PooledThread;
	class ThreadPool
	{
	public:
		ThreadPool(int32 minCapacity = 2, int32 maxCapacity = 16, int32 idleTime = 60, int32 stackSize = THREAD_STACK_SIZE);
		ThreadPool(const std::string& name,	int32 minCapacity = 2, int32 maxCapacity = 16, int32 idleTime = 60,	int32 stackSize = THREAD_STACK_SIZE);
		virtual ~ThreadPool();
		void AddCapacity(int32 n);
		int32 Capacity() const;
		void SetStackSize(int32 stackSize){_stackSize = stackSize;}
		int32 GetStackSize() const{return _stackSize;}
		int Getused() const;		/// Returns the number of currently used threads.
		int GetAllocated() const;		/// Returns the number of currently allocated threads.
		int GetAvailable() const;		/// Returns the number available threads.
		void Start(Runnable& target);
		void Start(Runnable& target, const std::string& name);
		void StartWithPriority(Thread::Priority priority, Runnable& target);
		void StartWithPriority(Thread::Priority priority, Runnable& target, const std::string& name);
		void StopAll();
		void JoinAll();
		void Collect();		/// Stops and removes no longer used threads from the thread pool. 
		const std::string& GetName() const{return _name;}
		static ThreadPool& defaultPool();/// Returns a reference to the default
	protected:
		PooledThread* getThread();
		PooledThread* createThread();
		void housekeep();
	private:
		ThreadPool(const ThreadPool& pool);
		ThreadPool& operator = (const ThreadPool& pool);
	private:
		typedef std::vector<PooledThread*> ThreadVec;
		std::string _name;
		int32 _minCapacity;
		int32 _maxCapacity;
		int32 _idleTime;
		int32 _serial;
		int32 _age;
		int32 _stackSize;
		ThreadVec _threads;
		mutable FastMutex _mutex;
	};

}

#endif
