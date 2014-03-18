
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


	namespace
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
		if (t_cachedTid == 0)
		{
#ifdef WINDOWS
			t_cachedTid = GetCurrentProcessId();
#else
			t_cachedTid = gettid();
#endif
		}
		return t_cachedTid;
	}

	const char* CurrentThread::name()
	{
		return t_threadName;
	}

	AtomicCounter Thread::m_numCreated;

	Thread::Thread(CFunctionArg0Base * func, const std::string& n)
		: m_bstarted(false),
		m_threadId(0),
		m_tid(0),
		m_func(func),
		m_name(n)
	{
#ifdef WINDOWS
		m_handle = NULL;
#else
		++m_numCreated;
#endif
	}

	Thread::~Thread()
	{
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
		assert(m_bstarted);
#ifdef WINDOWS
		WaitForSingleObject( m_handle, INFINITE );
		CloseHandle( m_handle );
#else
		pthread_join(m_threadId, NULL);
#endif

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
		okey::CurrentThread::t_threadName = "finished";
	}

}