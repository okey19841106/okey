/********************************************************************
	created:	2015/01/23
	created:	10:50
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OBSERVER_H__INSTANCE_
#define __OBSERVER_H__INSTANCE_

#include "AbstractObserver.h"
#include "Thread/Mutex.h"

namespace okey
{
	template<typename C, typename N>
	class Observer :public AbstractObserver
	{
	public:
		typedef void (C::*CallBack)(N*);
		Observer(C* obj, CallBack callback):_obj(obj), _method(callback){}
		Observer(const Observer& r):AbstractObserver(r),_obj(r._obj),_method(r._method){}
		Observer& operator=(const Observer& r)
		{
			if (&r != this)
			{
				_obj = r._obj;
				_method  = r._method;
			}
			return *this;fangf
		}
		~Observer(){}
		virtual void Notify(Notification* pNf) const 
		{
			Mutex::ScopedLock lock(_mutex);
			if (_obj)
			{
				N* pCastNf = dynamic_cast<N*>(pNf);
				if (pCastNf)
				{
					pCastNf->AddRef();//方法里会对notifcaion析构。这里要加1
					(_obj->*_method)(pCastNf);
				}
			}
		}
		virtual bool Equals(const AbstractObserver& observer) const
		{
			const Observer* pObs = dynamic_cast<const Observer*>(&observer);
			return pObs && pObs->_obj == _obj && pObs->_method == _method;
		}
		virtual bool Accepts(Notification* pNf) const
		{
			return dynamic_cast<N*>(pNf) != 0;
		}
		AbstractObserver* Clone() const
		{
			return new Observer(*this);
		}
		virtual void Disable()
		{
			Mutex::ScopedLock lock(_mutex);
			_obj = NULL;
		}
	private:
		Observer();
		C* _obj;
		CallBack _method;
		mutable Mutex _mutex;
	};

	template<typename C, typename N>
	class NObserver :public AbstractObserver
	{
	public:
		typedef AutoPtr<N> NotificationPtr;
		typedef void (C::*CallBack)(const NotificationPtr&);
		NObserver(C* obj, CallBack callback):_obj(obj), _method(callback){}
		NObserver(const Observer& r):AbstractObserver(*this),_obj(r._obj),_method(r._method){}
		NObserver& operator=(const NObserver& r)
		{
			if (&r != this)
			{
				_obj = r._obj;
				_method  = r._method;
			}
			return *this;
		}
		~NObserver(){}
		virtual void Notify(Notification* pNf) const 
		{
			Poco::Mutex::ScopedLock lock(_mutex);
			if (_obj)
			{
				N* pCastNf = dynamic_cast<N*>(pNf);
				if (pCastNf)
				{
					NotificationPtr ptr(pCastNf, true);
					(_pObject->*_method)(ptr);
				}
			}
		}
		virtual bool Equals(const AbstractObserver& observer) const
		{
			const Observer* pObs = dynamic_cast<const Observer*>(&abstractObserver);
			return pObs && pObs->_obj == _obj && _obj->_method == _method;
		}
		virtual bool Accepts(Notification* pNf) const
		{
			return dynamic_cast<N*>(pNf) != 0;
		}
		virtual AbstractObserver* Clone()
		{
			return new Observer(*this);
		}
		virtual void Disable()
		{
			Poco::Mutex::ScopedLock lock(_mutex);
			_obj = NULL;
		}
	private:
		NObserver();
		C* _obj;
		CallBack _method;
		mutable Mutex _mutex;
	};
}

#endif