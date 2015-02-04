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
		CompleteOperator()
		{
			hEvent = 0;
			Internal = 0;
			InternalHigh = 0;
			Offset = 0;
			OffsetHigh = 0;
			nMask = 0;
		}
		~CompleteOperator(){}
		uint32 GetBytesTransferred(){return static_cast<uint32>( InternalHigh );}
		int32 nMask;
	};
}




#endif