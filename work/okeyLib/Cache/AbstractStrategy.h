/********************************************************************
	created:	2015/09/06
	created:	17:50
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __CACHE_ABSTRACT_STRATEGY_H__
#define __CACHE_ABSTRACT_STRATEGY_H__

#include "KeyValueArgs.h"
#include "Events/EventArgs.h"
#include "ValidArgs.h"
#include <set>

namespace okey
{
	template <class TKey, class TValue> 
	class AbstractStrategy
	{
	public:
		AbstractStrategy()
		{
		}

		virtual ~AbstractStrategy()
		{
		}

		virtual void OnUpdate(const void* pSender, const KeyValueArgs <TKey, TValue>& args)
		{
			OnRemove(pSender,args.key());
			OnAdd(pSender, args);
		}
		virtual void OnAdd(const void* pSender, const KeyValueArgs <TKey, TValue>& key) = 0;
		virtual void OnRemove(const void* pSender, const TKey& key) = 0;
		virtual void OnGet(const void* pSender, const TKey& key) = 0;
		virtual void OnClear(const void* pSender, const EventArgs& args) = 0;
		virtual void OnIsValid(const void* pSender, ValidArgs<TKey>& key) = 0;
		virtual void OnReplace(const void* pSender, std::set<TKey>& elemsToRemove) = 0;
	};
}

#endif