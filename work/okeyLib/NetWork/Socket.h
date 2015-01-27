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

#else

#define SOCKET_EINTR	EINTR //被终端
#define SOCKET_EWOULDBLOCK	EWOULDBLOCK //非阻塞返回。
#define SOCKET_ENOBUFS	ENOBUFS //没有足够的缓冲区资源
#define SOCKET_ETIMEDOUT	ETIMEDOUT
#define SOCKET_ECONNRESET	ECONNRESET
#define SOCKET_EAGAIN	EAGAIN


#endif

	class SocketAddr
	{
		friend class Socket;
	public:
		SocketAddr():m_iPort(0){}
		SocketAddr(const std::string& ip, int32 port):m_sIP(ip), m_iPort(port){}
		SocketAddr(const SocketAddr& s): m_iPort(s.m_iPort), m_sIP(s.m_sIP){}
		~SocketAddr();
		int32 GetPort()const{return m_iPort;}
		void SetPort(const int32& port){m_iPort = port;}
		void SetIP(const std::string& ip){m_sIP = ip;}
		std::string GetIP() const{return m_sIP;}
		const SocketAddr& operator = (const SocketAddr& r)
		{
			if (&r != this)
			{
				m_sIP = r.m_sIP;
				m_iPort = r.m_iPort;
			}
			return *this;
		}
		void SetAddr(const struct sockaddr_in& addr)
		{
			Set(addr);
		}
	private:
		void Set(const struct sockaddr_in& addr);
		void Get(struct sockaddr_in& addr) const ;
		std::string m_sIP;
		int32 m_iPort;
	};

	class Socket
	{
	public:
		Socket();
		explicit Socket(SOCKET s);
		virtual ~Socket()
		{
			Close();
		}
		bool Create();
		bool Close();
		bool Bind();
		bool Bind(const SocketAddr& addr);
		bool Connect(const SocketAddr& addr);
		bool Listen(int32 backlog = 128);
		SOCKET Accept();
		int32 Send(const char* buf, int32 len, int32 flags = 0);
		int32 Recv(char* buf, int32 len, int32 flags = 0);

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
#ifdef WINDOWS
	protected:
		OVERLAPPED* m_RecvCompleteOperation;
		OVERLAPPED* m_SendCompleteOperation;
#endif
	private:
		

		SOCKET m_Socket;
	};
}

#endif