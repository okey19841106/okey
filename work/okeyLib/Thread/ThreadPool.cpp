#include "PreCom.h"
#include <assert.h>
#include <stdio.h>
#include "ThreadPool.h"
#include "Exception.h"
#include "Thread.h"
#include "Mutex.h"


namespace okey
{



	ThreadPool::ThreadPool(const std::string& name)
		: m_name(name),
		m_running(false)
	{
	}

	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::start(int32 numThreads)
	{
		assert(m_threads.empty());
		m_running = true;
		m_threads.reserve(numThreads);
		for (int32 i = 0; i < numThreads; ++i)
		{
			char id[32];
#ifdef WINDOWS
			_snprintf_s(id, sizeof (id), "%d", i);
#else
			snprintf(id, sizeof id, "%d", i);
#endif

			m_threads.push_back(new Thread(
				new CFunctionArg0<ThreadPool>(this, &ThreadPool::runInThread), m_name+id));
			(m_threads[i])->start();
		}
	}

	void ThreadPool::stop()
	{
		m_running = false;
		m_cond.broadcast();
		std::vector<Thread*>::iterator itr =m_threads.begin();
		for (;itr!=m_threads.end();++itr)
		{
			(*itr)->wait();
			delete (*itr);
		}
	}

	void ThreadPool::run(CFunctionArg0Base* f)
	{
		if (m_threads.empty())
		{
			(*f)();
		}
		else
		{
			MutexGuard lock(m_mutex);
			m_queue.push_back(f);
			m_cond.signal();
		}
	}

	CFunctionArg0Base* ThreadPool::take()
	{
		m_mutex.Lock();
		while (m_queue.empty() && m_running)
		{
			m_cond.wait(m_mutex);
		}
		CFunctionArg0Base* task;
		if(!m_queue.empty())
		{
			task = m_queue.front();
			m_queue.pop_front();
		}
		m_mutex.UnLock();
		return task;
	}

	void ThreadPool::runInThread()
	{
		try
		{
			while (m_running)
			{
				CFunctionArg0Base* task = take();
				if (task)
				{
					(*task)();
				}
				if (!task)
				{
					delete task;
				}
				
			}
		}
		catch (const Exception& ex)
		{
			fprintf(stderr, "exception caught in ThreadPool %s\n", m_name.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			fprintf(stderr, "stack trace: %s\n", ex.stackTrace());
			abort();
		}
		catch (const std::exception ex)
		{
			fprintf(stderr, "exception caught in ThreadPool %s\n", m_name.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			abort();
		}
		catch (...)
		{
			fprintf(stderr, "unknown exception caught in ThreadPool %s\n", m_name.c_str());
			abort();
		}
	}

}