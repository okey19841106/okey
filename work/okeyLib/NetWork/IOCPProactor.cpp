#include "PreCom.h"
#include "IOCPProactor.h"
#include "NetSession.h"

namespace okey
{

	IOCPProactor::IOCPProactor():_threadnum(0),m_bOpen(false),m_HandlerNum(0)
	{

	}

	IOCPProactor::~IOCPProactor()
	{
		//CloseHandle(completion_port);
	}

	bool IOCPProactor::Open(uint32 maxHandler, uint32 numThread)
	{
// 		completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,numThread);
// 		if ( NULL == completion_port )
// 		{
// 			return false;
// 		}
		m_bOpen = true;
		_threadnum = numThread;
		return true;
	}

	void IOCPProactor::Close()
	{
// 		for(int i = 0; i < _threadnum; ++i)
// 		{
// 			CompleteOperator* ov = new CompleteOperator;
// 			if (!ov)
// 			{
// 				return;
// 			}
// 			ov->nMask = CompleteOperator::IOCP_EVENT_CLOSE;
// 			PostQueuedCompletionStatus(completion_port, 0, (ULONG_PTR)0, (LPOVERLAPPED)ov);
// 		}
	}

	bool IOCPProactor::RegisterHandler(Event_Handler* handler, uint32 events)
	{
		if (!m_bOpen)
		{
			return false;
		}
		if (!handler)
		{
			return false;
		}
// 		if ( NULL == CreateIoCompletionPort( handler->GetHandle(),completion_port,(ULONG_PTR)handler,0))
// 		{
// 			return false;
// 		}
		if (!BindIoCompletionCallback(handler->GetHandle(),_HandleEvents,0))
		{
			return false;
		}
		handler->PostReadEvent();
		++m_HandlerNum;
		return true;
	}

	void IOCPProactor::RemoveHander(Event_Handler* handler, uint32 events)
	{
		CompleteOperator *pov = new CompleteOperator;
		pov->nMask = CompleteOperator::IOCP_EVENT_CLOSE;
		//PostQueuedCompletionStatus(completion_port, 0, (ULONG_PTR)handler, (LPOVERLAPPED)pov);
		--m_HandlerNum;
		handler->HandleClose();
	}

	bool IOCPProactor::HandleEvents()
	{
// 		LPOVERLAPPED pOverLapped = NULL;
// 		
// 		DWORD bytesTransferred = 0;
// 		Event_Handler* pHandler = NULL;
// 		// Get the next asynchronous operation that completes
// 		BOOL result = GetQueuedCompletionStatus (completion_port,&bytesTransferred,	(PULONG_PTR)&pHandler,&pOverLapped,INFINITE);
// 		if (result)
// 		{
// 			CompleteOperator* pCompleteOperation = (CompleteOperator*)pOverLapped;
// 			pCompleteOperation->byteTransfer = bytesTransferred;
// 			if (pHandler)
// 			{
// 				if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_READ_COMPLETE)
// 				{
// 					pHandler->HandleInput((void*)pCompleteOperation);
// 				}
// 				else if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_WRITE_END)
// 				{
// 					pHandler->HandleOutput((void*)pCompleteOperation);
// 				}
// 				else if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_CLOSE)
// 				{
// 					delete pOverLapped;
// 					pOverLapped = NULL;
// 					pHandler->HandleClose();
// 				}
// 			}
// 			else//关闭这个东西了。。
// 			{
// 				delete pCompleteOperation;
// 				pCompleteOperation = NULL;
// 				return false;
// 			}
// 		}
// 		else
// 		{
// 			int32 error = Socket::GetSysError();//ERROR_NETNAME_DELETED 远程主机断开连接。。。
// 			if (pHandler)
// 			{
// 				pHandler->HandleClose();
// 			}
// 		}
		return true;
	}

	int32 IOCPProactor::GetThreadNum() const
	{
		return _threadnum;
	}

#ifdef WINDOWS
	void CALLBACK IOCPProactor::_HandleEvents(DWORD dwErrCode, DWORD dwTransed, LPOVERLAPPED param)
	{
		CompleteOperator* pCompleteOperation = (CompleteOperator*)param;
		//assert()
		pCompleteOperation->byteTransfer = dwTransed;
		Event_Handler* pHandler = pCompleteOperation->pHandler;
		//assert()
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
			else if (pCompleteOperation->nMask == CompleteOperator::IOCP_EVENT_CLOSE)
			{
				delete param;
				param = NULL;
				pHandler->HandleClose();
			}
		}
		else//关闭这个东西了。。
		{
			delete pCompleteOperation;
			pCompleteOperation = NULL;
			return;
		}
	}
#endif
	
}