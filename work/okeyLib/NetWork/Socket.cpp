#include "PreCom.h"
#include "Socket.h"
#include "SocketAddr.h"

namespace okey
{
	Socket::Socket():m_Socket(INVALID_SOCKET)
	{

	}

	Socket::Socket(SOCKET s):m_Socket((s < 0) ? INVALID_SOCKET: s)
	{

	}

	bool Socket::Create()
	{
		if (IsValid())
		{
			return false;
		}
#ifdef WINDOWS
		::WSASocket(AF_INET, SOCK_STREAM, 0, 0, 0, WSA_FLAG_OVERLAPPED);
#else
		m_Socket = socket(PF_INET, SOCK_STREAM,0);
#endif
		if (m_Socket >= 0)
		{
			return true;
		}
		return false;
	}

	bool Socket::Close()
	{
		if (!IsValid())
		{
			return false;
		}
		while(true)
		{
#ifdef WINDOWS
			int ret = ::closesocket(m_Socket);//只减少计数。
#else
			int ret = close(m_Socket);
#endif
			if (ret < 0 && GetSysError() == SOCKET_EINTR)
			{
				continue;
			}
			else
			{
#ifdef WINDOWS
				shutdown(m_Socket, SD_BOTH);
#else
				shutdown(m_Socket, SHUT_RDWR);
#endif
			}
			m_Socket = INVALID_SOCKET;
			return (0 == ret);
		}
	}
	void Socket::SetReuseAddr()
	{
		uint32 option = 1;
		socklen_t len = sizeof(option);
		setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&option, len);
	}
	bool Socket::Bind()
	{
		struct sockaddr_in serverAddr;
		memset( &serverAddr, 0, sizeof(serverAddr) );
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = 0;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		int32 ret = bind( m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
		if ( ret ==  0)
		{
			SetReuseAddr();
			return true;
		}
		return false;
	}
	bool Socket::Bind(const SocketAddr& addr)
	{
		struct sockaddr_in serverAddr;
		addr.Get(serverAddr);
		int32 ret = bind( m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
		if ( ret ==  0)
		{
			SetReuseAddr();
			return true;
		}
		return false;
		
	}
	bool Socket::Connect(const SocketAddr& addr)
	{
		struct sockaddr_in serverAddr;
		addr.Get(serverAddr);
		while(true)
		{
			int32 ret = connect(m_Socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			if (ret < 0)
			{
				if (GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return 0 == ret;
		}
		return false;
		
	}
	bool Socket::Listen(int32 backlog)
	{
		return listen(m_Socket,backlog) == 0;//连接请求队列的最大长度
	}

	SOCKET Socket::Accept()
	{
		while(true)
		{
#ifdef WINDOWS
			SOCKET s = WSAAccept(m_Socket, NULL, NULL, NULL, NULL);
#else
			SOCKET s = accept(m_Socket, NULL, NULL);
#endif
			
			if (s < 0)
			{
				if (GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return s;
		}
		return INVALID_SOCKET;
	}

	int32 Socket::Send(const char* buf, int32 len, int32 flags)
	{
		while (true)
		{

			int32 ret = send(m_Socket, buf, len, flags);

			if (ret < 0 )
			{
				int32 errNum = GetSysError();
				if (GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
				
			}
			return ret;
		}
	}

	int32 Socket::Recv(char* buf, int32 len, int32 flags)
	{
		while (true)
		{

			int32 ret = recv(m_Socket, buf, len, flags);

			if (ret < 0 )
			{
				int32 errNum = GetSysError();
				if (GetSysError() == SOCKET_EINTR)
				{
					continue;
				}
			}
			return ret;

		}
	}

	bool Socket::GetSocketAddr(SocketAddr& addr)const
	{
		struct sockaddr_in addr4;
		socklen_t len = sizeof(addr4);
		if (getsockname(m_Socket, (sockaddr*)&addr4, &len) != 0)
		{
			return false;
		}
		addr.Set(addr4);
		return true;
	}
	bool Socket::GetPeerAddr(SocketAddr& addr)const
	{
		struct sockaddr_in addr4;
		socklen_t len = sizeof(addr4);
		if (getpeername(m_Socket, (sockaddr*)&addr4, &len) != 0)
		{
			return false;
		}
		addr.Set(addr4);
		return true;
	}
	int32 Socket::GetLinger() const //关闭延时。。。，非阻塞是优雅关闭。。。
	{
		struct linger lin;
		socklen_t len = sizeof(lin);
		if (getsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (char*)&lin, &len) == 0)
		{
			return lin.l_linger;
		}
		return -1;
	}
	bool Socket::SetLinger(int32 ling)
	{
		struct linger lin;
		lin.l_onoff = 1;
		lin.l_linger = (uint16)ling;
		socklen_t len = sizeof(lin);
		if (setsockopt(m_Socket, SOL_SOCKET, SO_LINGER, (char*)&lin, len) == 0)
		{
			return true;
		}
		return false;
	}

	bool Socket::SetNonBlocking(bool on)
	{
#ifdef WINDOWS
		u_long arg = on ? 1: 0;
		return (::ioctlsocket(m_Socket, FIONBIO, &arg) == 0);
#else
		int opts = fcntl(m_Socket, F_GETFL, 0);
		if (opts < 0)
		{
			return false;
		}
		if (on)
		{
			opts |= O_NONBLOCK;
		}
		else
		{
			opts &= ~O_NONBLOCK
		}
		return fcntl(m_Socket, F_SETFL, opts) >= 0;
#endif
	}
	bool Socket::SetNonDelay()
	{
		int32 arg = 1;
		return (setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&arg, sizeof(arg)) == 0);
	}

	int32 Socket::GetRecvBufSize()const
	{
		int32 val = 0;
		socklen_t len = sizeof(val);
		if (getsockopt(m_Socket,SOL_SOCKET, SO_RCVBUF, (char*)&val, &len) >= 0)
		{
			return val;
		}
		return -1;
	}
	bool Socket::SetRecvBufSize(int32 len)
	{
		socklen_t val = sizeof(len);
		return setsockopt(m_Socket, SOL_SOCKET, SO_RCVBUF, (char*)&len, val) == 0;
	}

	int32 Socket::GetSendBufSize() const
	{
		int32 val = 0;
		socklen_t len = sizeof(val);
		if (getsockopt(m_Socket,SOL_SOCKET, SO_SNDBUF, (char*)&val, &len) >= 0)
		{
			return val;
		}
		return -1;
	}
	bool Socket::SetSendBufSize(int32 len)
	{
		socklen_t val = sizeof(len);
		return setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, (char*)&len, val) == 0;
	}

	int32 Socket::GetSocketError()const
	{
		int32 error = 0;
		socklen_t len = sizeof(error);
		if (getsockopt(m_Socket, SOL_SOCKET, SO_ERROR, (char*)&error, &len) != 0)
		{
			return GetSysError();
		}
		return error;
	}
	int32 Socket::GetSysError()
	{
#ifdef WINDOWS
		return ::WSAGetLastError();
#else
		return errno;
#endif
	}
	void Socket::Shift(Socket& sock)
	{
		Close();
		m_Socket = sock.m_Socket;
		sock.m_Socket = INVALID_SOCKET;
	}
}