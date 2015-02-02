#include "PreCom.h"
#include "NetService.h"
#include "Socket.h"

namespace okey
{
	NetService::NetService(uint32 id, const NetServiceParam& param):m_ID(id),m_ConNum(0)
	{
		m_Param = param;
		//起线程。。。 
	}
	NetService::~NetService()
	{
		if (m_pThread)
		{
			delete m_pThread;
		}
	}
	bool NetService::StartUp()
	{
		if (m_State != e_Initial)
		{
			return false;
		}
		//起线程。
		//m_pThread->Start();
		return true;
	}
	void NetService::ShutDown()
	{
		if (m_State != e_Running)
		{
			return;
		}
		m_State = e_Shutdown;
		//m_pThread->Stop();
		m_pThread->Join();
		//全部停下。。。
	}
	bool NetService::OnConnect(SessionBase* pSession)
	{

	}

	bool NetService::OnAccept(SessionBase* pSession)
	{

	}

	bool NetService::OnDisconnect(SessionBase* pSession)
	{

	}

	bool NetService::OnSend()
	{

	}
	bool NetService::OnRecv()
	{

	}
	bool NetService::Run()
	{

	}
	SessionBase* NetService::Connect(const SocketAddr& addr)
	{

	}
	bool NetService::BindAddress(const SocketAddr& addr)
	{
		if (m_State != e_Running)
		{
			return false;
		}
		Socket sock;
		if (!sock.Create())
		{
			//create error
			return false;
		}
		if (!sock.Bind(addr))
		{
			return false;
		}
		if (!sock.Listen(m_Param.backlog))
		{
			return false;
		}
		if (!sock.SetNonBlocking())
		{
			return false;
		}
		sock.SetReuseAddr();
		//线程去注册监听器。。
	}
	bool NetService::Accept(const char* ip, int32 port)
	{

	}
	SessionBase* NetService::GetSession(int32 id)
	{
		CONNECTION_MAP::iterator itr = m_Connections.find(id);
		if (itr != m_Connections.end())
		{
			return itr->second;
		}
		return NULL;
	}
	bool NetService::Disconnect(int32 scoketid)
	{

	}
	void NetService::OnNewConnection(Socket& s, SessionBase::SessionType t)
	{
		SocketAddr addr;
		s.GetPeerAddr(addr);
		if (m_State != e_Running)
		{
			s.Close();
			return;
		}
		if (!InitSocket(s))
		{
			s.Close();
			return;
		}
		{
			FastMutex::ScopedLock lock(m_lock);
			if (m_ConNum >= m_Param._maxConNum)
			{
				s.Close();
				return;
			}
			++m_ConNum;
		}

		
	}
	SessionPtr NetService::Connect(uint32 id, const SocketAddr& addr)
	{
		if (m_State != e_Running)
		{
			return NULL;
		}
		Socket sock;
		if (!sock.Create())
		{
			return NULL;
		}
		if (!sock.Connect(addr))
		{
			return NULL;
		}
		if (!InitSocket(sock))
		{
			sock.Close();
			return NULL;
		}
		//Session.. 
	}
	void NetService::RecycleConnection(SessionBase* pSession)
	{
		bool bVerified = false;
		{
			FastMutex::ScopedLock lock(m_lock);
			if (m_ConNum > 0)
			{
				--m_ConNum;
			}
			CONNECTION_MAP::iterator itr = m_Connections.find(pSession->GetID());
			if (itr != m_Connections.end())
			{
				m_Connections.erase(itr);
				bVerified = true;
			}
		}
		if (bVerified)
		{
			//通知。。。。
		}
		pSession->Close();
		pSession->DecRef();
	}
}