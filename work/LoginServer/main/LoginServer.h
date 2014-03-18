/********************************************************************
	created:	2013/06/22
	created:	22-6-2013   23:33
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_LOGIN_SERVER_H__
#define __OKEY_LOGIN_SERVER_H__

#include "Singleton.h"
#include "Thread/Thread.h"
#include "ServerInfo/ServerManager.h"
#include "NetWork/PeerBase.h"

namespace okey
{

	class PacketConnect;
	class PacketServerID;
	class PacketServerInfo;

	class LoginServer: public PeerBase, public Singleton<LoginServer, Mutex>
	{
	public:
		LoginServer();
		~LoginServer();
		bool Init(int argc, char *argv[]);
		void Start();
		void Run();

		virtual void PeerConnect(int32 socketid);
		virtual void PeerAccept(int32 socketid);
		virtual void PeerDisconnect(int32 socketid);
		virtual void RegPktHandler();
		

		//pkt....
		void PktConnectHandler(PacketConnect* pkt);
		void PktServerID(PacketServerID* pkt);
		void PktServerInfo(PacketServerInfo* pkt);

	protected:
		int32 m_GroupServerID;
		int32 m_LoginServerID;
		ServerManager m_ServerManger;
	};
}




#endif