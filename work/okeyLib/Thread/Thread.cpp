
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
	Thread::Thread():_id(uniqueId()), 
		_name(makeName()), 
		_pTLS(NULL)
	{

	}
	Thread::Thread(const std::string& name):_id(uniqueId()), 
		_name(name), 
		_pTLS(NULL)
	{

	}
	Thread::~Thread()
	{
		delete _pTLS;
	}
	ThreadID Thread::GetTID() const
	{

	}
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
	static TID GetCurrentTID();

	ThreadLocalStorage& GetTLS(); //TLS
	void ClearTLS();

	std::string makeName();
	static int uniqueId();//创建一个全局唯一码。
}