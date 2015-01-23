/********************************************************************
	created:	2015/01/23
	created:	14:35
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DEFALUT_STRATEGY_H__
#define __DEFALUT_STRATEGY_H__

#include "NotificationStrategy.h"

namespace okey
{
	template <class TArgs, class TDelegate> 
	class DefaultStrategy: public NotificationStrategy<TArgs, TDelegate>
	{
	public:
		typedef SharedPtr<TDelegate>         DelegatePtr;
		typedef std::vector<DelegatePtr>     Delegates;
		typedef typename Delegates::iterator Iterator;
	public:
		DefaultStrategy(){}
		DefaultStrategy(const DefaultStrategy& s):_delegates(s._delegates){}
		~DefaultStrategy(){}
		DefaultStrategy& operator=(const DefaultStrategy& s)
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