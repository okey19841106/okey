/********************************************************************
	created:	2015/01/23
	created:	17:16
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PRIORITY_STRATEGY_H__
#define __PRIORITY_STRATEGY_H__

#include "SharedPtr.h"
#include "NotificationStrategy.h"
#include <vector>

namespace okey
{
	template <class TArgs, class TDelegate> 
	class PriorityStrategy: public NotificationStrategy<TArgs, TDelegate>
	{
	public:
		typedef SharedPtr<TDelegate>         DelegatePtr;
		typedef std::vector<DelegatePtr>     Delegates;
		typedef typename Delegates::iterator Iterator;
	public:
		PriorityStrategy(){}
		PriorityStrategy(const PriorityStrategy& s):_delegates(s._delegates){}
		~PriorityStrategy(){}
		PriorityStrategy& operator=(const PriorityStrategy& s)
		{
			if (&s != this)
			{
				_delegates = s._delegates;
			}
			return *this;
		}
		virtual void Notify(const void* sender, TArgs& arguments)
		{
			for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
			{
				(*it)->Notify(sender, arguments);
			}
		}
		virtual void Add(const TDelegate& delegate)
		{
			for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
			{
				if ((*it)->GetPriority() > delegate.GetPriority())
				{
					_delegates.insert(it, DelegatePtr(static_cast<TDelegate*>(delegate.Clone())));
					return;
				}
			}
			_delegates.push_back(DelegatePtr(static_cast<TDelegate*>(delegate.Clone())));
		}
		virtual void Remove(const TDelegate& delegate)
		{
			for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
			{
				if (delegate.Equals(**it))
				{
					(*it)->Disable();
					_delegates.erase(it);
					return;
				}
			}
		}
		virtual void Clear()
		{
			for (Iterator it = _delegates.begin(); it != _delegates.end(); ++it)
			{
				(*it)->Disable();
			}
			_delegates.Clear();
		}
		virtual bool IsEmpty() const
		{
			return _delegates.empty();
		}
	protected:
		Delegates _delegates;
	};
}

#endif