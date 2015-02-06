#include "PreCom.h"
#include "ThreadGroup.h"
#include "Thread.h"
#include "ErrorHandler.h"

namespace okey
{
	
	ThreadGroup::~ThreadGroup()
	{
		StopThreads();
	}
	void ThreadGroup::StartThreads(uint32 numOfThread)
	{
		if (!m_Threads.empty())
		{
			return;
		}
		for(uint32 i = 0; i < numOfThread; ++i)
		{
			std::pair<Thread*, Runnable*> threadinfo = CreateThread();
			if (threadinfo.first != NULL)
			{
				m_Threads.push_back(threadinfo);
				threadinfo.first->Start(*(threadinfo.second));
			}
		}
	}
	void ThreadGroup::StopThreads()
	{
		for(THREAD_VEC::iterator itr = m_Threads.begin(); itr != m_Threads.end(); ++itr)
		{
			itr->first->Stop();
			itr->first->Join();
			DestroyThread(*itr);
		}
		m_Threads.clear();
	}

	uint32 ThreadGroup::GetThreadNum() const
	{
		return m_Threads.size();
	}

	Thread* ThreadGroup::GetMiniLoadThread()
	{
		if (m_Threads.empty())
		{
			return;
		}
		uint32 threadidx = 0;
		uint32 threadload = uint32(-1);
		for (uint32 i = 0; i < m_Threads.size(); ++i)
		{
			if (m_Threads[i].first->GetLoad() < threadload)
			{
				threadload = m_Threads[i].first->GetLoad();
				threadidx = i;
			}
		}
		std::swap(m_Threads[threadidx], m_Threads[m_Threads.size() - 1]);
		return m_Threads[m_Threads.size() - 1].first;
	}

// 	std::pair<Thread*, Runnable*> ThreadGroup::CreateThread()
// 	{
// 		Thread* pThread = new Thread;
// 		return new Thread;
// 	}
// 
// 	void ThreadGroup::DestroyThread(Thread* thread)
// 	{
// 		if (thread)
// 		{
// 			delete thread;
// 		}
// 	}
	void ThreadGroup::Run()
	{
		if (_pTarget) // a NULL target means kill yourself
		{
			try
			{
				_pTarget->Run();
			}
			catch (Exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch (std::exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch (...)
			{
				ErrorHandler::handle();
			}
			_pTarget  = NULL;
		}
	}
}