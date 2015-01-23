/********************************************************************
	created:	2015/01/23
	created:	14:26
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ABSTRACT_PRIOTITY_DELEGATE_H_
#define __ABSTRACT_PRIOTITY_DELEGATE_H_


#include "AbstractDelegate.h"

namespace okey
{
	template<typename TArgs>
	class AbstractPriorityDelegate : public AbstractDelegate<TArgs>
	{
	public:
		AbstractPriorityDelegate(int prio):_priority(prio){}
		AbstractPriorityDelegate(const AbstractPriorityDelegate& del):AbstractDelegate<TArgs>(del),	_priority(del._priority){}
		virtual ~AbstractPriorityDelegate() {}
		int32 GetPriority() const{return _priority;}
	protected:
		int32 _priority;
	};
}

#endif