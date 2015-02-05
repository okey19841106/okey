#include "PreCom.h"
#include "NetThread.h"


namespace okey
{
	NetThread::NetThread(uint32 m):m_MaxHanleCount(m)
	{

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
	
}