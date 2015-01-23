/********************************************************************
	created:	2015/01/23
	created:	16:22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FUNCTION_DELEGATE_H__
#define __FUNCTION_DELEGATE_H__

#include "AbstractDelegate.h"

namespace okey
{
	template <typename TArgs, bool hasSender = true, bool senderIsConst = true> 
	class FunctionDelegate: public AbstractDelegate<TArgs>
	{
	public:
		typedef void (*NotifyMethod)(const void*, TArgs&);
		FunctionDelegate(NotifyMethod m):_method(m){}
		FunctionDelegate(const FunctionDelegate& f):AbstractDelegate<TArgs>(f),_method(f._method){}
		~FunctionDelegate(){}
		FunctionDelegate& operator=(const FunctionDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
			}
			return;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_method)
			{
				(*_method)(sender, arguments);
				return true;
			}
			else return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			const Delegate* pOtherDelegate = reinterpret_cast<const Delegate*>(other.Unwrap());
			return pOtherDelegate &&  _method == pOtherDelegate->_method;
		}
		virtual AbstractDelegate* Clone() const
		{
			return new FunctionDelegate(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_method = NULL;
		}
	private:
		FunctionDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};

	template <class TArgs> 
	class FunctionDelegate<TArgs, true, false>: public AbstractDelegate<TArgs>
	{
		typedef void (*NotifyMethod)(void*, TArgs&);
		FunctionDelegate(NotifyMethod m):_method(m){}
		FunctionDelegate(const FunctionDelegate& f):AbstractDelegate<TArgs>(f),_method(f._method){}
		~FunctionDelegate(){}
		FunctionDelegate& operator=(const FunctionDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
			}
			return;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_method)
			{
				(*_method)(const_cast<void*>sender, arguments);
				return true;
			}
			else return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			const Delegate* pOtherDelegate = reinterpret_cast<const Delegate*>(other.Unwrap());
			return pOtherDelegate &&  _method == pOtherDelegate->_method;
		}
		virtual AbstractDelegate* Clone() const
		{
			return new FunctionDelegate(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_method = NULL;
		}
	private:
		FunctionDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};

	template <class TArgs, bool senderIsConst> 
	class FunctionDelegate<TArgs, false, senderIsConst>: public AbstractDelegate<TArgs>
	{
		typedef void (*NotifyMethod)(TArgs&);
		FunctionDelegate(NotifyMethod m):_method(m){}
		FunctionDelegate(const FunctionDelegate& f):AbstractDelegate<TArgs>(f),_method(f._method){}
		~FunctionDelegate(){}
		FunctionDelegate& operator=(const FunctionDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
			}
			return;
		}
		virtual bool Notify(const void* sender, TArgs& arguments)
		{
			Mutex::ScopedLock lock(_mutex);
			if (_method)
			{
				(*_method)(arguments);
				return true;
			}
			else return false;
		}
		virtual bool Equals(const AbstractDelegate& other) const
		{
			const Delegate* pOtherDelegate = reinterpret_cast<const Delegate*>(other.Unwrap());
			return pOtherDelegate &&  _method == pOtherDelegate->_method;
		}
		virtual AbstractDelegate* Clone() const
		{
			return new FunctionDelegate(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_method = NULL;
		}
	private:
		FunctionDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};
}


#endif