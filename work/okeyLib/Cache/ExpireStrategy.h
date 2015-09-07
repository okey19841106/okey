/********************************************************************
	created:	2015/09/07
	created:	11:19
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_EXPIRATION_STRATEGY_H__
#define __CACHE_EXPIRATION_STRATEGY_H__

#include "AbstractStrategy.h"
#include <map>
#include "TimeStamp.h"


namespace okey
{
	template<typename TKey, typename TValue>
	class ExpireStrategy: public AbstractStrategy<TKey, TValue>
	{
	public:
		typedef std::multimap<TimeStamp, TKey> TimeIndex;
		typedef typename TimeIndex::iterator IndexIterator;
		typedef typename TimeIndex::const_iterator ConstIndexIterator;
		typedef std::map<TKey, IndexIterator> Keys;
		typedef typename Keys::iterator Iterator;
	public:
		ExpireStrategy(int64 e):_expireTime(e)
		{
// 			if (_expireTime < 25)
// 			{
// 				///assert 必须要多于25毫秒的。一个tick？
// 			}
		}
		~ExpireStrategy()
		{

		}

		virtual void OnAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key)
		{
			TimeStamp now;
			typename TimeIndex::value_type tiValue(now, key.key());
			IndexIterator it = _keyIndex.insert(tiValue);
			typename Keys::value_type kValue(key.key(), it);
			std::pair<Iterator, bool> stat = _keys.insert(kValue);
			if (!state.second)
			{
				_keyIndex.erase(stat.first->second);
				stat.first->second = it;
			}
			
		}

		virtual void OnRemove(const void* , const TKey& key)
		{
			Iterator it = _keys.find(key);
			if (it != _keys.end())
			{
				_keyIndex.erase(it->second);
				_keys.erase(it);
			}
		}

		virtual void OnGet(const void* , const TKey& key)
		{

		}
		virtual void OnClear(const void* , const EventArgs& args)
		{
			_keys.clear();
			_keyIndex.clear();
		}
		virtual void OnIsValid(const void* , ValidArgs<TKey>& key)
		{
			Iterator it = _keys.find(key.key());
			if (it != _keys.end())
			{
				if (it->second->first.isElapsed(_expireTime))
				{
					key.invalidate();
				}
			}
			else
				key.invalidate();
			
		}

		virtual void OnReplace(const void* , std::set<TKey>& elemsToRemove)
		{
			IndexIterator it = _keyIndex.begin();
			while(it != _keyIndex.end() && it->first.isElapsed(_expireTime))
			{
				elemsToRemove.insert(it->second);
				++it;
			}
		}
	protected:
		int64 _expireTime;
		Keys _keys;
		TimeIndex _keyIndex;
	};
}

#endif