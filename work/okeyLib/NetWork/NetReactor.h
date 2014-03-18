/********************************************************************
	created:	2013/06/06
	created:	6-6-2013   22:42
	author:		okey
	
	purpose:	反应堆模型
*********************************************************************/


#ifndef __NET_REACTOR_H__
#define __NET_REACTOR_H__


namespace okey
{
	enum NetEventMask
	{
		NetEvent_In = 1 << 0,
		NetEvent_Out = 1 << 1,
		NetEvent_Exception = 1 << 2,
		NetEvent_IO = NetEvent_In | NetEvent_Out | NetEvent_Exception,
		NetEvent_Tick = 1 << 3,
		NetEvent_All = NetEvent_IO | NetEvent_Tick,
	};
	
	class SocketBase;
	class NetReactor;


	class NetEventHandler
	{
	public:
		NetEventHandler():m_pReactor(NULL),m_Mask(0),m_TimeOut(0){}
		virtual ~NetEventHandler(){}
	public:
		virtual SocketBase* GetHandleSocket() = 0;
		virtual void HandleInput(void* pParam) = 0;
		virtual void HandleOutput(void* pParam) = 0;
		virtual void HandleException(void* pParam) = 0;
		virtual void HandleTick(const uint64& tNow){};
		virtual void HandleClose(void* pParam) = 0;
	public:
		void SetReactor(NetReactor* pReactor){m_pReactor = pReactor;}
		NetReactor* GetReactor()const{return m_pReactor;}
		void SetEventMask(uint32 mask){m_Mask = mask;}
		uint32 GetEventMask()const{return m_Mask;}
		void SetTimeOut(uint64 tTimeOut){m_TimeOut=tTimeOut;}
		uint64 GetTimeOut()const{return m_TimeOut;}
	protected:
		NetReactor* m_pReactor;
		uint32 m_Mask;
		uint64 m_TimeOut;
	};

	class NetReactor
	{
	public:
		NetReactor(){}
		virtual ~NetReactor(){}
	public:
		virtual bool Open(int32 maxNumHandlers, uint32 tickInter) = 0;
		virtual void Close() = 0;
		virtual bool RegisterHandler(NetEventHandler* pHander, uint32 tEvent = NetEvent_All) = 0;
		virtual bool RemoveHandler(NetEventHandler* pHander, uint32 tEvent = NetEvent_All) = 0;
		virtual bool HandleEvent(const int64& tNow) = 0;
		virtual int32 GetHandlerNum()const = 0;
	};

}


#endif