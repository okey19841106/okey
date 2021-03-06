#include "PreCom.h"
#include "Acceptor.h"
#include "Socket.h"
#include "NetServiceBase.h"
#include "SessionBase.h"

namespace okey
{
#ifdef WINDOWS
	LPFN_ACCEPTEX IOCPAcceptor::m_fnAcceptEx = NULL;
#endif
	
	Acceptor::Acceptor(Socket& socket, const SocketAddr& addr, NetServiceBase* p)
	{
		m_Socket.Shift(socket);
		m_pNetService = p;
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

	void IOCPAcceptor::PostAccept()
	{
		Socket s;
		s.Create();
		DWORD bytes;
		AcceptCompleteOperator* pOverLapped = new AcceptCompleteOperator;
		pOverLapped->nMask = CompleteOperator::IOCP_EVENT_READ_COMPLETE;
		pOverLapped->pHandler = this;
		while(true)
		{
			BOOL ret = m_fnAcceptEx(m_Socket.GetSocket(), s.GetSocket(), m_RecvBuf, 0, ADDRLEN, ADDRLEN, &bytes, pOverLapped);
			if (!ret)
			{
				uint32 error = Socket::GetSysError();
				if (error != WSA_IO_PENDING)
				{
					continue;
				}
			}
			pOverLapped->m_AcceptSocket.Shift(s);
			break;
		}
	}
	
	IOCPAcceptor::IOCPAcceptor(Socket& socket, const SocketAddr& addr, NetServiceBase* p):Acceptor(socket, addr, p)
	{
		class IOCPAcceptIniter
		{
		public:
			IOCPAcceptIniter(SOCKET s, LPFN_ACCEPTEX& f)
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
		static IOCPAcceptIniter helper(m_Socket.GetSocket(), m_fnAcceptEx);
		PostAccept();
	}

	IOCPAcceptor::~IOCPAcceptor()
	{

	}

	void IOCPAcceptor::HandleInput(void* pParam)
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
		delete p;
		p = NULL;
		PostAccept();
	}

}