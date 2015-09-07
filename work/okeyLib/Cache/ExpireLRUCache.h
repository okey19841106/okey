/********************************************************************
	created:	2015/09/07
	created:	15:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_EXPIRE_LRU_CACHE_H__
#define __CACHE_EXPIRE_LRU_CACHE_H__

#include "AbstractCache.h"
#include "StrategyCollection.h"
#include "ExpireStrategy.h"
#include "LRUStrategy.h"

namespace okey
{
	template<typename TKey, typename TValue, typename TMutex = FastMutex, typename TEventMutex = FastMutex>
	class ExpireLRUCache : public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >
	{
	public:
		ExpireLRUCache(std::size_t cacheSize = 1024, int64 expire = 60000):
		  AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex >(StrategyCollection<TKey, TValue>())
		{
			this->_strategy.PushBack(new LRUStrategy<TKey, TValue>(cacheSize));
			this->_strategy.PushBack(new ExpireStrategy<TKey, TValue>(expire));
		}
		~ExpireLRUCache(){}
	private:
		ExpireLRUCache(const ExpireLRUCache&);
		ExpireLRUCache& operator=(const ExpireLRUCache&);
	};
}

#endif