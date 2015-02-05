#include "PreCom.h"
#include "EpollReactor.h"
#ifndef WINDOWS

#include "Events/EventHandler.h"
#include <vector>

namespace okey
{
	EpollReactor::EpollReactor()
	{
		m_Epoll = 0;
		uint32 m_MaxOfHandler = 0;
		bool m_bOpen = false;
		bool m_RemvoeFlag = false;
	}
	EpollReactor::~EpollReactor()
	{
		Close();
	}
	bool EpollReactor::Open(uint32 maxHandler, uint32 numThread)
	{
		if (m_bOpen)
		{
			return false;
		}
		m_MaxOfHandler = maxHandler;
		m_Epoll = epoll_create((int)m_MaxOfHandler);
		if (m_Epoll < 0)
		{
			return false;
		}
		m_bOpen = true;
		m_RemvoeFlag = false;
		return true;
	}
	void EpollReactor::Close()
	{
		if (!m_bOpen)
		{
			return;
		}
		m_bOpen = false;
		m_RemvoeFlag = false;
		close(m_Epoll);
		m_Epoll = 0;
		m_MaxOfHandler = 0;
		//m_Queue.clear();
		for (HANDLER_MAP::iterator itr = m_Handlers.begin(); itr != m_Handlers.end(); ++itr)
		{
			itr->second._handler->HandleClose();
		}
		m_Handlers.clear();
	}
	bool EpollReactor::RegisterHandler(Event_Handler* handler, uint32 events)
	{
		events &= Event_Handler::Event_All;
		if (!m_bOpen || !handler || events == 0)
		{
			return false;
		}
		SessionBase* s = (SessionBase*)handler->GetHandle();
		SOCKET socket = s->GetSocket();
		if (socket < 0)
		{
			return false;
		}
		HANDLER_MAP::iterator itr = m_Handlers.find(socket);
		if (itr == m_Handlers.end())
		{
			if (m_Handlers.size() >= m_MaxOfHandler)
			{
				return false;
			}
			HandlerInfo info;
			info._events = 0;
			info._handler = handler;
			info._timeout = 0;
			handler->SetReacotr(this);
			m_Handlers.insert(std::make_pair(socket,info));
		}
		HandlerInfo& info = m_Handlers[socket];
		uint32 oldEvents = info._events;
		info._events |= events;
		if (oldEvents == info._events)
		{
			return true;
		}
		int32 opt = 0;
		if ((oldEvents & Event_Handler::Event_IO) == 0 && (info._events & Event_Handler::Event_IO) != 0)
		{
			opt = EPOLL_CTL_ADD;
		}
		else if ((oldEvents & Event_Handler::Event_IO) != (info._events & Event_Handler::Event_IO))
		{
			opt = EPOLL_CTL_MOD;
		}
		if (opt != 0)
		{
			struct epoll_event epollevent;
			epollevent.data.ptr = handler;
			epollevent.events = MaskToEpollEvent(info._events);
			if (epollevent.events != 0)
			{
				epoll_ctl(m_Epoll, opt, socket, & epollevent);
			}
		}
// 		if ((oldEvents & Event_Handler::Event_Tick) == 0 && (info._events & Event_Handler::Event_Tick) != 0)
// 		{
// 			m_Queue.insert(info);
// 		}
		return true;
	}

	void EpollReactor::RemoveHander(Event_Handler* handler, uint32 events)
	{
		events &= Event_Handler::Event_All;
		if (!m_bOpen || !handler || events == 0)
		{
			return ;
		}
		SessionBase* s = (SessionBase*)handler->GetHandle();
		SOCKET socket = s->GetSocket();
		if (socket < 0)
		{
			return ;
		}
		HANDLER_MAP::iterator itr = m_Handlers.find(socket);
		if (itr == m_Handlers.end())
		{
			return;
		}
		HandlerInfo& info = itr->second;
		uint32 oldEvents = info._events;
		info._events = oldEvents & (~events);
		if (oldEvents == info._events)
		{
			return;
		}
// 		if ((oldEvents & Event_Handler::Event_Tick) != 0 && (info._events & Event_Handler::Event_Tick) == 0)
// 		{
// 			for(HANDLER_QUEUE::iterator low = m_Queue.lower_bound(info), high = m_Queue.upper_bound(info); low != high; ++low)
// 			{
// 				if (low->_handler == handler)
// 				{
// 					m_Queue.erase(low);
// 				}
// 			}
// 		}
		int32 opt = 0;
		if ((oldEvents & Event_Handler::Event_IO) != 0 && (info._events & Event_Handler::Event_IO) == 0)
		{
			opt = EPOLL_CTL_DEL;
		}
		else if ((oldEvents & Event_Handler::Event_IO) != (info._events & Event_Handler::Event_IO))
		{
			opt = EPOLL_CTL_MOD;
		}
		if (opt != 0)
		{
			struct epoll_event epollevent;
			epollevent.data.ptr = handler;
			epollevent.events = MaskToEpollEvent(info._events);
			if (epollevent.events != 0)
			{
				epoll_ctl(m_Epoll, opt, socket, & epollevent);
			}
		}
		if (info._events = 0)
		{
			m_RemvoeFlag = true;
			info._handler->HandleClose();
			m_Handlers.erase(itr);
		}
	}
	bool EpollReactor::HandleEvents()
	{
		if (!m_bOpen)
		{
			return false;
		}
		if (0 == m_Handlers.size())
		{
			return 0;
		}
// 		std::vector<HandlerInfo> list;
// 		for(HANDLER_QUEUE::iterator nIter = m_Queue.begin(), iter; nIter != m_Queue.end();)
// 		{
// 			iter = nIter++;
// 			if (iter->_timeout < now.MilliSecond())
// 			{
// 				m_RemvoeFlag = false;
// 				iter->_handler->HandleTick(now);
// 				if (!m_RemvoeFlag)
// 				{
// 					if (iter->_events & Event_Handler::Event_Tick)
// 					{
// 						list.push_back(*iter);
// 						m_Queue.erase(iter);
// 					}
// 				}
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 		for(std::vector<HandlerInfo>::iterator itr = list.begin(); itr != list.end(); ++itr)
// 		{
// 			itr->_timeout = now.MilliSecond() + m_tickInter;
// 			m_Queue.insert(*itr);
// 		}
// 		list.clear();
		int32 ret = 0;
		while(true)
		{
			ret = epoll_wait(m_Epoll,m_EpollBuf,MAX_WAIT_EVENT,0);
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
		for(int32 i = 0; i < ret; ++i)
		{
			Event_Handler* handler = (Event_Handler*)m_EpollBuf[i].data.ptr;
			DispathNetEvents(handler, m_EpollBuf[i].events);
		}
		return ret > 0;
	}
	uint32 EpollReactor::GetNumOfHandler() const
	{
		return (uint32)m_Handlers.size();
	}

	uint32 EpollReactor::MaskToEpollEvent(uint32 mask)
	{
		uint32 events = 0;
		events = EPOLLERR | EPOLLHUP | EPOLLET;
		if (mask & Event_Handler::Event_In)
		{
			events |= EPOLLIN;
		}
		if (mask & Event_Handler::Event_Out)
		{
			events |= EPOLLOUT;
		}
		if (mask & Event_Handler::Event_Exception)
		{
			events != EPOLLPRI;
		}
		return events;

	}

	void EpollReactor::DispathNetEvents(Event_Handler* handler, uint32 events)
	{
		m_RemvoeFlag = false;
		if (!m_RemoveFlag && ((events & EPOLLIN)|| (events & EPOLLERR)))
		{
			handler->HandleInput();
		}
		if (!m_RemoveFlag && ((events & EPOLLOUT)|| (events & EPOLLERR)))
		{
			handler->HandleOutput();
		}
		if (!m_RemoveFlag && (events & EPOLLPRI))
		{
			handler->HandleException();
		}
	}
}

#endif
