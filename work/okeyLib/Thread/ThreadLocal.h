/********************************************************************
	created:	2015/01/16
	created:	16:59
	author:		okey
	
	purpose:	TLS..
*********************************************************************/
#ifndef __OKEY_THREAD_LOCAL_H__
#define __OKEY_THREAD_LOCAL_H__

#include <map>

namespace okey
{
	class TLSAbstractSlot
	{
	public:
		TLSAbstractSlot(){}
		virtual ~TLSAbstractSlot(){}
	};

	template<typename C>
	class TLSSlot : public TLSAbstractSlot
	{
	public:
		TLSSlot():_value(){}
		~TLSSlot(){}
		C& GetValue()
		{
			return _value;
		}
	private:
		TLSSlot(const TLSSlot&);
		TLSSlot& operator = (const TLSSlot&);
		C _value;
	};

	class  ThreadLocalStorage
	{
	public:
		ThreadLocalStorage();	/// Creates the TLS.
		~ThreadLocalStorage();	/// Deletes the TLS.
		TLSAbstractSlot*& Get(const void* key);	/// Returns the slot for the given key.
		static ThreadLocalStorage& Current();	/// Returns the TLS object for the current thread
		static void Clear();	/// Clears the current thread's TLS object.Does nothing in the main thread.
	private:
		typedef std::map<const void*, TLSAbstractSlot*> TLSMap;
		TLSMap _map;
		friend class Thread;
	};

	template <class C>
	class ThreadLocal
	{
	public:
		typedef TLSSlot<C> Slot;
	public:
		ThreadLocal(){}
		~ThreadLocal(){}
		C* operator->()
		{
			return &Get();
		}

		C& operator*()
		{
			return Get();
		}

		C& Get()
		{
			TLSAbstractSlot*& p = ThreadLocalStorage::Current().Get(this);
			if (!p) 
				p = new Slot;//这用的是引用，直接就会在map里了。不会内存泄露。
			return static_cast<Slot*>(p)->GetValue();
		}
	private:
		ThreadLocal(const ThreadLocal&);
		ThreadLocal& operator = (const ThreadLocal&);
	};
}

#endif