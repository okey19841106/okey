
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
	class ThreadClassFuntor0: ThreadFunctor
	{

		typedef void (*T::fun)(void);
		fun f_;
	public:
		ThreadClassFuntor0(T* pClass, fun pfun):f_(pfun){}
		~ThreadClassFuntor0(){}

		virtual void operator()()
		{
			(pClass->*f_)();
		}
	};

	class ThreadFuntor0: ThreadFunctor
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


	template<typename T>
	class ThreadClassFuntor1: ThreadFunctor
	{
		typedef void (*T::fun)(void*);
		fun f_;
		void* arg_;
	public:
		ThreadClassFuntor1(T* pClass, fun pfun, void* arg):f_(pfun),arg_(arg){}
		~ThreadClassFuntor1(){}

		virtual void operator()()
		{
			(pClass->*f_)(arg);
		}
	};

	class ThreadFuntor1: ThreadFunctor
	{
		typedef void (*fun)(void*);
		fun f_;
		void* arg_;
	public:
		ThreadFuntor1(fun pfun, void* arg):f_(pfun),arg_(arg){}
		~ThreadFuntor1(){}

		virtual void operator()()
		{
			(*f_)(arg_);
		}
	};

	class Thread : private nocopyable
	{
	public:
	  //typedef void (*ThreadFunc)(void*);;

		Thread(const std::string& name ,CFunctionArg1Base<void*>* func, void* arg);
		Thread(const std::string& name, CFunctionArg0Base* func);
		~Thread();

		void start();
		void wait();
		void stop();
		bool started() const { return m_bstarted; }
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

		bool       m_bstarted;
		ThreadID  m_threadId;
		ProcessID      m_tid;
		CFunctionArg1Base<void*> *m_func;
		void* m_pargs;
		std::string     m_name;
#ifdef WINDOWS
		HANDLE m_handle;
#endif
		static std::map<std::string, Thread*> threadList;
		static AtomicCounter m_numCreated;
	};

	namespace CurrentThread
	{
	  ProcessID tid();
	  const char* name();
	}

}
#endif
