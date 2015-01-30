/********************************************************************
	created:	2015/01/28
	created:	18:14
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NET_SERVICE_BASE_H__
#define __NET_SERVICE_BASE_H__

#include "Types.h"

namespace okey
{
	class SocketAddr;
	class SessionBase;

	struct NetServiceParam
	{
		NetServiceParam()
		{
			_threadConnNum = 1;
			_threadConMaxSize = 512;
			_tickInterval = 10;
			_sysSendBuff = 65535;
			_sysRecvBuff = 65535;
			_maxRecvSize = 0;
			_maxSendSize = 0;
			backlog = 512;
			_threadConMaxSize = 256;

		}
		//void Check();
		uint32 _threadConnNum; //���������߳�����
		uint32 _maxConNum;//���������
		uint32 _tickInterval;//���������¼�tickʱ��
		uint32 _sysSendBuff; //���ͻ������ڴ�С
		uint32 _sysRecvBuff; //���ܻ������ڴ�С
		uint32 _maxSendSize; // ���ͻ�������С
		uint32 _maxRecvSize; //���ջ�������С
		uint32 _threadConMaxSize; //�����̴߳�������������
		uint32 backlog;
	};

	class NetServiceBase
	{
	public:
		NetServiceBase(){}
		virtual ~NetServiceBase(){};
		virtual bool StartUp() = 0;
		virtual void ShutDown() = 0;
		virtual uint32 GetID() const = 0;
		virtual bool OnConnect(SessionBase* pSession)=0;
		virtual bool OnAccept(SessionBase* pSession)=0;
		virtual bool OnDisconnect(SessionBase* pSession)=0;
		virtual bool OnSend()=0;
		virtual bool OnRecv()=0;
		virtual bool Run()=0;
		virtual SessionBase* Connect(const SocketAddr& addr)=0;
		virtual bool BindAddress(const SocketAddr& addr) = 0;
		virtual bool Accept(const char* ip, int32 port)=0;
		virtual SessionBase* GetSession(int32 id) = 0;
		virtual bool Disconnect(int32 scoketid)=0;
		//virtual bool ProcessPacket(PacketBase* pkt) = 0;
		//virtual void SetPacketProcess(PacketProcessEx* pktpoc) = 0;
		//virtual PacketProcessEx* GetPacketProcess() = 0;
		virtual SessionBase* Connect(uint32 id, const SocketAddr& addr) = 0;
		const NetServiceParam& GetParam() const = 0;
	protected:
	private:
	};
}

#endif