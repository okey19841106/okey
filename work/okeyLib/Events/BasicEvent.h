/********************************************************************
	created:	2015/01/23
	created:	14:32
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_EVENT_H__
#define __BASE_EVENT_H__

#include "DefaultStrategy.h"
#include "AbstractEvent.h"
#include "Thread/Mutex.h"


namespace okey
{
	template <class TArgs, class TMutex = FastMutex> 
	class BasicEvent: public AbstractEvent<TArgs, DefaultStrategy<TArgs, AbstractDelegate<TArgs> >,	AbstractDelegate<TArgs>, TMutex>
	{
	public:
		BasicEvent(){}
		~BasicEvent(){}
	private:
		BasicEvent(const BasicEvent& e);
		BasicEvent& operator = (const BasicEvent& e);
	};
}

#endif