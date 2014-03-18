#include "PreCom.h"
#include "CompleteOperation.h"


namespace okey
{
	CompleteOperator::CompleteOperator()
	{
		hEvent = 0;
		Internal = 0;
		InternalHigh = 0;
		Offset = 0;
		OffsetHigh = 0;
		nMask = 0;
	}

	CompleteOperator::~CompleteOperator()
	{
		
	}
}