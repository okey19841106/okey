
#include "PreCom.h"
#include "MySocket.h"
#include "NetManagerBase.h"
#include "log/Logger.h"
#include "HelperFunction.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "SocketOps.h"
#include "IOCPReactor.h"


namespace okey
{

#ifdef WINDOWS
	MySocket::MySocket(NetManagerBase* mgr, uint32 sndBufSize, uint32 rvcBufSize,int32 socketRcvBuff, int32 socketSndBuff):m_NetManger(mgr),
					 m_SocketRcvBuff(socketRcvBuff),m_SocketSndBuff(socketSndBuff)
	{
		m_Sock = INVALID_SOCKET;
		m_SendDataSizeTotal = 0; 
		m_RecvDataSizeTotal = 0;
		m_Sending = false;
		m_SendingDataSize = 0;
		m_SendBuffer.Allocate(sndBufSize);
		m_RecvBuffer.Allocate(rvcBufSize);
	}

#elif defined(LINUX)
	MySocket::MySocket( int32 id, SOCKET sock, const std::string& ip, int32 port,uint32 sndBufSize, uint32 rvcBufSize )
	: m_SendDataSizeTotal(0), m_RecvDataSizeTotal(0),
	m_ID(id), m_Sock(sock), m_IP(ip), m_Port(port),
	m_Sending( false ), m_SendingDataSize(0)
	{
		m_SessionCompleteOperation.SetSession( this );
		m_SendBuffer.Allocate(sndBufSize);
		m_RecvBuffer.Allocate(rvcBufSize);
	}

#endif

	MySocket::~MySocket()
	{
		SocketOps::CloseSocket(m_Sock);
		m_Sock = INVALID_SOCKET;
	}

#ifdef WINDOWS

	WSABUF* MySocket::GetRecvWSABUF()
	{
		m_RecvWSABUF.buf = (char*)m_RecvBuffer.GetBuffer();
		m_RecvWSABUF.len = static_cast<u_long>( m_RecvBuffer.GetSpace() );
		return &m_RecvWSABUF;
	}

	WSABUF* MySocket::GetSendWSABUF()
	{
		m_SendWSABUF.buf = (char*)m_SendBuffer.GetBufferStart();
		m_SendWSABUF.len = static_cast<u_long>( m_SendBuffer.GetSize() );
		return &m_SendWSABUF;
	}

	CompleteOperator* MySocket::GetRecvCompleteOperation()
	{
		m_RecvCompleteOperation.hEvent = 0;
		m_RecvCompleteOperation.Internal = 0;
		m_RecvCompleteOperation.InternalHigh = 0;
		m_RecvCompleteOperation.Offset = 0;
		m_RecvCompleteOperation.OffsetHigh = 0;
		m_RecvCompleteOperation.nMask = NetEvent_In;
		return &m_RecvCompleteOperation;
	}

	CompleteOperator* MySocket::GetSendCompleteOperation()
	{
		m_SendCompleteOperation.hEvent = 0;
		m_SendCompleteOperation.Internal = 0;
		m_SendCompleteOperation.InternalHigh = 0;
		m_SendCompleteOperation.Offset = 0;
		m_SendCompleteOperation.OffsetHigh = 0;
		m_SendCompleteOperation.nMask = NetEvent_Out;
		return &m_SendCompleteOperation;
	}

	bool MySocket::PostRecvOperation()
	{
		unsigned long dwNumTransferred = 0;
		DWORD dwFlags = 0;
		int32 ret = WSARecv(
			GetSocket(),
			GetRecvWSABUF(),
			1,
			&dwNumTransferred,
			&dwFlags,
			GetRecvCompleteOperation(),
			NULL
			);
		if ( 0 != ret )
		{
			int32 errNum = WSAGetLastError();
			if ( WSA_IO_PENDING != errNum )
			{
				LOG_ERROR( logger, __FUNCTION__ << " failed WSARecv(), " << FormatErrorMessage( errNum ) );
				return false;
			}
		}

		return true;
	}

	bool MySocket::PostSendOperation()
	{
		m_SendingDataSize = static_cast<u_long>( m_SendBuffer.GetSize() );

		DWORD dwNumTransferred = 0;
		int32 ret = WSASend(
			GetSocket(), 
			GetSendWSABUF(), 
			1,
			&dwNumTransferred,
			0,
			GetSendCompleteOperation(),
			NULL
			);
		if ( SOCKET_ERROR == ret )
		{
			int32 errNum = WSAGetLastError();
			if ( WSA_IO_PENDING != errNum )
			{
				LOG_ERROR( logger, __FUNCTION__	<< " failed WSASend(), " << FormatErrorMessage( errNum ) );

				return false;
			}
		}

		return true;
	}

#elif defined(LINUX)

	AsyncCompleteOperation* MySocket::GetAsyncCompleteOperation()
	{
		return &m_SessionCompleteOperation;
	}

#endif

	bool MySocket::SendBuffer(void* pData, uint32 size )
	{
		MutexGuard guard( m_SendMutex );

		//check if free space is enough
		if( m_SendBuffer.GetSpace() < size )
		{
			return false;
		}
		m_SendBuffer.Write((void*)pData, size );
	#ifdef WINDOWS
		if ( !m_Sending )
		{
			PostSendOperation();
			SetSending( true );
		}	
		
	#elif defined(LINUX)
		guard.UnLock();
		m_SessionCompleteOperation.Complete( ASYNC_OPERATION_SEND );

	#endif

		return true;
	}

	void MySocket::Disconnect()
	{
		m_NetManger->Disconnect(m_ID);
	}

	PacketBase* MySocket::RecvPacket()
	{
		while(true)
		{
			if( static_cast<size_t>(m_RecvBuffer.GetSize()) < PACKET_HEAD )
			{
				break;
			}
			int16 packetlen = *( (int16*)(m_RecvBuffer.GetBufferStart()) );
			if( m_RecvBuffer.GetSize() < static_cast<size_t>(packetlen) + PACKET_LEN)
			{
				break;
			}
			m_RecvBuffer.Remove(PACKET_LEN);
			uint32 packetid = *( (uint32*)(m_RecvBuffer.GetBufferStart()) );
			PacketBase* pkt = (PacketBase*)s_PacketFactory.CreatePacket(packetid);
			if (!pkt)
			{
				break;
			}
			pkt->ReadPacket((char*)m_RecvBuffer.GetBufferStart());
			pkt->SetSocketID(m_ID);
			m_RecvBuffer.Remove(packetlen);
			return pkt;
		}
		return NULL;
	}

	void MySocket::OnRecv()
	{
		while (true)
		{
			PacketBase* pkt = RecvPacket();
			if (!pkt)
			{
				return;
			}
			if (!m_NetManger || !m_NetManger->GetPacketProcess())
			{
				return;
			}
			m_NetManger->ProcessPacket(pkt);
		}
	}
	bool MySocket::SendPacket(PacketBase* pkt)
	{
		if (!pkt)
		{
			return false;
		}
		MutexGuard guard( m_SendMutex );
		int16 packetlen = pkt->GetPakcetSize();
		//check if free space is enough
		if( m_SendBuffer.GetSpace() <(uint32)(packetlen + PACKET_LEN) )
		{
			return false;
		}
		
		char buffer[MAX_PACKET_BUFFER];
		pkt->WritePacket(buffer);
		m_SendBuffer.Write((void*)&packetlen, sizeof(int16) );
		m_SendBuffer.Write((void*)buffer,packetlen);
#ifdef WINDOWS
		if ( !m_Sending )
		{
			PostSendOperation();
			m_Sending = true;
		}	

#elif defined(LINUX)
		guard.UnLock();
		m_SessionCompleteOperation.Complete( ASYNC_OPERATION_SEND );

#endif
		return true;
	}
	void MySocket::OnSend()
	{
		return;
	}

	bool MySocket::Listen(const std::string& ip, int32 port)
	{
		if (!CreateSocket())
		{
			return false;
		}
		SocketOps::ReuseAddr(m_Sock);
		if (!SocketOps::DisableBuffering(m_Sock))
		{
			return false;
		}
#ifdef WINDOWS
		//IOCP特性，不然会返回64的错误哦。。
		int32 enabled = TRUE;
		if ( SO_ERROR == setsockopt( m_Sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&enabled, sizeof(enabled) ) )
		{
			return false;
		}
#endif
		sockaddr_in serverAddr;
		memset( &serverAddr, 0, sizeof(serverAddr) );
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons( port );
		serverAddr.sin_addr.s_addr = inet_addr( ip.c_str() );
		if ( SOCKET_ERROR == bind( m_Sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr) ) )
		{
			return false;
		}
		if( SOCKET_ERROR == listen( m_Sock, 5 ) )
		{
			return false;
		}
		m_IP = ip;
		m_Port = port;
		return true;
	}

	bool MySocket::Connect(const std::string& ip, int32 port)
	{
		
		if (!CreateSocket())
		{
			return false;
		}

		sockaddr_in serverAddr;
		memset( &serverAddr, 0, sizeof(serverAddr) );
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons( port );
#ifdef WINDOWS
		serverAddr.sin_addr.s_addr = inet_addr( ip.c_str());
#elif defined(LINUX)
		if ( 1 != inet_pton( AF_INET, ip, &serverAddr.sin_addr.s_addr ) )
		{
			return false;
		}
#endif

		//blocking connect to the server
#ifdef WINDOWS
		if( SOCKET_ERROR == connect( m_Sock, (sockaddr*)&serverAddr, sizeof(serverAddr) ) )
#elif defined(LINUX)
		if( -1 == connect( m_Sock, (sockaddr*)&serverAddr, sizeof(serverAddr) ) )
#endif
		{
			return false;
		}
		if (!InitSocketBuffer())
		{
			return false;
		}
		return true;
	}

	bool MySocket::Recv()
	{
		OnRecv();
		return true;
	}

	void MySocket::OnDisconnect()
	{

	}

	void MySocket::OnConnect()
	{

	}

	SocketBase* MySocket::Accept(uint32 sndBuffSize, uint32 recvBuffSize, int32 socketRcvBuff, int32 socketSndBuff )
	{
		SOCKET tmpSocket = INVALID_SOCKET;
		struct sockaddr_in tempAddress;
		int32 len = sizeof(sockaddr_in);
 #ifdef WINDOWS
 		tmpSocket = WSAAccept(m_Sock, (sockaddr*)&tempAddress, &len, NULL, NULL);
 #else
		tmpSocket = accept(m_Sock, (sockaddr*)&tempAddress, (socklen_t*)&len);
#endif
		char Buff[16] = {0};
		sprintf_s(Buff, inet_ntoa(tempAddress.sin_addr));
		printf("%s:%d\n",Buff  ,tempAddress.sin_port);
		if(tmpSocket == INVALID_SOCKET)
			return NULL;
		MySocket* retSocket = new MySocket(m_NetManger,sndBuffSize,recvBuffSize,socketRcvBuff,socketSndBuff);
		if (!retSocket)
		{
			return NULL;
		}
		retSocket->SetSocket(tmpSocket);
		retSocket->InitSocketBuffer();
		return retSocket;
	}

	bool MySocket::InitSocketBuffer()
	{
		if (!SocketOps::Nonblocking(m_Sock))
		{
			return false;
		}
		if (!SocketOps::DisableBuffering(m_Sock))
		{
		}
		if (!SocketOps::SetRecvBufferSize(m_Sock, m_SocketRcvBuff))
		{
			return false;
		}
		if (!SocketOps::SetSendBufferSize(m_Sock, m_SocketSndBuff))
		{
			return false;
		}
		return true;
	}


	bool MySocket::CreateSocket()
	{
#ifdef _WINDOWS
		m_Sock = SocketOps::CreateTCPFileDescriptor();
		if (m_Sock == INVALID_SOCKET)
		{
			return false;
		}
		return true;
#endif
	}

	SocketBase* MySocket::GetHandleSocket()
	{
		return static_cast<SocketBase*>(this);
	}

// 	void MySocket::GetHandleSocket()
// 	{
// 		MutexGuard guard(m_RecvMutex);
// 		OnRecv();
// 	}

	void MySocket::HandleOutput(void* pParam)
	{
		MutexGuard guard(m_SendMutex);
		CompleteOperator* pCompleteOperator = (CompleteOperator*)pParam;
		if (!pCompleteOperator )
		{
			return;
		}
		m_SendBuffer.Remove( pCompleteOperator->GetBytesTransferred() );
		IncreaseSendDataSizeTotal( pCompleteOperator->GetBytesTransferred() );

		if ( 0 != m_SendBuffer.GetSize() )
		{
			PostSendOperation();
		}
		else
		{
			m_Sending = false;
		}
	}

	void MySocket::HandleException(void* pParam)
	{
		Disconnect();
	}
	void MySocket::HandleTick(const uint64& tNow)
	{

	}
	void MySocket::HandleClose(void* pParam)
	{
		Disconnect();
	}

	void MySocket::HandleInput(void* pParam)
	{
		MutexGuard guard(m_RecvMutex);
		CompleteOperator* pCompleteOperator = (CompleteOperator*)pParam;
		if (!pCompleteOperator)
		{
			return;
		}
		if (pCompleteOperator->GetBytesTransferred() == 0)
		{
			Disconnect();//正常断开。。
		}
		else
		{
			m_RecvBuffer.IncrementWritten(pCompleteOperator->GetBytesTransferred());
			IncreaseRecvDataSizeTotal( pCompleteOperator->GetBytesTransferred() );
			Recv();
			PostRecvOperation();
		}
		
	}


} //namespace okey
