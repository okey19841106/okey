/********************************************************************
	created:	2015/01/28
	created:	14:48
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __IOCP_PROACTOR_H__
#define __IOCP_PROACTOR_H__

#include "EventActor.h"

namespace okey
{
	class Event_Handler;

	class IOCPProactor : public Event_Actor
	{
	public:
		IOCPProactor();
		virtual ~IOCPProactor();
		virtual bool Open(uint32 maxHandler, uint32 tickInter, uint32 numThread);
		virtual void Close();
		virtual bool RegisterHandler(Event_Handler* handler, uint32 events);
		virtual void RemoveHander(Event_Handler* handler, uint32 events);
		virtual bool HandleEvents(const TimeStamp& now);
		virtual int32 GetThreadNum() const;

	protected:
		bool m_bOpen;
		int32 _threadnum;
		HANDLE completion_port;
	};

}

#endif