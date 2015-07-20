/********************************************************************
	created:	2015/07/20
	created:	14:49
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NETWORK_SELECT_REACTOR_H__
#define __NETWORK_SELECT_REACTOR_H__

#include "Events/EventActor.h"
#include <map>

namespace okey
{
	class Event_Handler;

	class SelectReactor: public Event_Actor
	{
	public:
		typedef std::map<SOCKET, Event_Handler*> HANDLE_MAP;

		SelectReactor();
		~SelectReactor();

		virtual bool Open(uint32 maxHandler, uint32 numThread);
		virtual void Close();
		virtual bool RegisterHandler(Event_Handler* handler, uint32 events);
		virtual void RemoveHander(Event_Handler* handler, uint32 events);
		virtual bool HandleEvents();
		virtual uint32 GetNumOfHandler() const;
	private:
		HANDLE_MAP _handlers;
		fd_set _inSet;
		fd_set _outSet;
		fd_set _exceptSet;
		uint32 _maxOfHandler;
		bool _bOpened;
		bool _removeFlag;
	};
}

#endif