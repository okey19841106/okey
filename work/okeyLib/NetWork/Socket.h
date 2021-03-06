/********************************************************************
	created:	2015/01/27
	created:	14:52
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_SOCKET_H__
#define __OKEY_SOCKET_H__

#include "Types.h"
#include <string>

namespace okey
{
#ifdef WINDOWS

#define SOCKET_EINTR	WSAEINTR //被终端
#define SOCKET_EWOULDBLOCK	WSAEWOULDBLOCK //非阻塞返回。
#define SOCKET_ENOBUFS	WSAENOBUFS //没有足够的缓冲区资源
#define SOCKET_ETIMEDOUT	WSAETIMEDOUT
#define SOCKET_ECONNRESET	WSAECONNRESET
#define SOCKET_EAGAIN	-1
#define SOCKET_EINPROGRESS WSAEINPROGRESS
#else

#define SOCKET_EINTR	EINTR //被终端
#define SOCKET_EWOULDBLOCK	EWOULDBLOCK //非阻塞返回。
#define SOCKET_ENOBUFS	ENOBUFS //没有足够的缓冲区资源
#define SOCKET_ETIMEDOUT	ETIMEDOUT
#define SOCKET_ECONNRESET	ECONNRESET
#define SOCKET_EAGAIN	EAGAIN
#define SOCKET_EINPROGRESS	EINPROGRESS

#endif

	class SocketAddr;

	class Socket
	{
	public:
		enum SelectMode
		{
			SELECT_READ  = 1,
			SELECT_WRITE = 2,
			SELECT_ERROR = 4
		};

		Socket();
		explicit Socket(SOCKET s);
		virtual ~Socket()
		{
			Close();
		}
		static SOCKET CreateSocket();
		bool Create();
		bool Close();
		bool Bind();
		bool Bind(const SocketAddr& addr);
		bool Connect(const SocketAddr& addr);
		bool Connect(const SocketAddr& address, int64 timeout);
		bool Listen(int32 backlog = 128);
		SOCKET Accept();
		virtual int32 Send(const char* buf, int32 len, int32 flags = 0);
		virtual int32 Recv(char* buf, int32 len, int32 flags = 0);
		void SendUrgent(uint8 data);
		bool GetSocketAddr(SocketAddr& addr)const;
		bool GetPeerAddr(SocketAddr& addr)const;
		int32 GetLinger() const;
		bool SetLinger(int32 lin);

		void SetReuseAddr();

		bool SetNonBlocking(bool on = true);
		bool SetNonDelay();

		int32 GetRecvBufSize()const;
		bool SetRecvBufSize(int32 len);

		int32 GetSendBufSize() const;
		bool SetSendBufSize(int32 len);

		int32 GetSocketError()const;
		static int32 GetSysError();

		bool IsValid()const{return m_Socket != INVALID_SOCKET;}
		SOCKET GetSocket()const{return m_Socket;}
		void Shift(Socket& sock);
		void ShutdownReceive();
		void ShutdownSend();
		static bool Poll(SOCKET s, int64 timeout, int32 mode);
	protected:
		

		SOCKET m_Socket;
	};
}

#endif