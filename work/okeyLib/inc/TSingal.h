/********************************************************************
	created:	2015/07/17
	created:	15:24
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TEMPLATE_SINGAL_H__
#define __TEMPLATE_SINGAL_H__

#include <list>
#include "TSlot.h"

namespace okey
{
	template <typename _SlotT, typename _Mutex>
	class SignalBase 
	{
	public:
		typedef _SlotT                SlotType;
		typedef std::list<SlotType*>  SlotList;
		SignalBase(){}

		~SignalBase()
		{
			typename SlotList::iterator i = _slots.begin();
			while(i != _slots.end())
			{
				delete *i;
				i = _slots.erase(i);
			}
		}

		void Bind(SlotType& slot)
		{
			typename _Mutex::ScopedLock lock(_mutex);
			_slots.push_back(slot.clone());
		}

		template <class UnbindSlotType>
		void UnBind(UnbindSlotType& slot)
		{
			typename _Mutex::ScopedLock lock(_mutex);
			typename SlotList::iterator itr = _slots.begin();
			while(itr != _slots.end())
			{
				UnbindSlotType* s = static_cast<UnbindSlotType*>(*itr);
				if(s && *s == slot)
				{
					delete *itr;
					_slots.erase(itr);
					return;
				}
				++itr;
			}
		}
	protected:
		SlotList slotList()
		{
			ReadLock rl(_mutex);
			return _slots;
		}
	private:
		SignalBase(const SignalBase&);
		SignalBase& operator=(const SignalBase&);
		_Mutex	_mutex;
		SlotList	_slots;
	};

	template <class _RetT, class _Mutex = NullLock>
	class Signal0: public SignalBase<Slot0<_RetT>, _Mutex> 
	{
	public:
		typedef _RetT RetType;
		typedef SignalBase<Slot0<_RetT>,_Mutex> SignalBase;
		RetType Emit() //通知。。
		{
			typedef typename SignalBase::SlotList SlotList;
			RetType ret = RetType();
			SlotList slots = slotList();
			for(typename SlotList::const_iterator i = slots.begin(); i != slots.end(); ++i) 
			{
				ret = (*i)->Proxy();
				if(ret)
					break;
			}
			return ret;
		}
	};

	template<class _Mutex = NullLock>
	class Signal0<void, _Mutex>: public SignalBase<Slot0<void>, _Mutex>
	{
		typedef SignalBase<Slot0<void>,_Mutex> SignalBase;
		void Emit() //通知。。
		{
			typedef typename SignalBase::SlotList SlotList;
			RetType ret = RetType();
			SlotList slots = slotList();
			for(typename SlotList::const_iterator i = slots.begin(); i != slots.end(); ++i) 
			{
				(*i)->Proxy();
			}
		}
	};

	template <class _RetT, class P1, class _Mutex = NullLock>
	class Signal1: public SignalBase<Slot1<_RetT,P1>, _Mutex> 
	{
	public:
		typedef _RetT RetType;
		typedef SignalBase<Slot1<_RetT,P1>,_Mutex> SignalBase;
		RetType Emit(P1 p1) //通知。。
		{
			typedef typename SignalBase::SlotList SlotList;
			RetType ret = RetType();
			SlotList slots = slotList();
			for(typename SlotList::const_iterator i = slots.begin(); i != slots.end(); ++i) 
			{
				ret = (*i)->Proxy(p1);
				if(ret)
					break;
			}
			return ret;
		}
	};

	template<class P1, class _Mutex = NullLock>
	class Signal1<void,P1, _Mutex>: public SignalBase<Slot1<void,P1>, _Mutex>
	{
		typedef SignalBase<Slot1<void,P1>,_Mutex> SignalBase;
		void Emit(P1 p1) //通知。。
		{
			typedef typename SignalBase::SlotList SlotList;
			RetType ret = RetType();
			SlotList slots = slotList();
			for(typename SlotList::const_iterator i = slots.begin(); i != slots.end(); ++i) 
			{
				(*i)->Proxy(p1);
			}
		}
	};

	template <class _SignalT, class _SlotT>
	void f_bind(_SignalT& sig, _SlotT slot){ sig.Bind(slot); }


	template <class _SignalT, class _SlotT>
	void f_unbind(_SignalT& sig, _SlotT slot){ sig.UnBind(slot); }

}


#endif