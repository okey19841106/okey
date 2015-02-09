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

	bool IOCPProactor::Open(uint32 maxHandler, uint32 numThread)
	{
		completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,numThread);
		if ( NULL == completion_port )
		{
			return false;
		}
		m_bOpen = true;
		_threadnum = numThread;
		return true;
	}

	void IOCPProactor::Close()
	{
		for(int i = 0; i < _threadnum; ++i)
		{
			CompleteOperator* ov = new CompleteOperator;
			if (!ov)
			{
				return;
			}
			ov->nMask = CompleteOperator::IOCP_EVENT_CLOSE;
			PostQueuedCompletionStatus(completion_port, 0, (ULONG_PTR)0, (LPOVERLAPPED)&ov);
		}
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
		Event_Handler* pHandler = NULL;
		// Get the next asynchronous operation that completes
		BOOL result = GetQueuedCompletionStatus (completion_port,&bytesTransferred,	(PULONG_PTR)&pHandler,(LPOVERLAPPED*)&pCompleteOperation,INFINITE);
		if (result)
		{
			if (pHandler)
			{
				if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_READ_COMPLETE)
				{
					pHandler->HandleInput((void*)pCompleteOperation);
				}
				else if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_WRITE_END)
				{
					pHandler->HandleOutput((void*)pCompleteOperation);
				}
				else
				{
					pHandler->HandleClose();
				}
			}
			else//关闭这个东西了。。
			{
				delete pCompleteOperation;
				pCompleteOperation = NULL;
				return false;
			}
		}
		else
		{
			int32 error = Socket::GetSysError();//ERROR_NETNAME_DELETED 远程主机断开连接。。。
			if (pHandler)
			{
				pHandler->HandleClose();
			}
		}
		return true;
	}

	int32 IOCPProactor::GetThreadNum() const
	{
		return _threadnum;
	}
}