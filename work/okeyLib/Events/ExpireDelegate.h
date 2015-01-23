/********************************************************************
	created:	2015/01/23
	created:	15:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __EXPIRE_DELEGATE_H__
#define __EXPIRE_DELEGATE_H__

namespace okey
{
	template<typename TArgs>
	class ExpireDelegate : public AbstractDelegate<TArgs>
	{
	public:
		ExpireDelegate(const AbstractDelegate<TArgs>& p, int64 expireMillisecs):_pDelegate(p.Clone()),_expire(expireMillisecs){}
		ExpireDelegate(const ExpireDelegate& e):AbstractDelegate<TArgs>(e),
			_pDelegate(e._pDelegate->Clone()),_expire(e._expire),_creationTime(e._creationTime){}
		~ExpireDelegate()
		{
			if (_pDelegate)
			{
				delete _pDelegate;
				_pDelegate = NULL;
			}
		}
		ExpireDelegate& operator = (const ExpireDelegate& e)
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
		virtual AbstractDelegate* Clone() const 
		{
			return new ExpireDelegate(*this);
		}
		virtual void Disable()
		{
			_pDelegate->Disable();
		}
		virtual const AbstractDelegate* Unwrap() const			/// Returns the unwrapped delegate. Must be overridden by decorators like Expire.
		{
			return _pDelegate;
		}
	protected:
		bool expired() const
		{
			return _creationTime.isElapsed(_expire);
		}

		AbstractDelegate<TArgs>* _pDelegate;
		int64 _expire;
		TimeStamp _creationTime;
	private:
		ExpireDelegate();
	};
}

#endif