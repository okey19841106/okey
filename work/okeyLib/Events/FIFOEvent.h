/********************************************************************
	created:	2015/01/23
	created:	15:52
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FIFO_EVENT_H__
#define __FIFO_EVENT_H__

#include "AbstractEvent.h"
#include "FIFOStrategy.h"
#include "Thread/Mutex.h"

namespace okey
{
	template <class TArgs, class TMutex = FastMutex> 
	class FIFOEvent: public AbstractEvent < TArgs, FIFOStrategy<TArgs, AbstractDelegate<TArgs> >, AbstractDelegate<TArgs>, TMutex>
	{
	public:
		FIFOEvent()	{}
		~FIFOEvent(){}
	private:
		FIFOEvent(const FIFOEvent& e);
		FIFOEvent& operator = (const FIFOEvent& e);
	};
}

#endif