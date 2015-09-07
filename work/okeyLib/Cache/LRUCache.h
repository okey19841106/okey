/********************************************************************
	created:	2015/09/07
	created:	14:44
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_LRU_CAHCE_H__
#define __CACHE_LRU_CAHCE_H__

#include "AbstractCache.h"
#include "LRUStrategy.h"

namespace okey
{

	template <class TKey, class TValue,class TMutex = FastMutex, class TEventMutex = FastMutex> 
	class LRUCache: public AbstractCache<TKey, TValue, LRUStrategy<TKey, TValue>, TMutex, TEventMutex>
	{
	public:
		LRUCache(long size = 1024):
			AbstractCache<TKey, TValue, LRUStrategy<TKey, TValue>, TMutex, TEventMutex>(LRUStrategy<TKey, TValue>(size))
			{
			}

			~LRUCache()
			{
			}

	private:
		LRUCache(const LRUCache& aCache);
		LRUCache& operator = (const LRUCache& aCache);
	};
}
#endif