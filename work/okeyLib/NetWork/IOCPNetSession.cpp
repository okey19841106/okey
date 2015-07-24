#include "PreCom.h"
#include "IOCPNetSession.h"

namespace okey
{
	IOCPNetSession::IOCPNetSession(NetServiceBase* pNetService, Event_Actor* pActor):NetSession(pNetService,pActor)
	{

	}
	IOCPNetSession::~IOCPNetSession()
	{

	}

	void IOCPNetSession::HandleInput(void* p)
	{
		CompleteOperator *pCom = (CompleteOperator *)p;
		if (pCom->GetBytesTransferred() == 0)
		{
			char buffer[RECV_BLOCK_SIZE];
			if (m_Socket.Recv(buffer,RECV_BLOCK_SIZE) == 0)
			{
				Disconnect();//Õý³£¶Ï¿ª¡£¡£
				return;
			}
			int32 a = 0;
		}
		else
		{
			m_RecvBuffer.IncrementWritten(pCom->GetBytesTransferred());
			OnRecv();
		}
		PostReadEvent();
	}

	void IOCPNetSession::HandleOutput(void* p)
	{
		CompleteOperator *pCom = (CompleteOperator *)p;
		{
			FastMutex::ScopedLock lock(m_SendMutex);
			m_SendBuffer.Remove(pCom->GetBytesTransferred());
		}
		if (m_SendBuffer.GetContiguiousBytes() > 0)
		{
			PostWriteEvent();
		}
		else
		{
			m_bSend = false;
		}
	}

	void IOCPNetSession::PostReadEvent()
	{
		FastMutex::ScopedLock lock(m_RecvMutex);
		WSABUF buf;
		buf.len = m_RecvBuffer.GetSpace();
		buf.buf = (char*)m_RecvBuffer.GetBuffer();
		DWORD len = 0;
		DWORD flag = 0;
		m_RecvOverLapped.nMask = CompleteOperator::IOCP_EVENT_READ_COMPLETE;
		m_RecvOverLapped.pHandler = this;
		if (WSARecv(m_Socket.GetSocket(), &buf, 1, &len, &flag, &m_RecvOverLapped, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				Disconnect();
			}
		}
	}
	void IOCPNetSession::PostWriteEvent()
	{
		FastMutex::ScopedLock lock(m_SendMutex);
		WSABUF buf;
		buf.len = m_SendBuffer.GetContiguiousBytes();
		buf.buf = (char*)m_SendBuffer.GetBufferStart();
		DWORD len = 0;
		DWORD flag = 0;
		m_SendOverLapped.pHandler = this;
		if (SOCKET_ERROR == WSASend(m_Socket.GetSocket(),&buf,1, &len, flag, &m_SendOverLapped,0))
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				Disconnect();
			}
		}
	}

	int32 IOCPNetSession::SendData(const char* buff, int32 len)
	{
		if (m_State == e_DisConnected)
		{
			return -1;
		}
		int32 ret = -1;
		{
			FastMutex::ScopedLock lock(m_SendMutex);
			if( m_SendBuffer.GetSpace() > len )
			{
				m_SendBuffer.Write((void*)buff, len );
				PostWriteEvent();
				return len;
			}
			return -1;
		}
	}

}