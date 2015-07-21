/********************************************************************
	created:	2015/07/20
	created:	16:20
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __IOCP_NETSESSION_H__
#define __IOCP_NETSESSION_H__

#include "NetSession.h"

namespace okey
{
	class IOCPNetSession: public NetSession
	{
	public:
		IOCPNetSession(NetServiceBase* pNetService, Event_Actor* pActor);
		~IOCPNetSession();

		int32 SendData(const char* buff, int32 len);
		void PostReadEvent();
		void PostWriteEvent();
		void HandleInput(void* p);
		void HandleOutput(void* p);
	protected:
		WSABUF m_SendWSABuf;
		WSABUF m_RecvWSABuf;
		CompleteOperator m_SendOverLapped;
		CompleteOperator m_RecvOverLapped;
		CompleteOperator m_CloseOverLapped;
		bool m_bSend;

	};
}

#endif