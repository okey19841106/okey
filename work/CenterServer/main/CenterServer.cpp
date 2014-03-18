#include "PreCom.h"
#include "CenterServer.h"
#include "ServerPakcet/ServerPacketDef.h"


namespace okey
{
	CenterServer::CenterServer():m_GroupServerID(0)
	{
		m_PeerIP = "127.0.0.1";
		m_PeerPort = 5555;
	}
	CenterServer::~CenterServer()
	{

	}
	void CenterServer::PeerConnect(int32 socketid)
	{
// 		printf("connect to others :%d\n",sessionid);
// 		PacketConnect pkt;
// 		pkt.flag = Server_Scene;
// 		pkt.nPort = m_PeerPort;
// 		memset(pkt.nIp,0,sizeof(pkt.nIp));
// 		strcpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
// 		PeerSend(sessionid,&pkt);
	}

	void CenterServer::PeerAccept(int32 socketid)
	{
		printf("accept one connection:%d\n",socketid);
		PacketConnect pkt;
		pkt.nServerType = Server_Center;
		pkt.nPort = m_PeerPort;
		memset(pkt.nIp,0,sizeof(pkt.nIp));
		strncpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
		PeerSend(socketid,&pkt);
	}

	void CenterServer::PeerDisconnect(int32 socketid)
	{

	}

	void CenterServer::RegPktHandler()
	{
		PeerBase::RegPktHandler();
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktConnectHandler,PacketConnect,PacketBase,CenterServer);
	}

	void CenterServer::Start()
	{
		Run();
	}

	bool CenterServer::Init(int argc, char *argv[])
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
		PeerBase::PeerAccept();
		return true;
	}

	void CenterServer::PktConnectHandler(PacketConnect* pkt)
	{
		if (!pkt)
		{
			return;
		}
		if(pkt->nServerType == Server_Gate)
		{
			printf("recive from gate.....\n");
			ServerInfo* pInfo = new ServerInfo;
			pInfo->nServerIP = pkt->nIp;
			pInfo->nServerPort = pkt->nPort;
			pInfo->nServerType = Server_Gate;
			pInfo->nSocketID = pkt->GetSocketID();
			int32 tID = m_ServerManger.AddGateServer(pInfo);
			PacketServerID ServerPkt;
			ServerPkt.nServerID = tID;
			ServerPkt.nGroupID = m_GroupServerID;
			PeerSend(pkt->GetSocketID(),&ServerPkt);
		}
		else if(pkt->nServerType == Server_Login)
		{
			printf("recive from Login.....\n");
			ServerInfo* pInfo = new ServerInfo;
			pInfo->nServerIP = pkt->nIp;
			pInfo->nServerPort = pkt->nPort;
			pInfo->nServerType = Server_Login;
			pInfo->nSocketID = pkt->GetSocketID();
			m_ServerManger.AddLoginServer(pInfo);
			PacketServerID ServerPkt;
			ServerPkt.nServerID = 0;
			ServerPkt.nGroupID = m_GroupServerID;
			PeerSend(pkt->GetSocketID(),&ServerPkt);
		}
		else if(pkt->nServerType == Server_Scene)
		{
			printf("recive from Scene.....\n");
			ServerInfo* pInfo = new ServerInfo;
			pInfo->nServerIP = pkt->nIp;
			pInfo->nServerPort = pkt->nPort;
			pInfo->nServerType = Server_Scene;
			pInfo->nSocketID = pkt->GetSocketID();
			int32 tID = m_ServerManger.AddSceneServer(pInfo);
			PacketServerID ServerPkt;
			ServerPkt.nServerID = tID;
			ServerPkt.nGroupID = m_GroupServerID;
			PeerSend(pkt->GetSocketID(),&ServerPkt);
		}
		else if(pkt->nServerType == Server_Chat)
		{
			printf("recive from Chat.....\n");
			ServerInfo* pInfo = new ServerInfo;
			pInfo->nServerIP = pkt->nIp;
			pInfo->nServerPort = pkt->nPort;
			pInfo->nServerType = Server_Gate;
			pInfo->nSocketID = pkt->GetSocketID();
			m_ServerManger.AddChatServer(pInfo);
			PacketServerID ServerPkt;
			ServerPkt.nServerID = 0;
			ServerPkt.nGroupID = m_GroupServerID;
			PeerSend(pkt->GetSocketID(),&ServerPkt);
		}
// 		else if(pkt->nServerType == Server_Center)
// 		{
// 			return;
// 		}
		//tell all the server info
		//gate.....
		PacketServerInfo infoPkt;
		for (int32 i = 0; i< MAX_GATE_SERVER_LIST; ++i)
		{
			ServerInfo* pServerInfo = m_ServerManger.GetGateServer(i);
			if (!pServerInfo || pkt->nServerType == Server_Gate)
			{
				continue;
			}
			infoPkt.nServerID = pServerInfo->nID;
			infoPkt.nServerType = Server_Gate;
			infoPkt.nPort = pServerInfo->nServerPort;
			memset(infoPkt.nIp,0,sizeof(infoPkt.nIp));
			strncpy(infoPkt.nIp,pServerInfo->nServerIP.c_str(),pServerInfo->nServerIP.length());
			PeerSend(pkt->GetSocketID(),&infoPkt);
		}
		for (int32 i = 0; i< MAX_SCENE_SERVER_LIST; ++i)
		{
			ServerInfo* pServerInfo = m_ServerManger.GetSceneServer(i);
			if (!pServerInfo || pkt->nServerType == Server_Scene)
			{
				continue;
			}
			infoPkt.nServerID = pServerInfo->nID;
			infoPkt.nServerType = Server_Scene;
			infoPkt.nPort = pServerInfo->nServerPort;
			memset(infoPkt.nIp,0,sizeof(infoPkt.nIp));
			strncpy(infoPkt.nIp,pServerInfo->nServerIP.c_str(),pServerInfo->nServerIP.length());
			PeerSend(pkt->GetSocketID(),&infoPkt);
		}
		ServerInfo* pLoginInfo = m_ServerManger.GetLoginServer();
		if (pLoginInfo && pkt->nServerType != Server_Login)
		{
			infoPkt.nServerID = pLoginInfo->nID;
			infoPkt.nServerType = Server_Login;
			infoPkt.nPort = pLoginInfo->nServerPort;
			memset(infoPkt.nIp,0,sizeof(infoPkt.nIp));
			strncpy(infoPkt.nIp,pLoginInfo->nServerIP.c_str(),pLoginInfo->nServerIP.length());
			PeerSend(pkt->GetSocketID(),&infoPkt);
		}
		
		ServerInfo* pChatInfo = m_ServerManger.GetChatServer();
		if (pChatInfo && pkt->nServerType != Server_Chat)
		{
			infoPkt.nServerID = pChatInfo->nID;
			infoPkt.nServerType = Server_Chat;
			infoPkt.nPort = pChatInfo->nServerPort;
			memset(infoPkt.nIp,0,sizeof(infoPkt.nIp));
			strncpy(infoPkt.nIp,pChatInfo->nServerIP.c_str(),pChatInfo->nServerIP.length());
			PeerSend(pkt->GetSocketID(),&infoPkt);
		}
		
	}

	void CenterServer::Run()
	{
		while(true)
		{
			PeerRun();
		}
	}
}