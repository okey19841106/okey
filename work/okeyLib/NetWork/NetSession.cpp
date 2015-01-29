#include "PreCom.h"
#include "NetSession.h"

namespace okey
{

	NetSession::NetSession():m_State(e_DisConnected),m_Type(e_Active),m_ID(0),m_pNetService(NULL)
	{

	}

	NetSession::~NetSession()
	{
		m_State = e_DisConnected;
		m_Socket.Close();
	}

	void NetSession::Disconnect()
	{
		if (m_State == e_DisConnected)
		{
			return;
		}
		m_State = e_DisConnected;
		//log...
	}

	SocketAddr NetSession::GetPeerAddr() const
	{
		SocketAddr addr;
		m_Socket.GetPeerAddr(addr);
		return addr;
	}

	SocketAddr NetSession::GetHostAddr() const
	{
		SocketAddr addr;
		m_Socket.GetSocketAddr(addr);
		return addr;
	}

	void NetSession::Open(SOCKET s, SessionType type, NetServiceBase* pNet)
	{
		if (m_State == e_Connected)
		{
			return;
		}
		m_ID = 0;
		m_Type = type;
		m_pNetService = pNet;
		Socket temp(s);
		m_Socket.Shift(temp);
		m_State = e_Connected;
	}

	void NetSession::Close()
	{
		m_Socket.Close();
		m_Type = e_Active;
		m_pNetService = NULL;
	}

	bool NetSession::SendPacket(void* packet)
	{

	}

	void* NetSession::RecvPacket()
	{

	}

	int32 NetSession::SendData(const char* buff, int32 len)
	{

	}

	int32 NetSession::RecvData(char* buff, int32 len)
	{

	}
}