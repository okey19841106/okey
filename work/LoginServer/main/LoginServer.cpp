#include "PreCom.h"
#include "LoginServer.h"
#include "ServerPakcet/ServerPacketDef.h"


namespace okey
{
	LoginServer::LoginServer():m_LoginServerID(-1),m_GroupServerID(-1)
	{
		m_PeerIP = "127.0.0.1";
		m_PeerPort = 20000;
	}

	LoginServer::~LoginServer()
	{

	}

	void LoginServer::PeerConnect(int32 socketid)
	{
		printf("connect to others :%d\n",socketid);
		PacketConnect pkt;
		pkt.nServerType = Server_Login;
		pkt.nPort = m_PeerPort;
		pkt.nID = m_LoginServerID;
		memset(pkt.nIp,0,sizeof(pkt.nIp));
		strncpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
		PeerSend(socketid,&pkt);
	}

	void LoginServer::PeerAccept(int32 socketid)
	{
		printf("accept one connection:%d\n",socketid);
		PacketConnect pkt;
		pkt.nServerType = Server_Login;
		pkt.nPort = m_PeerPort;
		pkt.nID = m_LoginServerID;
		memset(pkt.nIp,0,sizeof(pkt.nIp));
		strncpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
		PeerSend(socketid,&pkt);
	}

	void LoginServer::PeerDisconnect(int32 sessionid)
	{

	}

	void LoginServer::RegPktHandler()
	{
		PeerBase::RegPktHandler();
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktConnectHandler,PacketConnect,PacketBase,LoginServer);
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktServerID,PacketServerID,PacketBase,LoginServer);
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktServerInfo,PacketServerInfo,PacketBase,LoginServer);
	}

	void LoginServer::Start()
	{
		Run();
	}

	bool LoginServer::Init(int argc, char *argv[])
	{
		for (int i = 0; i < argc; ++i)
		{
			if (strcmp(argv[i], "-ip") == 0)
			{
				m_PeerIP = argv[i+1];
			}
			else if (strcmp(argv[i], "port") == 0)
			{
				m_PeerPort = (int)atoi(argv[i+1]);
			}
		}
		PeerBase::Init(argc,argv);
 		while(true)
 		{
 			int32 nSocketId = PeerBase::PeerConnect("127.0.0.1", 5555);
 			if( nSocketId != -1)
 			{
 				ServerInfo* pServerInfo = new ServerInfo;
 				//m_GroupServerID = pkt->nID;
 				pServerInfo->nServerType = Server_Center;
 				pServerInfo->nServerIP = "127.0.0.1";
 				pServerInfo->nServerPort = 5555;
 				pServerInfo->nSocketID = nSocketId;
 				m_ServerManger.AddCenterServer(pServerInfo);
 				break;
 			}
 			printf("can not connect to CenterServer....\n");
 			Sleep(1000);
 		}
		PeerBase::PeerAccept();
		return true;
	}

	void LoginServer::PktConnectHandler(PacketConnect* pkt)
	{
		if (!pkt)
		{
			return;
		}
		if(pkt->nServerType == Server_Gate)
		{
			ServerInfo* pServerInfo = new ServerInfo;
			pServerInfo->nID = pkt->nID;
			pServerInfo->nServerType = Server_Gate;
			pServerInfo->nServerIP = pkt->nIp;
			pServerInfo->nServerPort = pkt->nPort;
			pServerInfo->nSocketID = pkt->GetSocketID();
			m_ServerManger.AddGateServer(pServerInfo);
		}
		else if(pkt->nServerType == Server_Login)
		{
			//跟login无连接。。。。
		}
		else if(pkt->nServerType == Server_Scene)
		{
			//不与scene连接。
		}
		else if(pkt->nServerType == Server_Chat)
		{
			ServerInfo* pServerInfo = new ServerInfo;
			pServerInfo->nID = pkt->nID;
			pServerInfo->nServerType = Server_Chat;
			pServerInfo->nServerIP = pkt->nIp;
			pServerInfo->nServerPort = pkt->nPort;
			pServerInfo->nSocketID = pkt->GetSocketID();
			m_ServerManger.AddChatServer(pServerInfo);
		}
// 		else if(pkt->nServerType == Server_Center)
// 		{
// 			ServerInfo* pServerInfo = new ServerInfo;
// 			m_GroupServerID = pkt->nID;
// 			pServerInfo->nServerType = Server_Center;
// 			pServerInfo->nServerIP = pkt->nIp;
// 			pServerInfo->nServerPort = pkt->nPort;
// 			pServerInfo->nSocketID = pkt->GetSocketID();
// 			m_ServerManger.AddCenterServer(pServerInfo);
// 		}
	}

	void LoginServer::PktServerID(PacketServerID* pkt)
	{
		if (!pkt)
		{
			return;
		}
		m_GroupServerID = pkt->nGroupID;
		printf("the LoginServer id:%d\n",pkt->nServerID);
		m_LoginServerID = pkt->nServerID;
	}

	void LoginServer::PktServerInfo(PacketServerInfo* pkt)
	{
		if (!pkt)
		{
			return;
		}
		if (pkt->nServerType == Server_Login)
		{
			return;
		}
		if(-1 == PeerBase::PeerConnect(pkt->nIp,pkt->nPort))
		{
			printf("can not connect to %d,%s,%d\n",pkt->nServerType,pkt->nIp,pkt->nPort);
			return;
		}
	}

	void LoginServer::Run()
	{
		while(true)
		{
			PeerRun();
		}
	}
}