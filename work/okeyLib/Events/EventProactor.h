/********************************************************************
	created:	2015/01/26
	created:	11:05
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __EVENT_PROACTOR_H__
#define __EVENT_PROACTOR_H__


namespace okey
{

	class Event_Handler;

	class Event_Proactor :public Event_Handler
	{
	public:
		Event_Proactor(){}
		virtual ~Event_Proactor(){}
		virtual bool Open(uint32 numThread) = 0;
		virtual void Open();
		virtual void Close() = 0;
		virtual bool RegisterHandler(Event_Handler* handler, uint32 events) = 0;
		virtual void RemoveHander(Event_Handler* handler, uint32 events) = 0;
		virtual bool HandleEvents(const TimeStamp& now) = 0;
	protected:
		virtual void HandleInput() {}
		virtual void HandleOutput() {}
		virtual void HandleException() {}
		virtual void HandleClose()	{}
	};
}

#endif