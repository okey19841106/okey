/********************************************************************
	created:	2015/09/07
	created:	15:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_ACCESS_EXPIRE_LRU_CACHE_H__
#define __CACHE_ACCESS_EXPIRE_LRU_CACHE_H__

#include "AbstractCache.h"
#include "StrategyCollection.h"
#include "AccessExpireStrategy.h"
#include "LRUStrategy.h"

namespace okey
{
	template<typename TKey, typename TValue, typename TMutex = FastMutex, typename TEventMutex = FastMutex>
	class AccessExpireLRUCache : public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >
	{
	public:
		AccessExpireLRUCache(std::size_t cacheSize = 1024, int64 expire = 60000):
		  AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >(StrategyCollection<TKey, TValue>())
		{
			this->_strategy.PushBack(new LRUStrategy<TKey, TValue>(cacheSize));
			this->_strategy.PushBack(new AccessExpireStrategy<TKey, TValue>(expire));
		}
		~AccessExpireLRUCache(){}
	private:
		AccessExpireLRUCache(const AccessExpireLRUCache&);
		AccessExpireLRUCache& operator=(const AccessExpireLRUCache&);
	};
}

#endif