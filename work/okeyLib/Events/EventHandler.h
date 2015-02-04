/********************************************************************
	created:	2015/01/26
	created:	10:06
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "TimeStamp.h"

namespace okey
{
	class Event_Reactor;

	class Event_Handler
	{
	public:
		enum NetEventMask
		{
			Event_In = 1 << 0,
			Event_Out = 1 << 1,
			Event_Exception = 1 << 2,
			Event_IO = Event_In | Event_Out | Event_Exception,
// 			Event_Tick = 1 << 3,
// 			Event_All = Event_IO | Event_Tick,
		};
	public:
		Event_Handler():m_pReactor(NULL),m_uMask(0),m_iTimeOut(0){}
		virtual ~Event_Handler(){}
		virtual void* GetHandle(){return NULL;}
		virtual void SetHandle(const void* pHandle){}
		virtual void HandleInput() = 0;
		virtual void HandleOutput() = 0;
		virtual void HandleException() = 0;
		virtual void HandleTick(const TimeStamp& now){}
		virtual void HandleClose() = 0;
		void SetReacotr(Event_Reactor* pReactor){m_pReactor = pReactor;}
		Event_Reactor* GetReactor(){return m_pReactor;}

		void SetEventMask(uint32 mask){m_uMask = mask;}
		uint32 GetEventMask()const {return m_uMask;}
		int64 GetTimeout()const {return m_iTimeOut;}
		void SetTimeout(int64 timeout){m_iTimeOut = timeout;}
	protected:
		Event_Reactor* m_pReactor;
		uint32 m_uMask;
		int64 m_iTimeOut;
	};
}

#endif