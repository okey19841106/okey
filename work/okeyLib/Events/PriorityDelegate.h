/********************************************************************
	created:	2015/01/23
	created:	17:33
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PRIORITY_DELEGATE_H__
#define __PRIORITY_DELEGATE_H__

#include "AbstractPriorityDelegate.h"
#include "Thread/Mutex.h"

namespace okey
{
	template <class TObj, class TArgs, bool useSender = true> 
	class PriorityDelegate: public AbstractPriorityDelegate<TArgs>
	{
	public:
		typedef void (TObj::*NotifyMethod)(const void*, TArgs&);

		PriorityDelegate(TObj* obj, NotifyMethod method, int prio):
		AbstractPriorityDelegate<TArgs>(prio),
			_receiverObject(obj),
			_receiverMethod(method)
		{
		}

		PriorityDelegate(const PriorityDelegate& delegate):
		AbstractPriorityDelegate<TArgs>(delegate),
			_receiverObject(delegate._receiverObject),
			_receiverMethod(delegate._receiverMethod)
		{
		}

		PriorityDelegate& operator = (const PriorityDelegate& delegate)
		{
			if (&delegate != this)
			{
				this->_receiverObject = delegate._receiverObject;
				this->_receiverMethod = delegate._receiverMethod;
				this->_priority       = delegate._priority;
			}
			return *this;
		}

		~PriorityDelegate()
		{
		}

		bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_receiverObject)
			{
				(_receiverObject->*_receiverMethod)(sender, arguments);
				return true; 
			}
			else return false;
		}

		bool Equals(const AbstractDelegate<TArgs>& other) const
		{
			const PriorityDelegate* pOtherDelegate = dynamic_cast<const PriorityDelegate*>(other.unwrap());
			return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
		}

		AbstractDelegate<TArgs>* Clone() const
		{
			return new PriorityDelegate(*this);
		}

		void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_receiverObject = 0;
		}

	protected:
		TObj*        _receiverObject;
		NotifyMethod _receiverMethod;
		Mutex _mutex;

	private:
		PriorityDelegate();
	};


	template <class TObj, class TArgs> 
	class PriorityDelegate<TObj, TArgs, false>: public AbstractPriorityDelegate<TArgs>
	{
	public:
		typedef void (TObj::*NotifyMethod)(TArgs&);

		PriorityDelegate(TObj* obj, NotifyMethod method, int prio):
		AbstractPriorityDelegate<TArgs>(prio),
			_receiverObject(obj),
			_receiverMethod(method)
		{
		}

		PriorityDelegate(const PriorityDelegate& delegate):
		AbstractPriorityDelegate<TArgs>(delegate),
			_receiverObject(delegate._receiverObject),
			_receiverMethod(delegate._receiverMethod)
		{
		}

		PriorityDelegate& operator = (const PriorityDelegate& delegate)
		{
			if (&delegate != this)
			{
				this->_receiverObject = delegate._receiverObject;
				this->_receiverMethod = delegate._receiverMethod;
				this->_priority       = delegate._priority;
			}
			return *this;
		}

		~PriorityDelegate()
		{
		}

		bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_receiverObject)
			{
				(_receiverObject->*_receiverMethod)(arguments);
				return true;
			}
			return false;
		}

		bool Equals(const AbstractDelegate<TArgs>& other) const
		{
			const PriorityDelegate* pOtherDelegate = dynamic_cast<const PriorityDelegate*>(other.unwrap());
			return pOtherDelegate && this->priority() == pOtherDelegate->priority() && _receiverObject == pOtherDelegate->_receiverObject && _receiverMethod == pOtherDelegate->_receiverMethod;
		}

		AbstractDelegate<TArgs>* Clone() const
		{
			return new PriorityDelegate(*this);
		}

		void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_receiverObject = 0;
		}

	protected:
		TObj*        _receiverObject;
		NotifyMethod _receiverMethod;
		Mutex _mutex;

	private:
		PriorityDelegate();
	};

	template <class TObj, class TArgs>
	static PriorityDelegate<TObj, TArgs, true> GetPriorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int prio)
	{
		return PriorityDelegate<TObj, TArgs, true>(pObj, NotifyMethod, prio);
	}


	template <class TObj, class TArgs>
	static PriorityDelegate<TObj, TArgs, false> GetPriorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int prio)
	{
		return PriorityDelegate<TObj, TArgs, false>(pObj, NotifyMethod, prio);
	}


	template <class TObj, class TArgs>
	static PriorityExpireDelegate<TArgs> GetPriorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int prio, Timestamp::TimeDiff expireMilliSec)
	{
		return PriorityExpireDelegate<TArgs>(PriorityDelegate<TObj, TArgs, true>(pObj, NotifyMethod, prio), expireMilliSec);
	}


	template <class TObj, class TArgs>
	static PriorityExpireDelegate<TArgs> GetPriorityDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int prio, Timestamp::TimeDiff expireMilliSec)
	{
		return PriorityExpireDelegate<TArgs>(PriorityDelegate<TObj, TArgs, false>(pObj, NotifyMethod, prio), expireMilliSec);
	}


	template <class TArgs>
	static PriorityExpireDelegate<TArgs> GetPriorityDelegate(void (*NotifyMethod)(const void*, TArgs&), int prio, Timestamp::TimeDiff expireMilliSec)
	{
		return PriorityExpireDelegate<TArgs>(FunctionPriorityDelegate<TArgs, true, true>(NotifyMethod, prio), expireMilliSec);
	}


	template <class TArgs>
	static PriorityExpireDelegate<TArgs> GetPriorityDelegate(void (*NotifyMethod)(void*, TArgs&), int prio, Timestamp::TimeDiff expireMilliSec)
	{
		return PriorityExpireDelegate<TArgs>(FunctionPriorityDelegate<TArgs, true, false>(NotifyMethod, prio), expireMilliSec);
	}


	template <class TArgs>
	static PriorityExpireDelegate<TArgs> GetPriorityDelegate(void (*NotifyMethod)(TArgs&), int prio, Timestamp::TimeDiff expireMilliSec)
	{
		return PriorityExpireDelegate<TArgs>(FunctionPriorityDelegate<TArgs, false>(NotifyMethod, prio), expireMilliSec);
	}


	template <class TArgs>
	static FunctionPriorityDelegate<TArgs, true, true> GetPriorityDelegate(void (*NotifyMethod)(const void*, TArgs&), int prio)
	{
		return FunctionPriorityDelegate<TArgs, true, true>(NotifyMethod, prio);
	}


	template <class TArgs>
	static FunctionPriorityDelegate<TArgs, true, false> GetPriorityDelegate(void (*NotifyMethod)(void*, TArgs&), int prio)
	{
		return FunctionPriorityDelegate<TArgs, true, false>(NotifyMethod, prio);
	}


	template <class TArgs>
	static FunctionPriorityDelegate<TArgs, false> GetPriorityDelegate(void (*NotifyMethod)(TArgs&), int prio)
	{
		return FunctionPriorityDelegate<TArgs, false>(NotifyMethod, prio);
	}
}

#endif