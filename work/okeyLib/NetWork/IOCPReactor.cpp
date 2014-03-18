#include "PreCom.h"
#include "IOCPReactor.h"
#include "SocketBase.h"
#include "CompleteOperation.h"
#include "SocketOps.h"
#include "HelperFunction.h"

namespace okey
{

	IOCPReactor::IOCPReactor(int32 tNumThread):numOfThread(tNumThread),m_isOpen(false)
	{
		
	}

	IOCPReactor::~IOCPReactor()
	{
		CloseHandle(completion_port);
	}

	bool IOCPReactor::Open(int32 maxNumHandlers, uint32 tickInter)
	{
		completion_port = CreateIoCompletionPort(
			INVALID_HANDLE_VALUE,
			NULL,
			0,
			numOfThread //单核应该是2个线程
			);
		if ( NULL == completion_port )
		{
			return false;
		}
		m_isOpen = true;
		return true;
	}

	void IOCPReactor::Close()
	{
		for(int i = 0; i < numOfThread; ++i)
		{
			CompleteOperator* ov = new CompleteOperator;
			if (!ov)
			{
				return;
			}
			ov->nMask = NetEvent_Exception;
			PostQueuedCompletionStatus(completion_port, 0, (ULONG_PTR)0, (LPOVERLAPPED)&ov);
		}
	}

	bool IOCPReactor::RegisterHandler(NetEventHandler* pHander, uint32 tEvent)
	{
		if (!pHander)
		{
			return false;
		}
		SocketBase* pSocket = pHander->GetHandleSocket();
		if (!pSocket)
		{
			return false;
		}
		if ( NULL == CreateIoCompletionPort( (HANDLE)pSocket->GetSocket(),completion_port,(ULONG_PTR)pHander,0))
		{
			return false;
		}
		pHander->SetReactor(this);
		return true;
	}

	bool IOCPReactor::RemoveHandler(NetEventHandler* pHander, uint32 tEvent)
	{
		if (!pHander)
		{
			return false;
		}
		return true;
	}

	bool IOCPReactor::HandleEvent(const int64& tNow)
	{
		CompleteOperator* pCompleteOperation = NULL;
		DWORD bytesTransferred = 0;
		NetEventHandler* pHandler = NULL;

		// Get the next asynchronous operation that completes
		BOOL result = GetQueuedCompletionStatus (completion_port,
			&bytesTransferred,
			(PULONG_PTR)&pHandler,
			(LPOVERLAPPED*)&pCompleteOperation,
			INFINITE);
		if (result == FALSE && pCompleteOperation == NULL) //严重的错误。
		{
			int32 error = SocketOps::GetLastError();
			std::string szerr = FormatErrorMessage(error);
			printf("%s\n", szerr.c_str());
			return false;
		}
		else if (pHandler != NULL)
		{
			if (result == FALSE)
			{
				int32 error = SocketOps::GetLastError();
				if (error == ERROR_NETNAME_DELETED ) //对方强制断开连接，
				{
					pHandler->HandleClose(pCompleteOperation);
					return true;
				}

				std::string szerr = FormatErrorMessage(error);
				printf("%s\n", szerr.c_str());
				return false;
			}
			if (pCompleteOperation->nMask & NetEvent_In)
			{
				pHandler->HandleInput(pCompleteOperation);
			}
			if (pCompleteOperation->nMask & NetEvent_Out)
			{
				pHandler->HandleOutput(pCompleteOperation);
			}
			if (pCompleteOperation->nMask & NetEvent_Exception)
			{
				pHandler->HandleException(pCompleteOperation);
			}
		}
		return true;
	}

	int32 IOCPReactor::GetHandlerNum()const
	{
		return -1;
	}
}