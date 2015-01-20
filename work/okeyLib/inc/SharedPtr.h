/********************************************************************
	created:	2015/01/16
	created:	10:53
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SHARED_PTR_H__
#define __SHARED_PTR_H__

#include "Thread/AtomicCounter.h"

namespace okey
{

	class ReferenceCounter
		/// Simple ReferenceCounter object, does not delete itself when count reaches 0.
	{
	public:
		ReferenceCounter(): _cnt(1)
		{
		}

		void AddRef()
		{
			++_cnt;
		}

		int32 DelRef()
		{
			return --_cnt;
		}

		int32 GetRef() const
		{
			return _cnt.GetValue();
		}

	private:
		AtomicCounter _cnt;
	};

	template <class C>
	class ReleasePolicy
	{
	public:
		static void release(C* pObj)
		{
			delete pObj;
		}
	};

	template <class C>
	class ReleaseArrayPolicy /// The release policy for SharedPtr holding arrays.
	{
	public:
		static void release(C* pObj)
		{
			delete [] pObj;
		}
	};

	template<typename C, typename RC = ReferenceCounter, typename RP = ReleasePolicy<C> > 
	class SharedPtr
	{
		template <typename OtherC, typename OtherRC, typename OtherRP> friend class SharedPtr;
	public:
		SharedPtr():_pCounter(new RC), _ptr(NULL){}
		SharedPtr(C* ptr):_pCounter(new RC), _ptr(ptr){}
		template<typename OtherC, typename OtherRP>
		SharedPtr(const SharedPtr<OtherC, RC, OtherRP>& oPtr):_pCounter(oPtr._pCounter), _ptr(const<OtherC>(oPtr._ptr))
		{
			_pCounter->AddRef();
		}
		SharedPtr(const SharedPtr& ptr): _pCounter(ptr._pCounter), _ptr(ptr._ptr)
		{
			_pCounter->AddRef();
		}
		~SharedPtr()
		{
			Release();
		}
		SharedPtr& Assign(C* ptr)
		{
			if (Get() != ptr)
			{
				RC* pTmp = new RC;
				Release();
				_pCounter = pTmp;
				_ptr = ptr;
			}
			return *this;
		}
		SharedPtr& Assign(const SharedPtr& ptr)
		{
			if (&ptr != this)
			{
				SharedPtr tmp(ptr);
				Swap(tmp);
			}
			return *this;
		}
		template <typename Other, typename OtherRP>
		SharedPtr& Assign(const SharedPtr<Other, RC, OtherRP>& ptr)
		{
			if (ptr.Get() != _ptr)
			{
				SharedPtr tmp(ptr);
				Swap(tmp);
			}
			return *this;
		}
		SharedPtr& operator = (C* ptr)
		{
			return Assign(ptr);
		}

		SharedPtr& operator = (const SharedPtr& ptr)
		{
			return Assign(ptr);
		}

		template <typename Other, typename OtherRP>
		SharedPtr& operator = (const SharedPtr<Other, RC, OtherRP>& ptr)
		{
			return Assign<Other, OtherRP>(ptr);
		}

		void Swap(SharedPtr& ptr)
		{
			std::swap(_ptr, ptr._ptr);
			std::swap(_pCounter, ptr._pCounter);
		}
		template <typename Other> 
		SharedPtr<Other, RC, RP> cast() const
		{
			Other* pOther = dynamic_cast<Other*>(_ptr);
			if (pOther)
				return SharedPtr<Other, RC, RP>(_pCounter, pOther);
			return SharedPtr<Other, RC, RP>();
		}

		template <typename Other> 
		SharedPtr<Other, RC, RP> unsafeCast() const
		{
			Other* pOther = static_cast<Other*>(_ptr);
			return SharedPtr<Other, RC, RP>(_pCounter, pOther);
		}

		C* operator -> ()
		{
			return deref();
		}

		const C* operator -> () const
		{
			return deref();
		}
		C& operator * ()
		{
			return *deref();
		}
		const C& operator * () const
		{
			return *deref();
		}
		C* Get()
		{
			return _ptr;
		}
		const C* Get() const
		{
			return _ptr;
		}
		operator C* ()
		{
			return _ptr;
		}

		operator const C* () const
		{
			return _ptr;
		}

		bool operator ! () const
		{
			return _ptr == 0;
		}

		bool isNull() const
		{
			return _ptr == 0;
		}

		bool operator == (const SharedPtr& ptr) const
		{
			return Get() == ptr.Get();
		}

		bool operator == (const C* ptr) const
		{
			return Get() == ptr;
		}

		bool operator == (C* ptr) const
		{
			return Get() == ptr;
		}

		bool operator != (const SharedPtr& ptr) const
		{
			return Get() != ptr.Get();
		}

		bool operator != (const C* ptr) const
		{
			return Get() != ptr;
		}

		bool operator != (C* ptr) const
		{
			return Get() != ptr;
		}

		bool operator < (const SharedPtr& ptr) const
		{
			return Get() < ptr.Get();
		}

		bool operator < (const C* ptr) const
		{
			return Get() < ptr;
		}

		bool operator < (C* ptr) const
		{
			return Get() < ptr;
		}

		bool operator <= (const SharedPtr& ptr) const
		{
			return Get() <= ptr.Get();
		}

		bool operator <= (const C* ptr) const
		{
			return Get() <= ptr;
		}

		bool operator <= (C* ptr) const
		{
			return Get() <= ptr;
		}

		bool operator > (const SharedPtr& ptr) const
		{
			return Get() > ptr.Get();
		}

		bool operator > (const C* ptr) const
		{
			return Get() > ptr;
		}

		bool operator > (C* ptr) const
		{
			return Get() > ptr;
		}

		bool operator >= (const SharedPtr& ptr) const
		{
			return Get() >= ptr.Get();
		}

		bool operator >= (const C* ptr) const
		{
			return Get() >= ptr;
		}

		bool operator >= (C* ptr) const
		{
			return Get() >= ptr;
		}

// 		int DelRef() const
// 		{
// 			return _pCounter->DelRef();
// 		}
	private:
		C* deref() const
		{
			if (!_ptr)
				throw NullPointerException();
			return _ptr;
		}

		void Release()
		{
			//poco_assert_dbg (_pCounter);
			int i = _pCounter->DelRef();
			if (i == 0)
			{
				RP::release(_ptr);
				_ptr = 0;
				delete _pCounter;
				_pCounter = 0;
			}
		}
	private:
		RC* _pCounter;
		C*  _ptr;

		
	};

	template <typename C, typename RC, typename RP>
	inline void Swap(SharedPtr<C, RC, RP>& p1, SharedPtr<C, RC, RP>& p2)
	{
		p1.Swap(p2);
	}
}


#endif