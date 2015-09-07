/********************************************************************
	created:	2015/09/07
	created:	11:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_UNIQUE_EXPIRATION_CACHE_H__
#define __CACHE_UNIQUE_EXPIRATION_CACHE_H__

#include "AbstractCache.h"
#include "UniqueExpireStrategy.h"

namespace okey
{
	template <class TKey, class TValue, class TMutex = FastMutex, class TEventMutex = FastMutex> 
	class UniqueExpireCache: public AbstractCache<TKey, TValue, UniqueExpireStrategy<TKey, TValue>, TMutex, TEventMutex>
	{
	public:
		UniqueExpireCache():
		  AbstractCache<TKey, TValue, ExpireStrategy<TKey, TValue>, TMutex, TEventMutex>(UniqueExpireStrategy<TKey, TValue>())
		{

		}
		~ExpireCache(){}
	private:
		UniqueExpireCache(const UniqueExpireCache&);
		UniqueExpireCache& operator=(const UniqueExpireCache&);
	};
}

#endif