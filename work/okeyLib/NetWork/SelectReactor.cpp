#include "PreCom.h"
#include "SelectReactor.h"
#include "Events/EventHandler.h"
#include "SessionBase.h"
#include "Socket.h"

namespace okey
{
	SelectReactor::SelectReactor():_maxOfHandler(0),_bOpened(false),_removeFlag(false)
	{
	}

	SelectReactor::~SelectReactor()
	{
	}

	bool SelectReactor::Open(uint32 maxHandler, uint32 numThread)
	{
		if (_bOpened)
		{
			Close();
		}
		FD_ZERO(&_inSet);
		FD_ZERO(&_outSet);
		FD_ZERO(&_exceptSet);
		if (maxHandler > FD_SETSIZE)
		{
			maxHandler = FD_SETSIZE;
		}
		_maxOfHandler = maxHandler;
		_bOpened = true;
		return true;
	}

	void SelectReactor::Close()
	{
		if (!_bOpened)
		{
			return;
		}
		_bOpened = false;
		_removeFlag = false;
		_maxOfHandler = 0;
		HANDLE_MAP::iterator itr = _handlers.begin();
		for (; itr != _handlers.end(); ++itr)
		{
			itr->second->HandleClose();
		}
		_handlers.clear();
	}

	bool SelectReactor::RegisterHandler(Event_Handler* handler, uint32 events)
	{
		events &= Event_Handler::Event_All;
		if (!_bOpened || NULL == handler || 0 == events)
		{
			return false;
		}
		SOCKET socket = ((SessionBase*)handler)->GetSocket();
		if (socket < 0)
		{
			return false;
		}
		HANDLE_MAP::iterator itr = _handlers.find(socket);
		if (itr == _handlers.end())
		{
			if (_handlers.size() >= _maxOfHandler)
			{
				return false;
			}
			handler->SetEventMask(0);
			handler->SetAcotr(this);
			handler->SetTimeout(0);
		}
		uint32 oldevents = handler->GetEventMask();
		events &= ~oldevents;
		handler->SetEventMask(oldevents |= events);
		if (events & Event_Handler::Event_In)
		{
			FD_SET(socket, &_inSet);
		}
		if (events & Event_Handler::Event_Out)
		{
			FD_SET(socket, &_outSet);
		}
		if (events & Event_Handler::Event_Exception)
		{
			FD_SET(socket, &_exceptSet);
		}
		return true;
	}

	void SelectReactor::RemoveHander(Event_Handler* handler, uint32 events)
	{
		events &= Event_Handler::Event_All;
		if (!_bOpened || NULL == handler || 0 == events)
		{
			return;
		}
		SOCKET socket = ((SessionBase*)handler)->GetSocket();
		if (socket < 0)
		{
			return ;
		}
		HANDLE_MAP::iterator itr = _handlers.find(socket);
		if (itr == _handlers.end())
		{
			return;
		}
		uint32 oldevents = handler->GetEventMask();
		events &= ~oldevents;
		if (events & Event_Handler::Event_In)
		{
			FD_CLR(socket, &_inSet);
		}
		if (events & Event_Handler::Event_Out)
		{
			FD_CLR(socket, &_outSet);
		}
		if (events & Event_Handler::Event_Exception)
		{
			FD_CLR(socket, &_exceptSet);
		}
		handler->SetEventMask(oldevents & ~events);
		if (handler->GetEventMask() == 0)
		{
			_removeFlag = true;
			_handlers.erase(itr);
			handler->HandleClose();
		}
	}

	bool SelectReactor::HandleEvents()
	{
		if (!_bOpened || 0 == _handlers.size())
		{
			return false;
		}
		int maxFd = 1;
#ifndef _WINDOWS
		HANDLE_MAP::iterator itr = _handlers.end();
		maxFd = (--itr)->first + 1;
#endif
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		fd_set inset = _inSet;
		fd_set outset = _outSet;
		fd_set excepset = _exceptSet;
		int ret = 0;
		while(true)
		{
			ret = select(maxFd, &inset,&outset,&excepset,&timeout);
			if (ret < 0)
			{
				if (SOCKET_EINTR == Socket::GetSysError()) //ÖÕ¶Ë×èÈû¡£¡£
				{
					continue;
				}
				return false;
			}
			break;
		}
		bool bEvent = false;
		for(HANDLE_MAP::iterator nIter = _handlers.begin(), iter; nIter != _handlers.end();)
		{
			Event_Handler* handler = iter->second;
			SOCKET socket = iter->first;
			_removeFlag = false;
			if (!_removeFlag && (handler->GetEventMask() & Event_Handler::Event_In) && FD_ISSET(socket, &inset))
			{
				handler->HandleInput();
			}
			if (!_removeFlag && (handler->GetEventMask() & Event_Handler::Event_Out) && FD_ISSET(socket, &outset))
			{
				handler->HandleOutput();
			}
			if (!_removeFlag && (handler->GetEventMask() & Event_Handler::Event_Exception) && FD_ISSET(socket, &excepset))
			{
				handler->HandleException();
			}
		}
	}

	uint32 SelectReactor::GetNumOfHandler() const
	{
		return (uint32)_handlers.size();
	}
}