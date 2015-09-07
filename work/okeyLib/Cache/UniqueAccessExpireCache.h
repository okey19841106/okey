/********************************************************************
	created:	2015/09/07
	created:	11:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_UNIQUE_ACCESS_EXPIRATION_CACHE_H__
#define __CACHE_UNIQUE_ACCESS_EXPIRATION_CACHE_H__

#include "AbstractCache.h"
#include "UniqueAccessExpireStrategy.h"

namespace okey
{
	template <class TKey, class TValue, class TMutex = FastMutex, class TEventMutex = FastMutex> 
	class UniqueAccessExpireCache: public AbstractCache<TKey, TValue, UniqueAccessExpireStrategy<TKey, TValue>, TMutex, TEventMutex>
	{
	public:
		UniqueAccessExpireCache(int64 expire = 60000):
		  UniqueAccessExpireCache<TKey, TValue, ExpireStrategy<TKey, TValue>, TMutex, TEventMutex>(UniqueAccessExpireStrategy<TKey, TValue>(expire))
		{

		}
		~AccessExpireCache(){}
	private:
		UniqueAccessExpireCache(const UniqueAccessExpireCache&);
		UniqueAccessExpireCache& operator=(const UniqueAccessExpireCache&);
	};
}

#endif