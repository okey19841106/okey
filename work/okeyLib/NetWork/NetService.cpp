#include "PreCom.h"
#include "NetService.h"
#include "Socket.h"
#include "Fuction.h"
#include "NetSession.h"
#ifdef WINDOWS
#include "IOCPProactor.h"
#else
#include "EpollReactor.h"
#endif

namespace okey
{
	NetService::NetService(uint32 id, const NetServiceParam& param):m_ID(id),m_ConNum(0),m_State(e_Initial)
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
		m_pEventActor->Open();
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
	void NetService::Run()
	{

	}
	SessionBase* NetService::Connect(const SocketAddr& addr)
	{

	}
	bool NetService::Accept(const SocketAddr& addr)
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
		SessionBase* pSession = GetSession(scoketid);
		RecycleConnection(pSession);
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
			FastMutex::ScopedLock lock(m_ConMutex);
			if (m_ConNum >= m_Param._maxConNum)
			{
				s.Close();
				return;
			}
			++m_ConNum;
		}
		SessionBase* pSession = new NetSession;
		SOCKET sock = s.GetSocket();
		pSession->Open(sock, t, this);
		pSession->SetEventActor(m_pEventActor);
		ScheduleSession(pSession);
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
		SessionBase* pSession = new NetSession;
		SOCKET s = sock.GetSocket();
		pSession->Open(s, SessionBase::e_Active, this);
		pSession->SetEventActor(m_pEventActor);
		if (m_ConnectCallBack)
		{
			(*m_ConnectCallBack)(pSession);
		}
		SessionPtr sPtr = pSession;
		ScheduleSession(sPtr);
		return sPtr;
	}
	void NetService::RecycleConnection(SessionBase* pSession)
	{
		bool bVerified = false;
		{
			FastMutex::ScopedLock lock(m_ConMutex);
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
		if (m_DisconnectCallBack && bVerified)
		{
			(*m_DisconnectCallBack)(pSession);
			//通知。。。。
		}
		pSession->Close();
		pSession->DecRef();
	}

	void NetService::ScheduleSession(SessionBase* pSession)
	{

	}

	Thread* NetService::CreateThread()
	{

	}

	void NetService::DestroyThread(Thread* pThread)
	{

	}


// 	void NetService::HandlerRun()
// 	{
// 		HANDLER_VEC newHandlers;
// 		{
// 			FastMutex::ScopedLock lock(m_WaitMutex);
// 			newHandlers.assign(m_WaitList.begin(), m_WaitList.end());
// 			m_WaitList.clear();
// 		}
// 		for (HANDLER_VEC::iterator itr = newHandlers.begin(); itr != newHandlers.end(); ++itr)
// 		{
// 			if (!m_pEventActor->RegisterHandler(itr->first, itr->second))
// 			{
// 				//log error...
// 				itr->first->HandleClose();
// 			}
// 		}
// 		newHandlers.clear();
// 	}
}