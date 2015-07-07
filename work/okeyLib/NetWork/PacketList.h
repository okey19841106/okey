/********************************************************************
	created:	2015/07/07
	created:	10:59
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __PACKET_LIST_H__
#define __PACKET_LIST_H__

#include "Types.h"
#include "Thread/Mutex.h"

namespace okey
{
	class PacketBase;

	class PacketList
	{
	public:
		PacketList();
		virtual ~PacketList();
		virtual bool Push_Head(PacketBase* pkt);
		virtual PacketBase* Pop_Head();
		virtual bool Push_Back(PacketBase* pkt);
		virtual PacketBase* Pop_Back();
		virtual PacketBase* GetNextPacket(PacketBase* pkt);
		int32 GetPacketCount()const{return m_count;}
	protected:
	private:
		PacketBase* m_head;
		PacketBase* m_back;
		int32 m_count;
	};

	class PacketListEx: public PacketList
	{
	public:
		PacketListEx(){}
		virtual ~PacketListEx(){}
		virtual bool Push_Head(PacketBase* pkt);
		virtual PacketBase* Pop_Head();
		virtual bool Push_Back(PacketBase* pkt);
		virtual PacketBase* Pop_Back();
		virtual PacketBase* GetNextPacket(PacketBase* pkt);
	private:
		FastMutex m_Mutex;
	};


}


#endif