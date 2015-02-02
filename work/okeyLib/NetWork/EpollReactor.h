/********************************************************************
	created:	2015/01/26
	created:	17:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __EPOLL_REACTOR_H__
#define __EPOLL_REACTOR_H__

#ifndef WINDOWS

#include "Events/EventActor.h"
#include <set>
#include <map>

namespace okey
{


	class EpollReactor : public Event_Actor
	{
	public:
		struct HandlerInfo
		{
			uint32 _events;
			int64 _timeout;
			Event_Handler* _handler;
			friend bool operator<(const HandlerInfo&, const HandlerInfo&);
		};

		const static uint32 MAX_WAIT_EVENT = 512;
		typedef std::multiset<HandlerInfo> HANDLER_QUEUE; //优先级队列。
		typedef std::map<SOCKET, HandlerInfo> HANDLER_MAP;

	public:
		EpollReactor();
		~EpollReactor();
		virtual bool Open(uint32 maxHandler, uint32 tickInter, uint32 numThread);
		virtual void Close();
		virtual bool RegisterHandler(Event_Handler* handler, uint32 events) ;
		virtual void RemoveHander(Event_Handler* handler, uint32 events);
		virtual bool HandleEvents(const TimeStamp& now);
		virtual uint32 GetNumOfHandler() const;
	private:
		uint32 MaskToEpollEvent(uint32 mask);
		void DispathNetEvents(Event_Handler* handler, uint32 events);
		int m_Epoll;
		struct epoll_event m_EpollBuf[MAX_WAIT_EVENT];
		HANDLER_QUEUE m_Queue;
		HANDLER_MAP m_Handlers;
		uint32 m_tickInter;
		uint32 m_MaxOfHandler;
		bool m_bOpen;
		bool m_RemoveFlag;
	};

	inline bool operator < (const EpollReactor::HandlerInfo& info1, const EpollReactor::HandlerInfo& info2)
	{
		return info1._timeout < info2._timeout;
	}
	
}

#endif

#endif