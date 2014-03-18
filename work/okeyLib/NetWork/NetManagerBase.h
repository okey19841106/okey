/********************************************************************
	created:	2013/12/08
	created:	8-12-2013   23:19
	author:		okey
	
	purpose:	
*********************************************************************/

#include "Types.h"


namespace okey
{



	class SocketBase;
	class PacketBase;
	class PacketProcessEx;

	class NetManagerBase
	{
	public:
		NetManagerBase(){}
		virtual ~NetManagerBase(){};
		virtual bool OnConnect(SocketBase* pSession)=0;
		virtual bool OnAccept(SocketBase* pSession)=0;
		virtual bool OnDisconnect(SocketBase* pSession)=0;
		virtual bool OnSend()=0;
		virtual bool OnRecv()=0;
		virtual bool Run()=0;
		virtual SocketBase* Connect(const char* ip,int32 port)=0;
		virtual bool Accept(const char* ip, int32 port)=0;
		virtual SocketBase* GetSocket(int32 socketid){return NULL;}
		virtual bool Disconnect(int32 scoketid)=0;
		virtual bool ProcessPacket(PacketBase* pkt) = 0;
		virtual void SetPacketProcess(PacketProcessEx* pktpoc) = 0;
		virtual PacketProcessEx* GetPacketProcess() = 0;
		virtual void StartWorkThread()=0;
		virtual void StopWorkThread()=0;
	protected:
	private:
	};
}