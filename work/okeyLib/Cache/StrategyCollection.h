/********************************************************************
	created:	2015/09/07
	created:	15:16
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_STRATEGY_COLECTION_H__
#define __CACHE_STRATEGY_COLECTION_H__

#include "AbstractStrategy.h"
#include <vector>

namespace okey
{
	template <class TKey, class TValue> 
	class StrategyCollection: public AbstractStrategy<TKey, TValue>
	{
	public:
		typedef std::vector<SharedPtr<AbstractStrategy<TKey, TValue> > > Strategies;
		typedef typename Strategies::iterator Iterator;
		typedef typename Strategies::const_iterator ConstIterator;
	public:
		StrategyCollection(){}
		~StrategyCollection(){}
		void PushBack(AbstractStrategy<TKey, TValue>* pState)
		{
			_strategies.push_back(SharedPtr<AbstractStrategy<TKey, TValue> >(pState));
		}
		void PopBack(AbstractStrategy<TKey, TValue>)
		{
			_strategies.pop_back();
		}
		virtual void OnAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnAdd(pSender, key);
			}
		}
		virtual void OnRemove(const void* pSender, const TKey& key)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnRemove(pSender, key);
			}
		}
		virtual void OnGet(const void* pSender, const TKey& key)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnGet(pSender, key);
			}
		}
		virtual void OnClear(const void* pSender, const EventArgs& args)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnClear(pSender, key);
			}
		}
		virtual void OnIsValid(const void* pSender, ValidArgs<TKey>& key)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnIsValid(pSender, key);
			}
		}
		virtual void OnReplace(const void* pSender, std::set<TKey>& elemsToRemove)
		{
			Iterator it = _strategies.begin();
			Iterator endit = _strategies.end();
			for(; it != endit; ++it)
			{
				(*it)->OnReplace(pSender, key);
			}
		}
	protected:
		Strategies _strategies;
	};
}

#endif