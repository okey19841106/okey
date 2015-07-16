/********************************************************************
	created:	2015/07/16
	created:	16:43
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __DYNAMIC_FACTORY_H__
#define __DYNAMIC_FACTORY_H__

#include <map>
#include "Exception.h"
#include "Thread/Mutex.h"

namespace okey
{
	template <class Base>
	class DynamicFactory
	{
	public:
		typedef AbstractInstantiator<Base> AbstractFactory;
		DynamicFactory(){}
		~DynamicFactory()
		{
			for (typename FactoryMap::iterator it = _map.begin(); it != _map.end(); ++it)
			{
				delete it->second;
			}
		}

		Base* CreateInstance(const std::string& className) const
		{
			FastMutex::ScopedLock lock(_mutex);
			typename FactoryMap::const_iterator it = _map.find(className);
			if (it != _map.end())
				return it->second->CreateInstance();
			else
				throw NotFoundException(className);
		}

		template <class C> 
		void RegisterClass(const std::string& className)
		{
			RegisterClass(className, new Instantiator<C, Base>);
		}

		void RegisterClass(const std::string& className, AbstractFactory* pAbstractFactory)
		{
			//check pAbstract.
			FastMutex::ScopedLock lock(_mutex);
			std::auto_ptr<AbstractFactory> ptr(pAbstractFactory);
			typename FactoryMap::iterator it = _map.find(className);
			if (it == _map.end())
				_map[className] = ptr.release();
			else
				throw ExistsException(className);
		}

		void UnRegisterClass(const std::string& className)
		{
			FastMutex::ScopedLock lock(_mutex);
			typename FactoryMap::iterator it = _map.find(className);
			if (it != _map.end())
			{
				delete it->second;
				_map.erase(it);
			}
			else throw NotFoundException(className);
		}

		bool IsClass(const std::string& className) const
		{
			FastMutex::ScopedLock lock(_mutex);
			return _map.find(className) != _map.end();
		}

		void Destroy(Base* ptr)
		{
			delete ptr;
		}

	private:
		DynamicFactory(const DynamicFactory&);
		DynamicFactory& operator = (const DynamicFactory&);
		typedef std::map<std::string, AbstractFactory*> FactoryMap;
		FactoryMap _map;
		mutable FastMutex _mutex;
	};
}


#endif