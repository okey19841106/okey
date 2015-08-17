#include "PreCom.h"
#include "DatagramSocket.h"
#include "SocketAddr.h"
#include "Socket.h"

namespace okey
{
	DatagramSocket::DatagramSocket():m_Socket(INVALID_SOCKET)
	{

	}

	DatagramSocket::DatagramSocket(SOCKET s):m_Socket((s < 0) ? INVALID_SOCKET: s)
	{

	}

	DatagramSocket::~DatagramSocket()
	{
		Close();
	}

	SOCKET DatagramSocket::CreateSocket()
	{
		SOCKET s = INVALID_SOCKET;
		s = socket(PF_INET, SOCK_DGRAM,0);
		return s;
	}

	bool DatagramSocket::Create()
	{
		if (IsValid())
		{
			return false;
		}
		m_Socket = socket(PF_INET, SOCK_DGRAM,0);
		if (m_Socket >= 0)
		{
			return true;
		}
		return false;
	}

	bool DatagramSocket::Close()
	{
		if (m_Socket != INVALID_SOCKET)
		{
#ifdef WINDOWS
			int ret = ::closesocket(m_Socket);//只减少计数。
#else
			int ret = close(m_Socket);
#endif
			m_Socket = INVALID_SOCKET;
		}
		return true;
	}

	bool DatagramSocket::Bind()
	{
		SetReuseAddr();
		struct sockaddr_in serverAddr;
		memset( &serverAddr, 0, sizeof(serverAddr) );
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = 0;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		int32 ret = bind( m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
		return ret == 0 ? true: false;
	}

	bool DatagramSocket::Bind(const SocketAddr& addr)
	{
		SetReuseAddr();
		struct sockaddr_in serverAddr;
		addr.Get(serverAddr);
		int32 ret = bind( m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
		return ret == 0 ? true: false;
	}

	int32 DatagramSocket::Send(const char* buf, int32 len, int32 flags)
	{
		while (true)
		{
			int32 ret = send(m_Socket, buf, len, flags);
			if (ret < 0 )
			{
				int32 errNum = Socket::GetSysError();
				if (Socket::GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return ret;
		}
	}

	int32 DatagramSocket::Recv(char* buf, int32 len, int32 flags)
	{
		while (true)
		{
			int32 ret = recv(m_Socket, buf, len, flags);
			if (ret < 0 )
			{
				int32 errNum = Socket::GetSysError();
				if (Socket::GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return ret;

		}
	}

	int32 DatagramSocket::SendTo(const char* buf, int32 len, const SocketAddr& addr, int32 flags)
	{
		int rc;
		if (!IsValid())
		{
			return -1;
		}
		struct sockaddr_in saddr;
		addr.Get(saddr);
		do
		{
			rc = ::sendto(m_Socket, buf, len, flags, (struct sockaddr*)&saddr, sizeof(saddr));
		}
		while (rc < 0 && Socket::GetSysError() == SOCKET_EINTR);
		if (rc < 0) 
		{
			int32 err = Socket::GetSysError();
		}
		return rc;
	}

	int32 DatagramSocket::ReceiveFrom(char* buf, int32 len, SocketAddr& addr, int32 flags)
	{
		if (!IsValid())
		{
			return -1;
		}
		struct sockaddr_in raddr;
		int32 saLen = sizeof(raddr);
		int rc;
		do
		{
			rc = ::recvfrom(m_Socket, buf, len, flags, (struct sockaddr*)&raddr, &saLen);
		}
		while (rc < 0 && Socket::GetSysError() == SOCKET_EINTR);
		if (rc >= 0)
		{
			addr.Set(raddr);
		}
		else
		{
// 			int err = lastError();
// 			if (err == POCO_EAGAIN || err == POCO_ETIMEDOUT)
// 				throw TimeoutException();
// 			else
// 				error(err);
			int32 err = Socket::GetSysError();
		}
		return rc;
	}

	void DatagramSocket::SetReuseAddr()
	{
		uint32 option = 1;
		socklen_t len = sizeof(option);
		setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, len);
	}

	bool DatagramSocket::Connect(const SocketAddr& addr)
	{
		struct sockaddr_in serverAddr;
		addr.Get(serverAddr);
		while(true)
		{
			int32 ret = connect(m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			if (ret < 0)
			{
				if (Socket::GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return 0 == ret;
		}
		return false;
	}
}