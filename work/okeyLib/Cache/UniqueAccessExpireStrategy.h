/********************************************************************
	created:	2015/09/07
	created:	11:19
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_UNIQUE_ACCESS_EXPIRATION_STRATEGY_H__
#define __CACHE_UNIQUE_ACCESS_EXPIRATION_STRATEGY_H__

#include "AbstractStrategy.h"
#include <map>
#include "TimeStamp.h"


namespace okey
{
	template<typename TKey, typename TValue>
	class UniqueAccessExpireStrategy: public ExpireStrategy<TKey, TValue>
	{
	public:
		typedef std::pair<TKey, int64> KeyExpire;
		typedef std::multimap<TimeStamp, KeyExpire> TimeIndex;
		typedef typename TimeIndex::iterator IndexIterator;
		typedef typename TimeIndex::const_iterator ConstIndexIterator;
		typedef std::map<TKey, IndexIterator> Keys;
		typedef typename Keys::iterator Iterator;
	public:
		UniqueAccessExpireStrategy(){}
		~UniqueAccessExpireStrategy(){}

		virtual void OnAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key)
		{
			TimeStamp expire;
			expire += key.value().GetTimeOut();
			IndexIterator it = _keyIndex.insert(std::make_pair(expire, std::make_pair(key.key(), key,value().GetTimeOut())));
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
			Iterator it = this->_keys.find(key);
			if (it != this->_keys.end())
			{
				KeyExpire ke = it->second->second;
				Timestamp expire;
				expire += ke.second;
				_keyIndex.erase(it->second);
				IndexIterator itt = _keyIndex.insert(std::make_pair(expire, ke));
				it->second = itt;
			}
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
				TimeStamp now;
				if (it->second->first <= now)
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
			while(it != _keyIndex.end() && it->first < now)
			{
				elemsToRemove.insert(it->second);
				++it;
			}
		}
	protected:
		Keys _keys;
		TimeIndex _keyIndex;

	};
}

#endif