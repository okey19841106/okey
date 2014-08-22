/********************************************************************
	created:	2014/08/22
	created:	16:46
	author:		
	purpose:	
*********************************************************************/


#ifndef OKEY_BASE_THREADPOOL_H
#define OKEY_BASE_THREADPOOL_H



#include <deque>
#include <vector>
#include <string>
#include "nocopyable.h"
#include "Fuction.h"
#include "Mutex.h"
#include "Condition.h"


namespace okey
{
	
	class Thread;

	class ThreadPool : private nocopyable
	{
		public:
		//	  typedef void (*Task)(void*);

		explicit ThreadPool(const std::string& name = std::string());
		~ThreadPool();

		void start(int32 numThreads);
		void stop();

		void run(CFunctionArg0Base* f);

		private:
		void runInThread();
		CFunctionArg0Base* take();

		Mutex m_mutex;
		Condition m_cond;
		std::string m_name;
		std::vector<Thread*> m_threads;
		std::deque<CFunctionArg0Base*> m_queue;
		bool m_running;
	};

}

#endif
