/********************************************************************
	created:	2015/01/23
	created:	16:45
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __FUNCTION_PRIORITY_DELEGATE_H__
#define __FUNCTION_PRIORITY_DELEGATE_H__

namespace okey
{
	template <typename TArgs, bool hasSender = true, bool senderIsConst = true> 
	class FunctionPriorityDelegate: public AbstractPriorityDelegate<TArgs>
	{
	public:
		typedef void (*NotifyMethod)(const void*, TArgs&);
		FunctionPriorityDelegate(NotifyMethod m, int32 priority):AbstractPriorityDelegate<TArgs>(priority),_method(m){}
		FunctionPriorityDelegate(const FunctionPriorityDelegate& f, int32 priority):AbstractPriorityDelegate<TArgs>(f, priority),_method(f._method){}
		~FunctionPriorityDelegate(){}
		FunctionPriorityDelegate& operator=(const FunctionPriorityDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
				_priority = f._priority;
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
		FunctionPriorityDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};

	template <class TArgs> 
	class FunctionPriorityDelegate<TArgs, true, false>: public AbstractPriorityDelegate<TArgs>
	{
		typedef void (*NotifyMethod)(void*, TArgs&);
		FunctionPriorityDelegate(NotifyMethod m):AbstractPriorityDelegate<TArgs>(priority),_method(m){}
		FunctionPriorityDelegate(const FunctionPriorityDelegate& f, int32 priority):AbstractPriorityDelegate<TArgs>(f, priority),_method(f._method){}
		~FunctionPriorityDelegate(){}
		FunctionPriorityDelegate& operator=(const FunctionPriorityDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
				_priority = f._priority;
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
		FunctionPriorityDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};

	template <class TArgs, bool senderIsConst> 
	class FunctionPriorityDelegate<TArgs, false, senderIsConst>: public AbstractPriorityDelegate<TArgs>
	{
		typedef void (*NotifyMethod)(TArgs&);
		FunctionPriorityDelegate(NotifyMethod m):AbstractPriorityDelegate<TArgs>(priority),_method(m){}
		FunctionPriorityDelegate(const FunctionPriorityDelegate& f):AbstractPriorityDelegate<TArgs>(f, priority),_method(f._method){}
		~FunctionPriorityDelegate(){}
		FunctionPriorityDelegate& operator=(const FunctionPriorityDelegate& f)
		{
			if (&f != this)
			{
				_method = f._method;
				_priority = f._priority;
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
		FunctionPriorityDelegate();
	protected:
		NotifyMethod _method;
		Mutex _mutex;
	};
}

#endif