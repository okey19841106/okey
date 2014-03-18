/********************************************************************
	created:	2013/06/24
	created:	24-6-2013   23:05
	author:		okey
	
	purpose:	ServerInfo and Manager..
*********************************************************************/

#ifndef __SERVER_MANAGER_H__
#define __SERVER_MANAGER_H__

#include <string>
#include <map>

namespace okey
{
	enum
	{
		Server_Gate,
		Server_Login,
		Server_Scene,
		Server_Chat,
		Server_Center,
	};

	struct ServerInfo
	{
		int32 nID;
		int32 nServerType;
		int32 nSocketID;
		int32 nServerPort;
		std::string nServerIP;
		ServerInfo()
		{
			nID = -1;
			nServerType = -1;
			nSocketID = -1;
			nServerType = -1;
		}
	};

#define MAX_SCENE_SERVER_LIST 16
#define MAX_GATE_SERVER_LIST 16

	class ServerManager
	{
	public:
		ServerManager();
		~ServerManager();

		int32 GetGroupID()const{return m_GroupID;}
		void SetGroupID(int32 nGourpID){m_GroupID = nGourpID;}
		int32 AddGateServer(ServerInfo* pServer);
		int32 AddSceneServer(ServerInfo* pServer);
		void AddCenterServer(ServerInfo* pServer){m_CenterServer = pServer;}
		void AddLoginServer(ServerInfo* pServer){m_LoginServer = pServer;}
		void AddChatServer(ServerInfo* pServer){m_ChatServer = pServer;}
		ServerInfo* GetGateServer(int32 nGateID);
		ServerInfo* GetSceneServer(int32 nSceneID);
		ServerInfo* GetCenterServer()const{return m_CenterServer;}
		ServerInfo* GetChatServer()const{return m_ChatServer;}
		ServerInfo* GetLoginServer()const{return m_LoginServer;}
	protected:
		int32 m_GroupID; //×éºÅ¡£
		std::map<int32, ServerInfo*> m_GateServers;
		ServerInfo* m_CenterServer;
		std::map<int32, ServerInfo*> m_SceneServers;
		ServerInfo* m_ChatServer;
		ServerInfo* m_LoginServer;
	};
}


#endif