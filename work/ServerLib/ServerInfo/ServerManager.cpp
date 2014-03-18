#include "PreCom.h"
#include "ServerManager.h"


namespace okey
{
	ServerManager::ServerManager():m_CenterServer(NULL),m_LoginServer(NULL),m_ChatServer(NULL)
	{

	}

	ServerManager::~ServerManager()
	{
		if (m_CenterServer)
		{
			delete m_CenterServer;
			m_CenterServer = NULL;
		}
		if (m_ChatServer)
		{
			delete m_ChatServer;
			m_ChatServer = NULL;
		}
		if (m_LoginServer)
		{
			delete m_LoginServer;
			m_LoginServer = NULL;
		}
		for (int32 i = 0; i < MAX_SCENE_SERVER_LIST; ++i)
		{
			std::map<int32, ServerInfo*>::iterator itr = m_SceneServers.begin();
			for(; itr != m_SceneServers.end();++itr)
			{
				if (itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
			}
		}
		for (int32 i = 0; i < MAX_GATE_SERVER_LIST; ++i)
		{
			std::map<int32, ServerInfo*>::iterator itr = m_GateServers.begin();
			for(; itr != m_GateServers.end();++itr)
			{
				if (itr->second)
				{
					delete itr->second;
					itr->second = NULL;
				}
			}
		}
	}

	int32 ServerManager::AddGateServer(ServerInfo* pServer)
	{
		int32 tID = -1;
		if (pServer->nID != -1)
		{
			m_GateServers.insert(std::make_pair<int32, ServerInfo*>(pServer->nID,pServer));
			tID = pServer->nID;
		}
		else
		{
			std::map<int32, ServerInfo*>::iterator itr = m_GateServers.begin();
			for (;itr!=m_GateServers.end();++itr)
			{
				if (itr->first > tID)
				{
					tID = itr->first;
				}
			}
			++tID;
			pServer->nID = tID ;
			m_GateServers.insert(std::make_pair<int32, ServerInfo*>(pServer->nID,pServer));
		}
		return tID;
	}

	int32 ServerManager::AddSceneServer(ServerInfo* pServer)
	{		
		int32 tID = -1;
		if (pServer->nID != -1)
		{
			m_SceneServers.insert(std::make_pair<int32, ServerInfo*>(pServer->nID,pServer));
			tID = pServer->nID;
		}
		else
		{
			std::map<int32, ServerInfo*>::iterator itr = m_SceneServers.begin();
			for (;itr!=m_SceneServers.end();++itr)
			{
				if (itr->first > tID)
				{
					tID = itr->first;
				}
			}
			++tID;
			pServer->nID = tID ;
			m_SceneServers.insert(std::make_pair<int32, ServerInfo*>(pServer->nID,pServer));
		}
		return tID;
	}

	ServerInfo* ServerManager::GetGateServer(int32 nGateID)
	{
		std::map<int32, ServerInfo*>::iterator itr = m_GateServers.find(nGateID);
		if (itr == m_GateServers.end())
		{
			return NULL;
		}
		return itr->second;
	}

	ServerInfo* ServerManager::GetSceneServer(int32 nSceneID)
	{
		std::map<int32, ServerInfo*>::iterator itr = m_SceneServers.find(nSceneID);
		if (itr == m_SceneServers.end())
		{
			return NULL;
		}
		return itr->second;
	}
}