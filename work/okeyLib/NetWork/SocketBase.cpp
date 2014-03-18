#include "PreCom.h"
#include "SocketBase.h"

namespace okey
{

	SocketBase::SocketBase():m_Sending(false),m_SendDataSizeTotal(0),m_RecvDataSizeTotal(0)
	{
		
	}



	void SocketBase::IncreaseSendDataSizeTotal( uint32 sizeIncreased )
	{
		m_SendDataSizeTotal += sizeIncreased;
	}


	void SocketBase::IncreaseRecvDataSizeTotal( uint32 sizeIncreased )
	{
		m_RecvDataSizeTotal += sizeIncreased;
	}

}