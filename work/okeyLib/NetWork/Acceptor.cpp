#include "PreCom.h"
#include "Acceptor.h"

namespace okey
{
	Acceptor::Acceptor(Socket& socket, const SocketAddr& addr, NetServiceImpl* p)
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
			Socket Sock(socket);
			m_pNetService->OnNewConnection(Sock, CT_PASSIVE);
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