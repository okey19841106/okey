#include "PreCom.h"
#include "ThreadManager.h"
#include "Thread.h"



namespace okey
{
	std::map<std::string, Thread*> ThreadManager::m_ThreadList;
	ThreadManager::ThreadManager()
	{

	}

	ThreadManager::~ThreadManager()
	{

	}

	void ThreadManager::AddThread(Thread* pThread)
	{

	}

	bool ThreadManager::StopThread(const std::string& name)
	{

	}

	bool ThreadManager::StopThread(ProcessID pid)
	{

	}
}