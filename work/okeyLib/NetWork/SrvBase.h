/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   16:54
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __OKEY_SRV_BASE_H__
#define __OKEY_SRV_BASE_H__


#include "Types.h"
#include <vector>
#include "PacketProcess.h"

namespace okey
{

	class PacketProcessEx;
	class NetManagerBase;
	class Thread;

	class PacketText;


	class SrvBase
	{
	public:
		SrvBase();
		virtual ~SrvBase();

		bool Init(int argc, char *argv[]);

		void OnSrvConnect(int32 sessionid)
		{
			SrvConnect(sessionid);
		}
		void OnSrvAccept(int32 sessionid)
		{
			SrvAccept(sessionid);
		}
		void OnSrvDisconnect(int32 sessionid)
		{
			SrvDisconnect(sessionid);
		}
		virtual void SrvConnect(int32 sessionid){}
		virtual void SrvAccept(int32 sessionid){}
		virtual void SrvDisconnect(int32 sessionid){}
		virtual bool SrvConnect(const char* ipaddress, int32 port);
		virtual bool SrvAccecpt(const char* ipaddress, int32 port);
		void SrvRun();
		void DoSrvRun();
		virtual void RegPktHandler();
		void DoSrvSend();
		bool SrvSend(int32 socketid, PacketBase* pkt);
		bool SrvProcPacket();
		bool SrvAccept();



		//包处理

		/*void PktTestHandler(PacketText* pkt);*/




	protected:
		std::string m_SrvIP;
		int32 m_SrvPort;
		PacketListEx m_PktSendList; //发包处理
		PacketListEx m_PktFailedList; //发包处理
		PacketProcessEx* m_SrvPocPacket; //收包处理
		NetManagerBase* m_NetManger;
		std::vector<Thread*> m_Threads;
		int32 m_LastFrameTime;
		
	};


#endif
}