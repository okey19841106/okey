/********************************************************************
	created:	2015/01/29
	created:	16:03
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NET_SOCKET_ADDR_H__
#define __NET_SOCKET_ADDR_H__

#include "Types.h"
#include <string>

namespace okey
{
	class SocketAddr
	{
		friend class Socket;
	public:
		SocketAddr():m_iPort(0){}
		SocketAddr(const std::string& ip, int32 port):m_sIP(ip), m_iPort(port){}
		SocketAddr(const SocketAddr& s): m_iPort(s.m_iPort), m_sIP(s.m_sIP){}
		~SocketAddr(){}
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
		void Swap(SocketAddr& addr)
		{
			std::swap(m_iPort,addr.m_iPort);
			std::swap(m_sIP,addr.m_sIP);
		}
		std::string toString() const;
		bool operator < (const SocketAddr& addr) const;
		bool operator == (const SocketAddr& addr) const;
		bool operator != (const SocketAddr& addr) const;
	private:
		void Set(const struct sockaddr_in& addr);
		void Get(struct sockaddr_in& addr) const ;
		std::string m_sIP;
		int32 m_iPort;
	};
	inline void Swap(SocketAddr& addr1, SocketAddr &addr2)
	{
		addr1.Swap(addr2);
	}
	
	inline bool SocketAddr::operator == (const SocketAddr& addr) const
	{
		return m_sIP == addr.m_sIP && m_iPort == addr.m_iPort;
	}
	inline bool SocketAddr::operator != (const SocketAddr& addr) const
	{
		return m_sIP != addr.m_sIP || m_iPort != addr.m_iPort;
	}
}

#endif