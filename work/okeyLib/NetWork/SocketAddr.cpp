#include "PreCom.h"
#include "SocketAddr.h"

namespace okey
{
	void SocketAddr::Set(const struct sockaddr_in& addr)
	{
#ifdef WINDOWS
		char* str = inet_ntoa(addr.sin_addr);
		if (str)
		{
			m_sIP = str;
		}
#else
		char str[32];
		memset(str, 0, sizeof(str));
		inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str));
#endif
		m_iPort = ntohs(addr.sin_port);
	}

	void SocketAddr::Get(struct sockaddr_in& addr) const
	{
		memset(&addr , 0, sizeof(addr));
		addr.sin_family =AF_INET;
		addr.sin_addr.s_addr = inet_addr(m_sIP.c_str());
		addr.sin_port = htons(m_iPort);
	}

}