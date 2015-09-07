/********************************************************************
	created:	2015/09/07
	created:	11:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_ACCESS_EXPIRATION_CACHE_H__
#define __CACHE_ACCESS_EXPIRATION_CACHE_H__

#include "AbstractCache.h"
#include "AccessExpireStrategy.h"

namespace okey
{
	template <class TKey, class TValue, class TMutex = FastMutex, class TEventMutex = FastMutex> 
	class AccessExpireCache: public AbstractCache<TKey, TValue, AccessExpireStrategy<TKey, TValue>, TMutex, TEventMutex>
	{
	public:
		AccessExpireCache(int64 expire = 60000):
		  AccessExpireCache<TKey, TValue, ExpireStrategy<TKey, TValue>, TMutex, TEventMutex>(AccessExpireStrategy<TKey, TValue>(expire))
		{

		}
		~AccessExpireCache(){}
	private:
		AccessExpireCache(const AccessExpireCache&);
		AccessExpireCache& operator=(const AccessExpireCache&);
	};
}

#endif