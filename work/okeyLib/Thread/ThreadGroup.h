/********************************************************************
	created:	2015/02/05
	created:	16:22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_THREAD_GROUP_H__
#define __OKEY_THREAD_GROUP_H__

#include <vector>
#include "Runnable.h"

namespace okey
{
	class Thread;

	class ThreadGroup: public Runnable
	{
		typedef std::vector<std::pair<Thread* , Runnable* > > THREAD_VEC;
	public:
		ThreadGroup(){}
		virtual ~ThreadGroup();
		void StartThreads(uint32 numOfThread);
		void StopThreads();
		uint32 GetThreadNum() const;
		Thread* GetMiniLoadThread();
		virtual void Run();
	protected:
		virtual std::pair<Thread*, Runnable*> CreateThread() = 0;
		virtual void DestroyThread(std::pair<Thread*, Runnable*> threadinfo) = 0;
	private:
		THREAD_VEC m_Threads;
		Runnable*  _pTarget;
	};
}

#endif