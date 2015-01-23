/********************************************************************
	created:	2015/01/23
	created:	17:22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PRIORITY_EXPIRE_DELEGATE_H__
#define __PRIORITY_EXPIRE_DELEGATE_H__

#include "AbstractPriorityDelegate.h"

namespace okey
{
	template<typename TArgs>
	class PriorityExpireDelegate : public AbstractPriorityDelegate<TArgs>
	{
	public:
		PriorityExpireDelegate(const AbstractPriorityDelegate<TArgs>& p, int64 expireMillisecs):
		  AbstractPriorityDelegate<TArgs>(p), _pDelegate(static_cast<AbstractPriorityDelegate<TArgs>*>(p.Clone())),
			  _expire(expireMillisecs){}
		PriorityExpireDelegate(const PriorityExpireDelegate& e):
		  AbstractPriorityDelegate<TArgs>(e),_pDelegate(e._pDelegate->Clone()),_expire(e._expire),_creationTime(e._creationTime){}
		~ExpireDelegate()
		{
			if (_pDelegate)
			{
				delete _pDelegate;
				_pDelegate = NULL;
			}
		}
		PriorityExpireDelegate& operator = (const PriorityExpireDelegate& e)
		{
			if (&e != this)
			{
				delete _pDelegate;
				_pDelegate = e.Clone();
				_creationTime = e._creationTime;
				_expire = e._expire;
			}
			return *this;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			if (!expired())
				return this->_pDelegate->Notify(sender, arguments);
			else
				return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			return other.Equals(*_pDelegate);
		}
		virtual AbstractPriorityDelegate<TArgs>* Clone() const 
		{
			return new PriorityExpireDelegate(*this);
		}
		virtual void Disable()
		{
			_pDelegate->Disable();
		}
		virtual const AbstractPriorityDelegate<TArgs>* Unwrap() const			/// Returns the unwrapped delegate. Must be overridden by decorators like Expire.
		{
			return _pDelegate;
		}
	protected:
		bool expired() const
		{
			return _creationTime.isElapsed(_expire);
		}

		AbstractPriorityDelegate<TArgs>* _pDelegate;
		int64 _expire;
		TimeStamp _creationTime;
	private:
		ExpireDelegate();
	};
}

#endif