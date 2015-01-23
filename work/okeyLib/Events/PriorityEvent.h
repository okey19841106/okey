/********************************************************************
	created:	2015/01/23
	created:	16:58
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PRIORITY_EVENT_H__
#define __PRIORITY_EVENT_H__


namespace okey
{
	template <class TArgs, class TMutex = FastMutex> 
	class PriorityEvent: public AbstractEvent < TArgs,	PriorityStrategy<TArgs, AbstractPriorityDelegate<TArgs> >,	AbstractPriorityDelegate<TArgs>, TMutex >
	{
	public:
		PriorityEvent(){	}
		~PriorityEvent(){	}
	private:
		PriorityEvent(const PriorityEvent&);
		PriorityEvent& operator = (const PriorityEvent&);
	};
}

#endif