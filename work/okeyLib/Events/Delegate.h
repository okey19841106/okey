/********************************************************************
	created:	2015/01/23
	created:	14:56
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DELEGATE_H__
#define __DELEGATE_H__

#include "AbstractDelegate.h"

namespace okey
{
	template <typename TObj, typename TArgs, bool withSender = true> 
	class Delegate: public AbstractDelegate<TArgs>
	{
	public:
		typedef void (TObj::*NotifyMethod)(const void*, TArgs&);
		Delegate(TObj* obj, NotifyMethod method):_obj(obj),_method(method){}
		Delegate(const Delegate& d):AbstractDelegate<TArgs>(d),_obj(d._obj),_method(d._method){}
		~Delegate(){}
		Delegate& operator=(const Delegate& d)
		{
			if (&d != this)
			{
				_obj = d._obj;
				_method = d._method;
			}
			return *this;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_obj)
			{
				(_obj->*_method)(sender, arguments);
				return true;
			}
			else return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			const Delegate* pOtherDelegate = reinterpret_cast<const Delegate*>(other.Unwrap());
			return pOtherDelegate && _obj == pOtherDelegate->_obj && _method == pOtherDelegate->_method;
		}
		virtual AbstractDelegate* Clone() const
		{
			return new Delegate(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_obj = NULL;
		}
	private:
		Delegate();
		TObj* _obj;
		NotifyMethod _method;
		Mutex        _mutex;
	};


	template <typename TObj, typename TArgs>
	class Delegate<TObj, TArgs, false>: public AbstractDelegate<TArgs>
	{
		typedef void (TObj::*NotifyMethod)(TArgs&);
		Delegate(TObj* obj, NotifyMethod method):_obj(obj),_method(method){}
		Delegate(const Delegate& d):AbstractDelegate<TArgs>(d),_obj(d._obj),_method(d._method){}
		~Delegate(){}
		Delegate& operator=(const Delegate& d)
		{
			if (&d != this)
			{
				_obj = d._obj;
				_method = d._method;
			}
			return *this;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_obj)
			{
				(_obj->*_method)(arguments);
				return true;
			}
			else 
				return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			const Delegate* pOtherDelegate = reinterpret_cast<const Delegate*>(other.Unwrap());
			return pOtherDelegate && _obj == pOtherDelegate->_obj && _method == pOtherDelegate->_method;
		}
		virtual AbstractDelegate* Clone() const
		{
			return new Delegate(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_obj = NULL;
		}
	private:
		Delegate();
		TObj* _obj;
		NotifyMethod _method;
		Mutex        _mutex;
	};

	template <class TObj, class TArgs>
	static Delegate<TObj, TArgs, true> GenDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&))
	{
		return Delegate<TObj, TArgs, true>(pObj, NotifyMethod);
	}


	template <class TObj, class TArgs>
	static Delegate<TObj, TArgs, false> GenDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&))
	{
		return Delegate<TObj, TArgs, false>(pObj, NotifyMethod);
	}


	template <class TObj, class TArgs>
	static ExpireDelegate<TArgs> GenDelegate(TObj* pObj, void (TObj::*NotifyMethod)(const void*, TArgs&), int64 expireMillisecs)
	{
		return ExpireDelegate<TArgs>(Delegate<TObj, TArgs, true>(pObj, NotifyMethod), expireMillisecs);
	}


	template <class TObj, class TArgs>
	static ExpireDelegate<TArgs> GenDelegate(TObj* pObj, void (TObj::*NotifyMethod)(TArgs&), int64 expireMillisecs)
	{
		return ExpireDelegate<TArgs>(Delegate<TObj, TArgs, false>(pObj, NotifyMethod), expireMillisecs);
	}


	template <class TArgs>
	static ExpireDelegate<TArgs> GenDelegate(void (*NotifyMethod)(const void*, TArgs&), int64 expireMillisecs)
	{
		return ExpireDelegate<TArgs>(FunctionDelegate<TArgs, true, true>(NotifyMethod), expireMillisecs);
	}


	template <class TArgs>
	static ExpireDelegate<TArgs> GenDelegate(void (*NotifyMethod)(void*, TArgs&), int64 expireMillisecs)
	{
		return ExpireDelegate<TArgs>(FunctionDelegate<TArgs, true, false>(NotifyMethod), expireMillisecs);
	}


	template <class TArgs>
	static ExpireDelegate<TArgs> GenDelegate(void (*NotifyMethod)(TArgs&), int64 expireMillisecs)
	{
		return ExpireDelegate<TArgs>(FunctionDelegate<TArgs, false>(NotifyMethod), expireMillisecs);
	}


	template <class TArgs>
	static FunctionDelegate<TArgs, true, true> GenDelegate(void (*NotifyMethod)(const void*, TArgs&))
	{
		return FunctionDelegate<TArgs, true, true>(NotifyMethod);
	}


	template <class TArgs>
	static FunctionDelegate<TArgs, true, false> GenDelegate(void (*NotifyMethod)(void*, TArgs&))
	{
		return FunctionDelegate<TArgs, true, false>(NotifyMethod);
	}


	template <class TArgs>
	static FunctionDelegate<TArgs, false> GenDelegate(void (*NotifyMethod)(TArgs&))
	{
		return FunctionDelegate<TArgs, false>(NotifyMethod);
	}
}

#endif