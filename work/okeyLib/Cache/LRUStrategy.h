/********************************************************************
	created:	2015/09/07
	created:	14:44
	author:		okey
	
	purpose:	最近最少使用
*********************************************************************/
#ifndef __CACHE_LRU_STRATEGY_H__
#define __CACHE_LRU_STRATEGY_H__

#include "AbstractStrategy.h"
#include <list>
#include <map>

namespace okey
{
	template<typename TKey, typename TValue>
	class LRUStrategy: public AbstractStrategy<TKey, TValue>
	{
	public:
		typedef std::list<TKey> Keys;
		typedef typename Keys::iterator Iterator;
		typedef typename Keys::const_iterator ConstIterator;
		typedef std::map<TKey, Iterator> KeyIndex;
		typedef typename KeyIndex::iterator IndexIterator;
		typedef typename KeyIndex::const_iterator ConstIndexIterator;
	public:
		LRUStrategy(std::size_t s):_size(s)
		{
			//assert size < 1
		}
		~LRUStrategy(){}

		virtual void OnAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key)
		{
			_keys.push_front(key.key());
			std::pair<IndexIterator, bool> stat = _keyIndex.insert(std::make_pair(key.key(), _keys.front()));
			if (!stat.second)
			{
				stat.first->second = _keys.begin();
			}
			
		}

		virtual void OnRemove(const void* , const TKey& key)
		{
			Iterator it = _keyIndex.find(key);
			if (it != _keyIndex.end())
			{
				_keyIndex.erase(it);
				_keys.erase(it->second);
			}
		}

		virtual void OnGet(const void* , const TKey& key)
		{
			IndexIterator it = _keyIndex.find(key);
			if ( it != _keyIndex.end())
			{
				_keys.splice(_keys.begin(), _keys, it->second);
				it->second = _keys.begin();
			}
			
		}
		virtual void OnClear(const void* , const EventArgs& args)
		{
			_keys.clear();
			_keyIndex.clear();
		}
		virtual void OnIsValid(const void* , ValidArgs<TKey>& key)
		{
			if (_keyIndex.find(key.key()) == _keyIndex.end())
			{
				key.invalidate();
			}
		}

		virtual void OnReplace(const void* , std::set<TKey>& elemsToRemove)
		{
			size_t curSize = _keyIndex.size();
			if (curSize < _size)
			{
				return;
			}
			std::size_t diff = curSize - _size;
			Iterator it = --_keys.end();
			std::size_t i = 0;
			while(i++ < diff)
			{
				elemsToRemove.insert(*it);
				if (it != _keys.begin())
				{
					--it;
				}
			}
		}
	protected:
		std::size_t _size;
		Keys _keys;
		KeyIndex _keyIndex;
	};
}

#endif