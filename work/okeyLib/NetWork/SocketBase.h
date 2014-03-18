/********************************************************************
	created:	2012/12/14
	created:	14-12-2012   23:01
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__

#include "Types.h"
#include "Thread/Mutex.h"
#include "CircularBuffer.h"
#include <WinSock2.h>

namespace okey
{
	class PacketBase;
	class CircularBuffer;
	class NetManagerBase;

	class SocketBase
	{
	public:
		SocketBase();
		virtual ~SocketBase(){}
		inline bool Sending() const{return m_Sending;}
		inline void SetSending( bool sending ){m_Sending = sending;}
		inline uint32 GetSendingDataSize() const{return m_SendingDataSize;}
		inline int32 GetID() const{return m_ID;}
		inline const std::string& GetIP() const{return m_IP;}
		inline int32 GetPort() const{return m_Port;}
		inline void SetID(int32 id){m_ID = id;}
//		NetManagerBase* GetNetManger(){return m_NetManger;}
		inline uint32 GetSendDataSizeTotal() const{return m_SendDataSizeTotal;}
		void IncreaseSendDataSizeTotal( uint32 sizeIncreased );
		inline uint32 GetRecvDataSizeTotal() const{return m_RecvDataSizeTotal;}
		void IncreaseRecvDataSizeTotal( uint32 sizeIncreased );
	
		//锁操作。
		Mutex& GetRecvLock(){return m_RecvMutex;}
		Mutex& GetSendLock(){return m_SendMutex;}
		void RecvLock(){m_RecvMutex.Lock();}
		void RecvUnLock(){m_RecvMutex.UnLock();}
		void SendLock(){m_SendMutex.Lock();}
		void SendUnLock(){m_SendMutex.UnLock();}
		//socket
		virtual void SetSocket(SOCKET s){}
		virtual SOCKET GetSocket(){return -1;}


		//实际的操作，发包，收报，发送等。
		virtual bool CreateSocket(){return false;}
		virtual bool Listen(const std::string& ip, int32 port){return false;}
		virtual bool Connect(const std::string& ip, int32 port){return false;}
		virtual bool Recv(){return false;}
		virtual bool SendBuffer( void* pData, uint32 size ){return false;}
		virtual bool SendPacket(PacketBase* pkt){return false;}
		virtual void Disconnect(){return;}
		virtual PacketBase* RecvPacket(){return NULL;}
		virtual void OnSend(){}
		virtual void OnDisconnect(){}
		virtual void OnRecv(){}
		virtual void OnConnect(){}
		virtual SocketBase* Accept(uint32 sndBuffSize, uint32 recvBuffSize, int32 socketRcvBuff, int32 socketSndBuff ){return NULL;}
		
	protected:
		bool m_Sending;
		int32 m_ID;
		std::string m_IP;
		int32 m_Port;
		uint32 m_SendingDataSize;
		uint32 m_SendDataSizeTotal;
		uint32 m_RecvDataSizeTotal;
		Mutex m_RecvMutex; //两个锁。
		Mutex m_SendMutex;
		
		

	};
}

#endif