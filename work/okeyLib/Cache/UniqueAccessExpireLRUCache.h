/********************************************************************
	created:	2015/09/07
	created:	15:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_UNIQUE_ACCESS_EXPIRE_LRU_CACHE_H__
#define __CACHE_UNIQUE_ACCESS_EXPIRE_LRU_CACHE_H__

#include "AbstractCache.h"
#include "StrategyCollection.h"
#include "UniqueAccessExpireStrategy.h"
#include "LRUStrategy.h"

namespace okey
{
	template<typename TKey, typename TValue, typename TMutex = FastMutex, typename TEventMutex = FastMutex>
	class UniqueAccessExpireLRUCache : public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >
	{
	public:
		UniqueAccessExpireLRUCache(std::size_t cacheSize = 1024):
		  AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >(StrategyCollection<TKey, TValue>())
		{
			this->_strategy.PushBack(new LRUStrategy<TKey, TValue>(cacheSize));
			this->_strategy.PushBack(new UniqueAccessExpireStrategy<TKey, TValue>());
		}
		~UniqueAccessExpireLRUCache(){}
	private:
		UniqueAccessExpireLRUCache(const UniqueAccessExpireLRUCache&);
		UniqueAccessExpireLRUCache& operator=(const UniqueAccessExpireLRUCache&);
	};
}

#endif