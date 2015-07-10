/********************************************************************
	created:	2015/07/10
	created:	10:40
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_OBJECT_POOL_H__
#define __BASE_OBJECT_POOL_H__

#include "AutoPtr.h"
#include "SharedPtr.h"
#include <vector>
#include "Thread/Mutex.h"

namespace okey
{
	template<typename C, typename P = C*>
	class PoolableObjectFactory
	{
	public:
		P CreateObject()
		{
			return new C;
		}

		bool IsValidObject(P pObject)
		{
			return true;
		}

		void ActivateObject(P pObject)//call before object is handed out by pool
		{

		}

		void DeactivateObject(P pObject)//call after object been given back to pool
		{

		}

		void DestroyObject(P pObject)
		{
			delete pObject;
		}
	};

	template<typename C>
	class PoolableObjectFactory<C, AutoPtr<C> >
	{
	public:
		AutoPtr<C> CreateObject()
		{
			return new C;
		}

		bool IsValidObject(P pObject)
		{
			return true;
		}

		void ActivateObject(P pObject)//call before object is handed out by pool
		{
		}

		void DeactivateObject(P pObject)//call after object been given back to pool
		{
		}

		void DestroyObject(P pObject)
		{
		}
	};

	template<typename C>
	class PoolableObjectFactory<C, SharedPtr<C> >
	{
	public:
		SharedPtr<C> CreateObject()
		{
			return new C;
		}

		bool IsValidObject(P pObject)
		{
			return true;
		}

		void ActivateObject(P pObject)//call before object is handed out by pool
		{
		}

		void DeactivateObject(P pObject)//call after object been given back to pool
		{
		}

		void DestroyObject(P pObject)
		{
		}
	};

	template<typename C, typename P = C*, typename F = PoolableObjectFactory<C, P> >
	class ObjectPool
	{
	public:
		ObjectPool(std::size_t capacity, std::size_t peakCapacity):
		  _capacity(capacity),_peakCapacity(peakCapacity),_size(0)
		  {
			  //assert capacity <= peakCapacity;
		  }
		ObjectPool(const F& factory, std::capacity, std::size_t peakCapacity):
		  _factory(factory),_capacity(capacity),_peakCapacity(peakCapacity),_size(0)
		  {

		  }
		~ObjectPool()
		{
			for(typename std::vector<P>::iterator itr = _pool.begin(); itr != _pool.end(); ++itr)
			{
				_factory.DestroyObject(*itr);
			}
		}
		P BorrowObject()
		{
			FastMutex::ScopedLock lock(_mutex);
			if (!_pool.empty())
			{
				P pObject = _pool.back();
				_pool.pop_back();
				return ActivateObject(pObject);
			}
			else if (_size < _peakCapacity)
			{
				P pObject = _factory.CreateObject();
				ActivateObject(pObject);
				++_size;
				return pObject;
			}
			else
				return 0;
		}
		void ReturnObject(P pObject)
		{
			FastMutex::ScopedLock lock(_mutex);
			if (_factory.IsValidObject(pObject))
			{
				_factory.DeactivateObject(pObject);
				if (_pool.size() < _capacity)
				{
					_pool.push_back(pObject);
				}
				else
				{
					_factory.DestroyObject(pObject);
					--_size;
				}
			}
			else
			{
				_factory.DestroyObject(pObject);
			}
		}
		std::size_t GetCapacity()const{return _capacity;}
		std::size_t GetPeakCapacity()const{return _peakCapacity;}
		std::size_t GetSize()const
		{
			FastMutex::ScopedLock lock(_mutex);
			return _size;
		}
		size_t GetAvailable()const
		{
			FastMutex::ScopedLock lock(_mutex);
			return _pool.size() + _peakCapacity - _size;
		}
	protected:
		P ActivateObject(P pObject)
		{
			try
			{
				_factory.ActivateObject(pObject);
			}
			catch (...)
			{
				_factory.DestroyObject(pObject);
				throw;
			}
			return pObject;
		}
	private:
		ObjectPool();
		ObjectPool(const ObjectPool&);
		ObjectPool& operator = (const ObjectPool&);
	private:
		F _factory;
		std::size_t _capacity;
		std::size_t _peakCapacity;
		std::size_t _size;
		std::vector<P> _pool;
		mutable FastMutex _mutex;
	};
}

#endif
