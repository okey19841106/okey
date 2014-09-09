
#ifndef OKEY_BASE_THREAD_H
#define OKEY_BASE_THREAD_H



#ifdef WINDOWS                // windows95 and above
//#include <windows.h>
#include <map>
#else                       // linux
#include <pthread.h>
#include <unistd.h>
#endif

#include "Types.h"
#include "AtomicCounter.h"
#include "Fuction.h"
#include "nocopyable.h"
#include "Mutex.h"


namespace okey
{


	class ThreadFunctor
	{
	public:
		ThreadFunctor(){}
		virtual ~ThreadFunctor(){}
		virtual void operator()() = 0;
	};

	template<typename T>
	class ThreadClassFuntor0: public ThreadFunctor
	{

		typedef void (T::*fun)(void);
		T* pClassObj;
		fun f_;
	public:
		ThreadClassFuntor0(T* pClass, fun pfun):pClassObj(pClass),f_(pfun){}
		~ThreadClassFuntor0(){}

		virtual void operator()()
		{
			(pClassObj->*f_)();
		}
	};

	class ThreadFuntor0: public ThreadFunctor
	{
		typedef void (*fun)();
		fun f_;
	public:
		ThreadFuntor0(fun pfun):f_(pfun){}
		~ThreadFuntor0(){}

		virtual void operator()()
		{
			(*f_)();
		}
	};


	template<typename T,typename Arg>
	class ThreadClassFuntor1: public ThreadFunctor
	{
		typedef void (T::*fun)(Arg*);
		T* pClassObj;
		fun f_;
		Arg* arg_;
	public:
		ThreadClassFuntor1(T* pClass, fun pfun, Arg* arg):pClassObj(pClass),f_(pfun),arg_(arg){}
		~ThreadClassFuntor1(){}

		virtual void operator()()
		{
			(pClassObj->*f_)(arg);
		}
	};

	template<typename Arg>
	class ThreadFuntor1: public ThreadFunctor
	{
		typedef void (*fun)(Arg*);
		fun f_;
		Arg* arg_;
	public:
		ThreadFuntor1(fun pfun, Arg* arg):f_(pfun),arg_(arg){}
		~ThreadFuntor1(){}

		virtual void operator()()
		{
			(*f_)(arg_);
		}
	};

	/////////////////////////////////thread//////////////////////

	class Thread : private nocopyable
	{
	public:
	  //typedef void (*ThreadFunc)(void*);;

		Thread(const std::string& name ,ThreadFunctor* func);
		//Thread(const std::string& name, CFunctionArg0Base* func);
		~Thread();

		void start();
		void wait();
		void stop();
		bool isstarted() const;

		// pthread_t pthreadId() const { return pthreadId_; }
		ProcessID tid() const { return m_tid; }
		std::string name() const { return m_name; }

		static int32 numCreated() { return (int32)m_numCreated.GetVal(); }

	private:
#ifdef WINDOWS
		static  uint32  __stdcall startThread(void* thread);
#else
		static void* startThread(void* thread);
#endif
	  
		void runInThread();


		mutable Mutex	m_Lock;
		bool       m_bstarted;
		ThreadID  m_threadId;
		ProcessID      m_tid;
		ThreadFunctor* m_func;
		std::string     m_name;
#ifdef WINDOWS
		HANDLE m_handle;
#endif
		static std::map<std::string, Thread*> threadList;
		static AtomicCounter m_numCreated;

		static void StopAllThread();
	};

	namespace CurrentThread
	{
	  ProcessID tid();
	  const char* name();
	}

}
#endif
