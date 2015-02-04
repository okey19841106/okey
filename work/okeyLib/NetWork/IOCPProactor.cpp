#include "PreCom.h"
#include "IOCPProactor.h"
#include "NetSession.h"

namespace okey
{

	IOCPProactor::IOCPProactor():_threadnum(0),completion_port(INVALID_HANDLE_VALUE),m_bOpen(false),m_HandlerNum(0)
	{

	}

	IOCPProactor::~IOCPProactor()
	{
		CloseHandle(completion_port);
	}

	bool IOCPProactor::Open(uint32 maxHandler, uint32 tickInter, uint32 numThread)
	{
		completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,numThread);
		if ( NULL == completion_port )
		{
			return false;
		}
		m_bOpen = true;
		return true;
	}

	void IOCPProactor::Close()
	{

	}

	bool IOCPProactor::RegisterHandler(Event_Handler* handler, uint32 events)
	{
		if (!m_bOpen)
		{
			return;
		}
		if (!handler)
		{
			return false;
		}
		NetSession* pSession = (NetSession*)handler->GetHandle();
		if (!pSession)
		{
			return false;
		}
		if ( NULL == CreateIoCompletionPort( (HANDLE)(pSession->GetSocket()),completion_port,(ULONG_PTR)handler,0))
		{
			return false;
		}
		++m_HandlerNum;
		return true;
	}

	void IOCPProactor::RemoveHander(Event_Handler* handler, uint32 events)
	{
		--m_HandlerNum;
	}

	bool IOCPProactor::HandleEvents()
	{
		CompleteOperator* pCompleteOperation = NULL;
		DWORD bytesTransferred = 0;
		NetSession* pSession = NULL;
		// Get the next asynchronous operation that completes
		BOOL result = GetQueuedCompletionStatus (completion_port,&bytesTransferred,	(PULONG_PTR)&pSession,(LPOVERLAPPED*)&pCompleteOperation,INFINITE);
		if (result == FALSE && pCompleteOperation == NULL) //严重的错误。
		{
			return false;
		}
		if (result == FALSE)
		{
			int32 error = Socket::GetSysError();
			if (error == ERROR_NETNAME_DELETED ) //对方强制断开连接，
			{
				pSession->HandleClose();
				return true;
			}
		}
		pSession->HandlerComplete(pCompleteOperation);
		return true;
	}

	int32 IOCPProactor::GetThreadNum() const
	{
		return _threadnum;
	}
}