#include "PreCom.h"
#include "NetSession.h"
#include "NetServiceBase.h"
#include "Events/EventActor.h"

namespace okey
{
	const int32 NetSession::RECV_BLOCK_SIZE = 1024;

	NetSession::NetSession(NetServiceBase* pNetService, Event_Actor* pActor):m_State(e_DisConnected),m_Type(e_Active),m_ID(0),m_pNetService(pNetService),m_pActor(pActor)
	{
		m_SendBuffer.Allocate(pNetService->GetParam()._maxSendSize);
		m_RecvBuffer.Allocate(pNetService->GetParam()._maxRecvSize);
	}

	NetSession::~NetSession()
	{
		m_State = e_DisConnected;
		m_Socket.Close();
	}

	void NetSession::Disconnect()//线程处理断链接。。
	{
		if (m_State == e_DisConnected)
		{
			return;
		}
		m_State = e_DisConnected;
		m_pActor->RemoveHander(this,Event_Handler::Event_All);
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

	void NetSession::Open(Socket& s, SessionType type, NetServiceBase* pNet)
	{
		if (m_State == e_Connected)
		{
			return;
		}
		m_ID = 0;
		m_Type = type;
		m_pNetService = pNet;
		m_Socket.Shift(s);
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
		return true;
	}

	void* NetSession::RecvPacket()
	{
		return NULL;
	}

	int32 NetSession::SendData(const char* buff, int32 len)
	{
		if (m_State == e_DisConnected)
		{
			return -1;
		}
		int32 ret = -1;
		{
			FastMutex::ScopedLock lock(m_SendMutex);
			if( m_SendBuffer.GetSpace() > len )
			{
				m_SendBuffer.Write((void*)buff, len );
				return len;
			}
			//error 缓冲不够。 这块是不是要重新设计一下呢？。。。
			ret = m_Socket.Send(buff,len);
			if (ret < 0)
			{
				int32 error = Socket::GetSysError();
				if (SOCKET_EWOULDBLOCK == error || SOCKET_EAGAIN == error || SOCKET_ENOBUFS == error || SOCKET_EINTR == error)
				{
					int32 oldsize = m_Socket.GetSendBufSize();
					int32 maxsize = m_pNetService->GetParam()._sysSendBuff;
					if (oldsize < maxsize)
					{
						int32 newSize = (oldsize * 2) < maxsize ? (oldsize * 2): maxsize;
						if (m_Socket.SetSendBufSize(newSize))
						{
							ret = m_Socket.Send(buff,len);
						}
					}
				}
			}
			else if (ret < len)
			{
				int32 oldsize = m_Socket.GetSendBufSize();
				int32 maxsize = m_pNetService->GetParam()._sysSendBuff;
				if (oldsize < maxsize)
				{
					int32 newSize = (oldsize * 2) < maxsize ? (oldsize * 2): maxsize;
					if (m_Socket.SetSendBufSize(newSize))
					{
						int32 old = ret;
						ret = m_Socket.Send(buff,len - ret);
						if (ret >= 0)
						{
							ret += old;
						}
					}
				}
			}
		}
		if (ret < 0)
		{
			int32 error = Socket::GetSysError();
			if (SOCKET_EWOULDBLOCK == error || SOCKET_EAGAIN == error || SOCKET_ENOBUFS == error || SOCKET_EINTR == error)
			{
				//上边已经做过一次了。 这里再次阻塞了。 就直接放弃治疗 peer is busy
				Disconnect();
				return -1;
			}
			else if (SOCKET_ECONNRESET == error)
			{
				//对端已经断开链接了。。。 
				Disconnect();
				return -1;
			}
			else
			{
				//各种其他错误发生了。。。
				Disconnect();
				return -1;
			}
		}
		return ret;
	}

	int32 NetSession::RecvData(char* buff, int32 len)
	{
		if (m_State == e_DisConnected)
		{
			return -1;
		}
		int32 ret = m_Socket.Recv(buff,len);
		if (ret < 0)
		{
			int32 error = Socket::GetSysError();
			if (SOCKET_EWOULDBLOCK == error || SOCKET_EAGAIN == error || SOCKET_EINTR == error)
			{
				return 0;
			}
			else if (SOCKET_ECONNRESET == error)
			{
				ret = 0;
			}
			else
			{
				//IO 错误。。。
				Disconnect();
				return -1;
			}
		}
		if (0 == ret)//链接断开了。。 
		{
			Disconnect();
			return -1;
		}
		return ret;
	}

	void NetSession::OnRecv()
	{
		if (m_State == e_DisConnected)
		{
			return;
		}
		char buffer[RECV_BLOCK_SIZE];
		int32 tRecv = 0;
		do 
		{
			int32 ret = RecvData(buffer, RECV_BLOCK_SIZE);
			if (ret == -1)
			{
				//Disconnect();
				return;
			}
			if (ret == 0) //block。。。 不再读了。
			{
				break;
			}
			tRecv += ret;
			if ((int32)m_RecvBuffer.GetSpace() >= ret)
			{
				m_RecvBuffer.Write(buffer,ret);
			}
			else
			{
				while(ret > (int32)m_RecvBuffer.GetSpace())
				{
					//生成数据包。。
				}
				if (ret <= (int32)m_RecvBuffer.GetBuffer())
				{
					m_RecvBuffer.Write(buffer,ret);
				}
				else
				{
					// RecvData Error..............
					Disconnect();
				}
			}

		} while (true);
// 		while(true)
// 		{
// 			//生成数据包 放在队列里。。 
// 		}
	}

	void NetSession::OnTick(const TimeStamp& curtime)
	{
		//可以发送心跳包。。。
	}

	void NetSession::OnConnect()
	{

	}

	void NetSession::OnSend()
	{
		int32 total = 0;
		do 
		{
			if (m_SendBuffer.GetSize() <= 0)
			{
				return;
			}
			uint32 smax = m_pNetService->GetParam()._sysSendBuff;
			int32 len = (int32)(m_SendBuffer.GetSize() < smax? m_SendBuffer.GetSize(): smax);
			int32 ret = m_Socket.Send((const char*)m_SendBuffer.GetBufferStart(), len);
			if (ret < 0)
			{
				int32 error = Socket::GetSysError();
				if (SOCKET_EWOULDBLOCK == error || SOCKET_EINTR == error || SOCKET_EAGAIN == error)
				{
					m_pActor->RegisterHandler(this, Event_Out);
					break;
				}
				else if (SOCKET_ECONNRESET == error)
				{
					ret = 0;
				}
				else
				{
					//IO error
					Disconnect();
				}
			}
			if (ret == 0)
			{
				//connect disconnect;
				Disconnect();
			}
			m_SendBuffer.Remove(ret);
			total += ret;
		} while (true);
	}

	void NetSession::HandleInput()
	{
		OnRecv();
	}

	void NetSession::HandleOutput()
	{
		OnSend();
		m_pActor->RemoveHander(this,Event_Out);
	}
	void NetSession::HandleException()
	{
		Disconnect();
	}

	void NetSession::HandleTick(const TimeStamp& now)
	{
		if (m_State == e_DisConnected)
		{
			//removeHandler(this, NETNEVET_ALL);
			return;
		}
		OnTick(now);
	}

	void NetSession::HandleClose()
	{
		Disconnect();
		m_pNetService->RecycleConnection(this);
	}

	void NetSession::SetEventActor(Event_Actor* pActor)
	{
		m_pActor = pActor;
	}

}