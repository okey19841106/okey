#include "PreCom.h"
#include "PacketList.h"
#include "Packet.h"

namespace okey
{
	PacketList::PacketList():m_head(NULL),m_back(NULL),m_count(0)
	{

	}

	PacketList::~PacketList()
	{

	}

	bool PacketList::Push_Head(PacketBase* pkt)
	{
		if (!pkt)
		{
			return false;
		}
		if (!m_head && !m_back)
		{
			m_head = m_back = pkt;
			m_head->m_next = m_back;
			m_back->m_prev = m_head;
		}
		pkt->m_next = m_head;
		m_head->m_prev = pkt;
		m_head = pkt;
		return true;

	}

	PacketBase* PacketList::Pop_Head()
	{
		if (!m_head)
		{
			return NULL;
		}
		PacketBase* pkt;
		pkt = m_head;
		m_head = m_head->m_next;
		if (m_head)
		{
			m_head->m_prev = NULL;
		}
		else
		{
			m_head = m_back =	NULL;
		}
		return pkt;
		 
	}

	bool PacketList::Push_Back(PacketBase* pkt)
	{
		if (!pkt)
		{
			return false;
		}
		if (!m_head && !m_back)
		{
			m_head = m_back = pkt;
			return true;
		}
		pkt->m_prev = m_back;
		m_back->m_next = pkt;
		m_back = pkt;
		return true;
	}

	PacketBase* PacketList::Pop_Back()
	{
		if (!m_back)
		{
			return NULL;
		}
		PacketBase* pkt;
		pkt = m_back;
		m_back = m_head->m_next;
		if (m_back)
		{
			m_back->m_next = NULL;
		}
		return pkt;
	}

	PacketBase* PacketList::GetNextPacket(PacketBase* pkt)
	{
		if (!pkt)
		{
			return m_head;
		}
		return pkt->m_next;
	}
	bool PacketListEx::Push_Head(PacketBase* pkt)
	{
		FastMutex::ScopedLock tmpMutex(m_Mutex);
		return PacketList::Push_Head(pkt);
	}
	PacketBase* PacketListEx::Pop_Head()
	{
		FastMutex::ScopedLock tmpMutex(m_Mutex);
		return PacketList::Pop_Head();
	}
	bool PacketListEx::Push_Back(PacketBase* pkt)
	{
		FastMutex::ScopedLock tmpMutex(m_Mutex);
		return PacketList::Push_Back(pkt);
	}
	PacketBase* PacketListEx::Pop_Back()
	{
		FastMutex::ScopedLock tmpMutex(m_Mutex);
		return PacketList::Pop_Head();
	}
	PacketBase* PacketListEx::GetNextPacket(PacketBase* pkt)
	{
		FastMutex::ScopedLock tmpMutex(m_Mutex);
		return PacketList::GetNextPacket(pkt);
	}
}