/********************************************************************
	created:	2015/07/30
	created:	14:37
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DATA_GRAM_SOCKET_H__
#define __DATA_GRAM_SOCKET_H__


namespace okey
{
	class SocketAddr;

	class DatagramSocket
	{
	public:
		DatagramSocket();
		explicit DatagramSocket(SOCKET s);
		virtual ~DatagramSocket();
		static SOCKET CreateSocket();
		bool Create();
		bool Close();
		bool Bind();
		bool Bind(const SocketAddr& addr);
		bool Connect(const SocketAddr& addr); //udp中不能再去调用bind，这是高效的方式去校验是否有错误。
		int32 Send(const char* buf, int32 len, int32 flags = 0);
		int32 Recv(char* buf, int32 len, int32 flags = 0);
		int32 SendTo(const char* buf, int32 len, const SocketAddr& addr, int32 flags = 0);
		int32 ReceiveFrom(char* buf, int32 len, SocketAddr& addr, int32 flags = 0);
		inline bool IsValid()const{return m_Socket != INVALID_SOCKET;}
		void SetReuseAddr();
	protected:
		SOCKET m_Socket;
	};
}

#endif