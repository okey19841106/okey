/********************************************************************
	created:	2015/09/07
	created:	11:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_EXPIRATION_CACHE_H__
#define __CACHE_EXPIRATION_CACHE_H__

#include "AbstractCache.h"
#include "ExpireStrategy.h"

namespace okey
{
	template <class TKey, class TValue, class TMutex = FastMutex, class TEventMutex = FastMutex> 
	class ExpireCache: public AbstractCache<TKey, TValue, ExpireStrategy<TKey, TValue>, TMutex, TEventMutex>
	{
	public:
		ExpireCache(int64 expire = 60000):
		  AbstractCache<TKey, TValue, ExpireStrategy<TKey, TValue>, TMutex, TEventMutex>(ExpireStrategy<TKey, TValue>(expire))
		{

		}
		~ExpireCache(){}
	private:
		ExpireCache(const ExpireCache&);
		ExpireCache& operator=(const ExpireCache&);
	};
}

#endif