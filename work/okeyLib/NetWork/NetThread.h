/********************************************************************
	created:	2015/02/05
	created:	17:23
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_NET_THREAD_H__
#define __OKEY_NET_THREAD_H__

#include <vector>
#include "Thread/Thread.h"
#include "Thread/Mutex.h"



namespace okey
{
	class Event_Handler;
	class Event_Actor;

	class NetThread: public Thread
	{
		typedef std::vector<std::pair<Event_Handler*, uint32> > HANDLER_VEC;
	public:
		NetThread(uint32 m);
		~NetThread();
		void RegisterHandler(Event_Handler* pHandler, uint32 events);
		uint32 GetLoad() const{return m_HandleCount;}
		void HandleRun();
		virtual void Stop(){m_IsExist = true;}
	protected:
		void OnQuit();
	private:
		HANDLER_VEC m_WaitList;
		FastMutex m_WaitMutex;
		Event_Actor* m_pEventActor;
		uint32 m_HandleCount;
		uint32 m_MaxHanleCount;
		bool m_IsExist;
	};
}

#endif