#include "PreCom.h"
#include "ThreadManager.h"
#include "Thread.h"



namespace okey
{

	ThreadManager& GetThreadManager()
	{
		static ThreadManager inst;
		return inst;
	}

	ThreadManager::ThreadManager()
	{

	}

	ThreadManager::~ThreadManager()
	{

	}

	void ThreadManager::AddThread(Thread* pThread)
	{
		//assert(pthread)
		m_ThreadList.insert(std::make_pair(pThread->name(),pThread));
	}

	bool ThreadManager::StopThread(const std::string& name)
	{
		std::map<std::string, Thread*>::iterator itr = m_ThreadList.find(name);
		if (itr == m_ThreadList.end())
		{
			return false;
		}
		itr->second->stop();
		return true;
		/*itr->second*/
	}

}