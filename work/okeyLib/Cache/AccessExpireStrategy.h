/********************************************************************
	created:	2015/09/07
	created:	11:19
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_ACCESS_EXPIRATION_STRATEGY_H__
#define __CACHE_ACCESS_EXPIRATION_STRATEGY_H__

#include "AbstractStrategy.h"
#include <map>
#include "TimeStamp.h"


namespace okey
{
	template<typename TKey, typename TValue>
	class AccessExpireStrategy: public ExpireStrategy<TKey, TValue>
	{
	public:
		AccessExpireStrategy(int64 e):ExpireStrategy<TKey, TValue>(e)
		{
		
		}
		~AccessExpireStrategy()
		{

		}

		virtual void OnGet(const void* , const TKey& key)
		{
			typename ExpireStrategy<TKey, TValue>::Iterator it = this->_keys.find(key);
			if (it != this->_keys.end())
			{
				this->_keyIndex.erase(it->second);
				Timestamp now;
				typename ExpireStrategy<TKey, TValue>::IndexIterator itIdx =
					this->_keyIndex.insert(typename ExpireStrategy<TKey, TValue>::TimeIndex::value_type(now, key));
				it->second = itIdx;
			}
		}

	};
}

#endif