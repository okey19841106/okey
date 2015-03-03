#include "PreCom.h"
#include "Acceptor.h"
#include "Socket.h"
#include "NetServiceBase.h"
#include "SessionBase.h"

namespace okey
{
#ifdef WINDOWS
	LPFN_ACCEPTEX Acceptor::m_fnAcceptEx = NULL;
#endif
	
	Acceptor::Acceptor(Socket& socket, const SocketAddr& addr, NetServiceBase* p)
	{
		m_Socket.Shift(socket);
		m_pNetService = p;
#ifdef WINDOWS
		class IOCPAcceptIniter
		{
		public:
			IOCPAcceptIniter(SOCKET s, LPFN_ACCEPTEX f)
			{
				DWORD dwBytes = 0;
				GUID guidAcceptEx = WSAID_ACCEPTEX;
				WSAIoctl(s, 
					SIO_GET_EXTENSION_FUNCTION_POINTER,
					&guidAcceptEx,
					sizeof(guidAcceptEx),
					&f,
					sizeof(f),
					&dwBytes,
					NULL,
					NULL);
			}
		};
		static IOCPAcceptIniter helper(socket.GetSocket(), m_fnAcceptEx);
		PostAccept();
#endif
	}
	Acceptor::~Acceptor()
	{
		m_Socket.Close();
	}
	void Acceptor::HandleInput()
	{
		while(true)
		{
			SOCKET sock = m_Socket.Accept();
			if (sock == INVALID_SOCKET)
			{
				int error = Socket::GetSysError();
				if (error != SOCKET_EAGAIN && error != SOCKET_EWOULDBLOCK)
				{
					//log...
				}
				break;
			}
			Socket Sock(sock);
			m_pNetService->OnNewConnection(Sock, SessionBase::e_Passive);
		}
	}
	void Acceptor::HandleOutput()
	{
		return;
	}
	void Acceptor::HandleException()
	{
		return;
	}
	void Acceptor::HandleClose()
	{
		delete this;
	}

	void Acceptor::HandleInput(void* pParam)
	{
		AcceptCompleteOperator* p = (AcceptCompleteOperator*)(pParam);
		if (!p)
		{
			//assert();
			return;
		}
		Socket s;
		s.Shift(p->m_AcceptSocket);
		m_pNetService->OnNewConnection(s, SessionBase::e_Passive);
		PostAccept();
	}

#ifdef WINDOWS
	void Acceptor::PostAccept()
	{
		Socket s;
		s.CreateSocket();
		//memset(m_RecvBuf, 0, sizeof(m_RecvBuf));
		DWORD bytes;
		m_AccepterCom.nMask = CompleteOperator::IOCP_EVENT_READ_COMPLETE;
		while(true)
		{
			BOOL ret = Acceptor::m_fnAcceptEx(m_Socket.GetSocket(), s.GetSocket(), m_RecvBuf, 0, ADDRLEN, ADDRLEN, &bytes, &m_AccepterCom);
			if (!ret)
			{
				uint32 error = Socket::GetSysError();
				if (error == WSA_IO_PENDING)
				{
					continue;
				}
			}
			m_AccepterCom.m_AcceptSocket.Shift(s);
			break;
		}
	}
#endif
	
}