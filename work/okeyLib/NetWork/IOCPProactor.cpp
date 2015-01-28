#include "PreCom.h"
#include "IOCPProactor.h"


namespace okey
{

	IOCPProactor::IOCPProactor():_threadnum(0),completion_port(INVALID_HANDLE_VALUE),m_bOpen(false)
	{

	}

	IOCPProactor::~IOCPProactor()
	{

	}

	bool IOCPProactor::Open(uint32 numThread)
	{
		completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,numThread);
		if ( NULL == completion_port )
		{
			return false;
		}
		m_bOpen = true;
		return true;
	}

	void IOCPProactor::Open()
	{

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
		void* pHandler = handler->GetHandle();
		if (!pHandler)
		{
			return false;
		}
		
		if ( NULL == CreateIoCompletionPort( (HANDLE)(*pHandler),completion_port,(ULONG_PTR)handler,0))
		{
			return false;
		}
		
		return true;
	}

	void IOCPProactor::RemoveHander(Event_Handler* handler, uint32 events)
	{

	}

	bool IOCPProactor::HandleEvents(const TimeStamp& now)
	{
		OVERLAPPED* pCompleteOperation = NULL;
		DWORD bytesTransferred = 0;
		Event_Handler* pHandler = NULL;

		// Get the next asynchronous operation that completes
		BOOL result = GetQueuedCompletionStatus (completion_port,
			&bytesTransferred,
			(PULONG_PTR)&pHandler,
			&pCompleteOperation,
			now.MilliSecond());
		if (result == FALSE && pCompleteOperation == NULL) //ÑÏÖØµÄ´íÎó¡£
		{
			int32 error = SocketOps::GetLastError();
			std::string szerr = FormatErrorMessage(error);
			printf("%s\n", szerr.c_str());
			return false;
		}
		else if (pHandler != NULL)
		{
		}
	}

	int32 IOCPProactor::GetThreadNum() const
	{
		return _threadnum;
	}
}