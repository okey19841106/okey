#include "PreCom.h"
#include "SceneServer.h"
#include "ServerPakcet/ServerPacketDef.h"


namespace okey
{
	SceneServer::SceneServer():m_SceneServerID(-1),m_GroupServerID(-1)
	{
		m_PeerIP = "127.0.0.1";
		m_PeerPort = 30000;
	}

	SceneServer::~SceneServer()
	{

	}

	void SceneServer::PeerConnect(int32 socketid)
	{
		printf("connect to others :%d\n",socketid);
		PacketConnect pkt;
		pkt.nServerType = Server_Scene;
		pkt.nPort = m_PeerPort;
		pkt.nID = m_SceneServerID;
		memset(pkt.nIp,0,sizeof(pkt.nIp));
		strncpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
		PeerSend(socketid,&pkt);
	}

	void SceneServer::PeerAccept(int32 socketid)
	{
		printf("accept one connection:%d\n",socketid);
		PacketConnect pkt;
		pkt.nServerType = Server_Scene;
		pkt.nPort = m_PeerPort;
		pkt.nID = m_SceneServerID;
		memset(pkt.nIp,0,sizeof(pkt.nIp));
		strncpy(pkt.nIp,m_PeerIP.c_str(),m_PeerIP.length());
		PeerSend(socketid,&pkt);
	}

	void SceneServer::PeerDisconnect(int32 sessionid)
	{

	}

	void SceneServer::RegPktHandler()
	{
		PeerBase::RegPktHandler();
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktConnectHandler,PacketConnect,PacketBase,SceneServer);
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktServerID,PacketServerID,PacketBase,SceneServer);
		REG_PACKET_IMPL_HANDLER(m_PeerPocPacket,PktServerInfo,PacketServerInfo,PacketBase,SceneServer);
	}

	void SceneServer::Start()
	{
		Run();
	}

	bool SceneServer::Init(int argc, char *argv[])
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

	void SceneServer::PktConnectHandler(PacketConnect* pkt)
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
			//scene与scene应该无连接。要不就太乱了。
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

	void SceneServer::PktServerID(PacketServerID* pkt)
	{
		if (!pkt)
		{
			return;
		}
		m_GroupServerID = pkt->nGroupID;
		printf("the sceneserver id:%d\n",pkt->nServerID);
		m_SceneServerID = pkt->nServerID;
	}

	void SceneServer::PktServerInfo(PacketServerInfo* pkt)
	{
		if (!pkt)
		{
			return;
		}
		if (pkt->nServerType == Server_Scene)
		{
			return;
		}
		if(PeerBase::PeerConnect(pkt->nIp,pkt->nPort) == -1)
		{
			printf("can not connect to %d,%s,%d\n",pkt->nServerType,pkt->nIp,pkt->nPort);
			return;
		}
	}

	void SceneServer::Run()
	{
		while(true)
		{
			PeerRun();
		}
	}
}