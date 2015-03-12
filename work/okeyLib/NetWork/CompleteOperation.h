/********************************************************************
	created:	2013/06/09
	created:	9-6-2013   0:33
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_COMPLETE_OPERAOTR_H__
#define __OKEY_COMPLETE_OPERAOTR_H__

#include "BaseClass.h"


namespace okey
{
	class CompleteOperator: public OVERLAPPED
	{
	public:
		enum CompleteOperatorEvent
		{
			IOCP_IVALID = -1,
			IOCP_EVENT_READ_COMPLETE = 0,
			IOCP_EVENT_WRITE_END = 1,
			IOCP_EVENT_CLOSE = 2,
		};
	public:
		CompleteOperator()
		{
			hEvent = 0;
			Internal = 0;
			InternalHigh = 0;
			Offset = 0;
			OffsetHigh = 0;
			byteTransfer = 0;
			nMask = IOCP_IVALID;
		}
		virtual ~CompleteOperator(){}
		uint32 GetBytesTransferred(){return static_cast<uint32>( byteTransfer );}
		DWORD byteTransfer;
		CompleteOperatorEvent nMask;
	};
}




#endif