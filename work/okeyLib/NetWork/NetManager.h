/********************************************************************
	created:	2013/05/26
	created:	26-5-2013   20:12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NET_MANAGER_H_COMPELETE__
#define __NET_MANAGER_H_COMPELETE__

#include "Types.h"
#include "NetManagerBase.h"
#include "CircleList.h"
#include "Fuction.h"
#include "Thread/Mutex.h"
#include <vector>


namespace okey
{

#define MAX_SOCKET_LIST 128

	class SocketBase;
	class PacketBase;
	class PacketProcess;
	class NetReactor;
	class Thread;

	class NetManager: public NetManagerBase
	{
	public:
		NetManager(int32 numThread,int32 skRcv,int32 stRcv,int32 skSnd, int32 stSnd,
			CFunctionArg1Base<int32>* AptFun,CFunctionArg1Base<int32>* conFun,
			CFunctionArg1Base<int32>* DisFun);
		~NetManager();
		virtual bool OnConnect(SocketBase* pSession);
		virtual bool OnAccept(SocketBase* pSession);
		virtual bool OnDisconnect(SocketBase* pSession);
		virtual bool OnSend();
		virtual bool OnRecv();
		virtual bool Run();
		
		virtual SocketBase* Connect(const char* ip,int32 port);
		virtual bool Accept(const char* ip, int32 port);
		virtual SocketBase* GetSocket(int32 scoketid);
		virtual bool Disconnect(int32 scoketid);
		virtual bool ProcessPacket(PacketBase* pkt);
		virtual void SetPacketProcess(PacketProcessEx* pktpoc)
		{
			m_pktProc = pktpoc;
		}
		virtual void StartWorkThread();
		virtual void StopWorkThread();
		PacketProcessEx* GetPacketProcess(){return m_pktProc;}
		void ProcessDelSockets();
	protected:
#ifdef	WINDOWS
		bool RunWindowsIOCP();
#else
		bool RunLinuxEpoll();
#endif
	private:
		void ThreadRun();
		void RunAccept();
		std::string m_ip;
		int32 m_port;
		int32 m_numThread;
		Thread *m_aptThread;
	//	SOCKET m_ListenSock;
		SocketBase* m_pListenSocket;
		CircleList<SocketBase*, MAX_SOCKET_LIST> m_SocketList;
		CircleList<SocketBase*, MAX_SOCKET_LIST> m_DelList;
		int32 m_socketRcvSize;
		int32 m_socketSndSize;
		int32 m_streamRcvSize;
		int32 m_streamSndSize;
		CFunctionArg1Base<int32>* m_ConFun;
		CFunctionArg1Base<int32>* m_AptFun;
		CFunctionArg1Base<int32>* m_DisFun;
		Mutex m_Mutex;
		Mutex m_DelMutex;
		PacketProcessEx* m_pktProc;
		NetReactor* m_pReactor;
		std::vector<Thread*> m_Threads;
		bool m_isThreadExit;
	};
}




#endif