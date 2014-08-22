
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


	

	class Thread : private nocopyable
	{
	 public:
	  //typedef void (*ThreadFunc)(void*);;

	  Thread(CFunctionArg0Base*, const std::string& name = std::string());
	  ~Thread();

	  void start();
	  void wait();

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
	  CFunctionArg0Base *m_func;
	  std::string     m_name;
#ifdef WINDOWS
	   HANDLE m_handle;
#endif
	 
	  static AtomicCounter m_numCreated;
	};

	namespace CurrentThread
	{
	  ProcessID tid();
	  const char* name();
	}

}
#endif
