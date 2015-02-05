/********************************************************************
	created:	2015/01/26
	created:	10:59
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __EVENT_REACTOR_H__
#define __EVENT_REACTOR_H__

#include "TimeStamp.h"

namespace okey
{
	class Event_Handler;

	class Event_Actor
	{
	public:
		Event_Actor(){}
		virtual ~Event_Actor(){}

		virtual bool Open(uint32 maxHandler, uint32 numThread)= 0;
		virtual void Close() = 0;
		virtual bool RegisterHandler(Event_Handler* handler, uint32 events) = 0;
		virtual void RemoveHander(Event_Handler* handler, uint32 events) = 0;
		virtual bool HandleEvents() = 0;
		virtual uint32 GetNumOfHandler() const = 0;
	
	};
}

#endif