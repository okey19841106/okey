/********************************************************************
	created:	2013/06/07
	created:	7-6-2013   0:00
	author:		okey
	
	purpose:	IOCP
*********************************************************************/
#ifndef __IOCP_REACTOR_H__
#define __IOCP_REACTOR_H__

#include "NetReactor.h"


namespace okey
{

	class IOCPReactor : public NetReactor
	{
	public:
		IOCPReactor(int32 tNumThread);
		virtual ~IOCPReactor();
	public:
		virtual bool Open(int32 maxNumHandlers, uint32 tickInter);
		virtual void Close();
		virtual bool RegisterHandler(NetEventHandler* pHander, uint32 tEvent = NetEvent_All);
		virtual bool RemoveHandler(NetEventHandler* pHander, uint32 tEvent = NetEvent_All);
		virtual bool HandleEvent(const int64& tNow);
		virtual int32 GetHandlerNum()const;
	protected:
		int32 numOfThread;
		HANDLE completion_port;
		bool m_isOpen;
	};

}



#endif