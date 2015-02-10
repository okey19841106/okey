#include "PreCom.h"
#include "NetThread.h"
#include "Events/EventActor.h"
#include "Events/EventHandler.h"
#ifdef WINDOWS
#include "IOCPProactor.h"
#else
#include "EpollReactor.h"
#endif


namespace okey
{
	NetThread::NetThread(uint32 m):m_MaxHanleCount(m),m_HandleCount(0),m_IsExist(true)
	{
#if WINDOWS
		//m_pEventActor = new IOCPProactor;
#else
		m_pEventActor = new EpollReactor;
		m_pEventActor->Open(m_MaxHanleCount,0);
#endif

	}

	NetThread::~NetThread()
	{

	}

	void NetThread::RegisterHandler(Event_Handler* pHandler, uint32 events)
	{
		if (!pHandler)
		{
			return;
		}
		FastMutex::ScopedLock lock(m_WaitMutex);
		m_WaitList.push_back(std::make_pair(pHandler, events));
	}
	
	void NetThread::HandleRun()
	{
		while(!m_IsExist)
		{
			HANDLER_VEC newHandlers;
			{
				FastMutex::ScopedLock lock(m_WaitMutex);
				newHandlers.assign(m_WaitList.begin(), m_WaitList.end());
				m_WaitList.clear();
			}
			for (HANDLER_VEC::iterator itr = newHandlers.begin(); itr != newHandlers.end(); ++itr)
			{
				if (!m_pEventActor->RegisterHandler(itr->first, itr->second))
				{
					//log error...
					itr->first->HandleClose();
				}
			}
			newHandlers.clear();
			m_HandleCount = m_pEventActor->GetNumOfHandler();
			m_pEventActor->HandleEvents();
		}
		OnQuit();
	}

	void NetThread::OnQuit()
	{
		{
			FastMutex::ScopedLock lock(m_WaitMutex);
			for(HANDLER_VEC::iterator itr = m_WaitList.begin(); itr != m_WaitList.end(); ++ itr)
			{
				itr->first->HandleClose();
			}
			m_WaitList.clear();
		}
		m_pEventActor->Close();
	}

#ifdef WINDOWS
	void NetThread::SetEventAcotr(Event_Actor* pEventActor)
	{
		m_pEventActor = pEventActor;
	}
#endif
}