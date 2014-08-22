/********************************************************************
	created:	2014/08/22
	created:	16:48
	author:		
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_THREAD_H__
#define __OKEY_THREAD_H__

#include <map>
#include <string>

namespace okey
{
	class Thread;
	class ThreadManager
	{
	public:
		ThreadManager();
		~ThreadManager();
		void AddThread(Thread* pThread);
		bool StopThread(const std::string& name);
		bool StopThread(ProcessID pid); 
	public:
		static std::map<std::string, Thread*> m_ThreadList;
	};

	extern ThreadManager& GetThreadManager();
}


#endif