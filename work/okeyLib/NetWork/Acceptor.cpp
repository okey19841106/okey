#include "PreCom.h"
#include "Acceptor.h"
#include "Socket.h"
#include "NetServiceBase.h"
#include "SessionBase.h"

namespace okey
{
	Acceptor::Acceptor(Socket& socket, const SocketAddr& addr, NetServiceBase* p)
	{
		m_Socket.Shift(socket);
		m_pNetService = p;
	}
	Acceptor::~Acceptor()
	{
		m_Socket.Close();
	}
	void* Acceptor::GetHandle()
	{

	}
	void Acceptor::SetHandle(const void* pHandle){}
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
}