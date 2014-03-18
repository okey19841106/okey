/********************************************************************
	created:	2013/03/05
	created:	5-3-2013   22:53
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_


#include "Types.h"
#include "SocketBase.h"
#include "NetReactor.h"
#include "CompleteOperation.h"


namespace okey
{

#define SEND_BUFFER 4096
#define RECV_BUFFER 4096

	class PacketBase;
	class NetManagerBase;
	/**
	 * a session
	 */
	#define PACKET_LEN     2
	#define PACKET_HEAD_ID 4
	#define PACKET_SESSION_ID 4
	#define PACKET_TYPE_ID 1

	#define PACKET_HEAD (2+4+4+1)

	#define MAX_PACKET_BUFFER 512


	class MySocket : public SocketBase, public NetEventHandler
	{
	public:
		MySocket(NetManagerBase* mgr, uint32 sndBufSize, uint32 rvcBufSize, int32 socketRcvBuff = 4096, int32 socketSndBuff = 4096 );
		~MySocket();

#ifdef WINDOWS
	public:
		WSABUF* GetRecvWSABUF();
		WSABUF* GetSendWSABUF();

		CompleteOperator* GetRecvCompleteOperation();
		CompleteOperator* GetSendCompleteOperation();

		bool PostRecvOperation();
		bool PostSendOperation();

	private:
		WSABUF m_RecvWSABUF;
		WSABUF m_SendWSABUF;
 		CompleteOperator m_RecvCompleteOperation;
 		CompleteOperator m_SendCompleteOperation;

#elif defined(LINUX)
	public:
		AsyncCompleteOperation* GetAsyncCompleteOperation();

	private:
		SessionCompleteOperation m_SessionCompleteOperation;
#endif

	public:
		virtual void SetSocket(SOCKET s){m_Sock = s;}
		virtual SOCKET GetSocket(){return m_Sock;}
		virtual bool Listen(const std::string& ip, int32 port);
		virtual bool Connect(const std::string& ip, int32 port);
		virtual bool Recv();
		virtual bool SendBuffer( void* pData, uint32 size );
		virtual bool SendPacket(PacketBase* pkt);
		virtual void Disconnect();
		virtual PacketBase* RecvPacket();
		virtual void OnSend();
		virtual void OnDisconnect();
		virtual void OnRecv();
		virtual void OnConnect();
		virtual SocketBase* Accept(uint32 sndBuffSize, uint32 recvBuffSize, int32 socketRcvBuff, int32 socketSndBuff );
		bool InitSocketBuffer();
		virtual bool CreateSocket();
	public:
		CircularBuffer* GetRecvBuffer()
		{
			return &m_RecvBuffer;
		}

		CircularBuffer* GetSendBuffer()
		{
			return &m_SendBuffer;
		}

	public:
		virtual SocketBase* GetHandleSocket();
		virtual void HandleInput(void* pParam);
		virtual void HandleOutput(void* pParam);
		virtual void HandleException(void* pParam);
		virtual void HandleTick(const uint64& tNow);
		virtual void HandleClose(void* pParam);
	protected:
		SOCKET m_Sock;
		//the data's size in sending
		CircularBuffer m_SendBuffer;
		CircularBuffer m_RecvBuffer;
		int32 m_SocketRcvBuff;
		int32 m_SocketSndBuff;
		NetManagerBase* m_NetManger;
		
	};

} //namespace okey

#endif 	//SESSION_H
