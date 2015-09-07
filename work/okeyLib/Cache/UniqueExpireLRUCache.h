/********************************************************************
	created:	2015/09/07
	created:	15:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_UNIQUE_EXPIRE_LRU_CACHE_H__
#define __CACHE_UNIQUE_EXPIRE_LRU_CACHE_H__

#include "AbstractCache.h"
#include "StrategyCollection.h"
#include "UniqueExpireStrategy.h"
#include "LRUStrategy.h"

namespace okey
{
	template<typename TKey, typename TValue, typename TMutex = FastMutex, typename TEventMutex = FastMutex>
	class UniqueExpireLRUCache : public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >
	{
	public:
		UniqueExpireLRUCache(std::size_t cacheSize = 1024):
		  AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >(StrategyCollection<TKey, TValue>())
		{
			this->_strategy.PushBack(new LRUStrategy<TKey, TValue>(cacheSize));
			this->_strategy.PushBack(new UniqueExpireStrategy<TKey, TValue>());
		}
	private:
		UniqueExpireLRUCache(const UniqueExpireLRUCache&);
		UniqueExpireLRUCache& operator=(const UniqueExpireLRUCache&);
	};
}

#endif