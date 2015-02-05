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
		typedef std::vector<Thread*> THREAD_VEC;
	public:
		ThreadGroup(){}
		ThreadGroup(Runnable& p);
		virtual ~ThreadGroup();
		void StartThreads(uint32 numOfThread, Runnable& tar );
		void StopThreads();
		uint32 GetThreadNum() const;
		Thread* GetMiniLoadThread();
		virtual void Run();
	protected:
		virtual Thread* CreateThread();
		virtual void DestroyThread(Thread* thread);
	private:
		THREAD_VEC m_Threads;
		Runnable*  _pTarget;
	};
}

#endif