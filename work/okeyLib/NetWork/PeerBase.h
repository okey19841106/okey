/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   16:54
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_PEER_BASE_H__
#define __OKEY_PEER_BASE_H__


#include "Types.h"
#include <vector>
#include "PacketProcess.h"

namespace okey
{

	class PacketProcessEx;
	class NetManagerBase;
	class Thread;

	class PacketText;
	

	class PeerBase
	{
	public:
		PeerBase();
		virtual ~PeerBase();

		virtual bool Init(int argc, char *argv[]);

		void OnPeerConnect(int32 socketid)
		{
			PeerConnect(socketid);
		}
		void OnPeerAccept(int32 socketid)
		{
			PeerAccept(socketid);
		}
		void OnPeerDisconnect(int32 socketid)
		{
			PeerDisconnect(socketid);
		}
		virtual void PeerConnect(int32 socketid){}
		virtual void PeerAccept(int32 socketid){}
		virtual void PeerDisconnect(int32 socketid){}
		virtual int32 PeerConnect(const char* ipaddress, int32 port);
		virtual bool PeerAccept(const char* ipaddress, int32 port);
		virtual bool PeerAccept();
		void PeerRun();
		void DoPeerRun();
		virtual void RegPktHandler();
		void DoPeerSend();
		bool PeerSend(int32 socketid, PacketBase* pkt);
		bool PeerProcPacket();



		//包处理

		void PktTestHandler(PacketText* pkt);
		



	protected:
		std::string m_PeerIP;
		int32 m_PeerPort;
		PacketListEx m_PktSendList; //发包处理
		PacketListEx m_PktFailedList; //发包处理
		PacketProcessEx* m_PeerPocPacket; //收包处理
		NetManagerBase* m_NetManger;
		std::vector<Thread*> m_Threads;
		int32 m_LastFrameTime;
		
	};


}

#endif