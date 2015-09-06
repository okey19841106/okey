/********************************************************************
	created:	2015/09/06
	created:	16:21
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ABSTRACT_CACHE_H__
#define __ABSTRACT_CACHE_H__

#include "Thread/Mutex.h"
#include "Events/FIFOEvent.h"
#include "SharedPtr.h"
#include "KeyValueArgs.h"
#include "Events/EventArgs.h"
#include <map>
#include <set>
#include "Events/Delegate.h"

namespace okey
{
	template<typename TKey, class TValue, class TStrategy, typename TMutex = FastMutex, typename TEventMutex = FastMutex>
	class AbstractCache
	{
	public:

		FIFOEvent<const KeyValueArgs<TKey, TValue>, TEventMutex > Add;
		FIFOEvent<const KeyValueArgs<TKey, TValue>, TEventMutex > Update;
		FIFOEvent<const TKey, TEventMutex > Remove;
		FIFOEvent<const TKey, TEventMutex > Get;
		FIFOEvent<const EventArgs, TEventMutex> Clear;

		typedef std::map<TKey, SharedPtr<TValue> > DataHolder;
		typedef typename DataHolder::iterator Iterator;
		typedef typename DataHolder::const_iterator ConstIterator;
		typedef std::set<TKey> KeySet;

		AbstractCache()
		{
			initialize();
		}
		AbstractCache(const TStrategy& strat):_strategy(strat)
		{
			initialize();
		}
		virtual ~AbstractCache()
		{
			uninitialize();
		}

		void Add(const TKey& key, const TValue& val)
		{
			typename TMutex::ScopedLock lock(_mutex);
			doAdd(key, val)
		}

		void Update(const TKey& key, const TValue& val)
		{
			typename TMutex::ScopedLock lock(_mutex);
			doUpdate(key, val)
		}

		void Add(const TKey& key, SharedPtr<TValue>& val)
		{
			typename TMutex::ScopedLock lock(_mutex);
			doAdd(key, val)
		}

		void Update(const TKey& key,  SharedPtr<TValue>& val)
		{
			typename TMutex::ScopedLock lock(_mutex);
			doUpdate(key, val)
		}

		void Remove(const TKey& key)
		{
			typename TMutex::ScopedLock lock(_mutex);
			Iterator it = _data.find(key);
			doRemove(it);
		}

		bool Has(const TKey& key) const
		{
			typename TMutex::ScopedLock lock(_mutex);
			return doHas(key);
		}

		SharedPtr<TValue> Get(const TKey& key)
		{
			typename TMutex::ScopedLock lock(_mutex);
			return doGet(key);
		}

		void Clear()
		{
			typename TMutex::ScopedLock lock(_mutex);
			doClear();
		}

		std::size_t size()
		{
			typename TMutex::ScopedLock lock(_mutex);
			doReplace();
			return _data.size();
		}

		void ForceReplace()
		{
			typename TMutex::ScopedLock lock(_mutex);
			doReplace();
		}

		std::set<TKey> GetAllKeys()
		{
			typename TMutex::ScopedLock lock(_mutex);
			doReplace();
			ConstIterator it = _data.begin();
			ConstIterator itEnd = _data.end();
			std::set<TKey> r;
			for (; it != itEnd; ++it)
			{
				r.insert(it->first);
			}
			return r;
		}
	protected:
		mutable FIFOEvent<ValidArgs<TKey> > IsValid;
		mutable FIFOEvent<KeySet> Replace;

		void initialize()
		{
			Add += Delegate<TStrategy, const KeyValueArgs<TKey, TValue> >(&_strategy, &TStrategy::OnAdd);
			Update += Delegate<TStrategy, const KeyValueArgs<TKey, TValue> >(&_strategy, &TStrategy::OnUpdate);
			Remove += Delegate<TStrategy, const TKey >(&_strategy, &TStrategy::OnRemove);
			Get += Delegate<TStrategy, const TKey>(&_strategy, &TStrategy::OnGet);
			Clear += Delegate<TStrategy, const EventArgs >(&_strategy, &TStrategy::OnClear);
			IsValid += Delegate<TStrategy, ValidArgs<TKey> >(&_strategy, &TStrategy::OnIsValid);
			Replace += Delegate<TStrategy, KeySet >(&_strategy, &TStrategy::OnReplace);
		}
		
		void uninitialize()
		{
			Add -= Delegate<TStrategy, const KeyValueArgs<TKey, TValue> >(&_strategy, &TStrategy::OnAdd);
			Update -= Delegate<TStrategy, const KeyValueArgs<TKey, TValue> >(&_strategy, &TStrategy::OnUpdate);
			Remove -= Delegate<TStrategy, const TKey >(&_strategy, &TStrategy::OnRemove);
			Get -= Delegate<TStrategy, const TKey>(&_strategy, &TStrategy::OnGet);
			Clear -= Delegate<TStrategy, const EventArgs >(&_strategy, &TStrategy::OnClear);
			IsValid -= Delegate<TStrategy, ValidArgs<TKey> >(&_strategy, &TStrategy::OnIsValid);
			Replace -= Delegate<TStrategy, KeySet >(&_strategy, &TStrategy::OnReplace);
		}

		void doAdd(const TKey& key, const TValue& val)
		{
			Iterator it = _data.find(key);
			doRemove(it);
			KeyValueArgs<TKey, TValue> args(key, val);
			Add.Notify(this, args);
			_data.insert(std::make_pair(key, SharedPtr<TValue>(new TValue(val))));
			doReplace();
		}

		void doAdd(const TKey& key, SharedPtr<TValue>& val)
		{
			Iterator it = _data.find(key);
			doRemove(it);
			KeyValueArgs<TKey, TValue> args(key, val);
			Add.Notify(this, args);
			_data.insert(std::make_pair(key,val)));
			doReplace();
		}

		void doUpdate(const TKey& key, const TValue& val)
		{
			KeyValueArgs<TKey, TValue> args(key, val);
			Iterator it = _data.find(key);
			if (it == _data.end())
			{
				Add.Notify(this, args);
				_data.insert(std::make_pair(key, SharedPtr<TValue>(new TValue(val))));
			}
			else
			{
				Update.Notify(this, args);
				it->second =  SharedPtr<TValue>(new TValue(val));
			}
			doReplace();
		}

		void doUpdate(const TKey& key, SharedPtr<TValue>& val)
		{
			KeyValueArgs<TKey, TValue> args(key, *val);
			Iterator it = _data.find(key);
			if (it == _data.end())
			{
				Add.Notify(this, args);
				_data.insert(std::make_pair(key, val));
			}
			else
			{
				Update.Notify(this, args);
				it->second =  val;
			}
			doReplace();
		}

		void doRemove(Iterator it)
		{
			if (it != _data.end())
			{
				Remove.Notify(this, it->first);
				_data.erase(it);
			}
		}

		bool doHas(const TKey& key) const
		{
			ConstIterator it = _data.find(key);
			bool r = false;
			if (it != _data.end())
			{
				ValidArgs<TKey> args(key);
				IsValid.Notify(this, args);
				r = args.isValid();
			}
			return r;
		}

		SharedPtr<TValue> doGet(const TKey& key)
		{
			Iterator it = _data.find(key);
			SharedPtr<TValue> r;
			if (it != _data.end())
			{
				Get.Notify(this, key);
				ValidArgs<TKey> args(key);
				IsValid.Notify(this, args);
				if (!args.isValid())
				{
					doRemove(it);
				}
				else
				{
					r = it->second;
				}
			}
			return r;
		}

		void doClear()
		{
			static EventArgs _emptyArgs;
			Clear.Notify(this, _emptyArgs);
			_data.clear();
		}

		void doReplace()
		{
			std::set<TKey> delMe;
			Replace.Notify(this, delMe);

			typename std::set<TKey>::const_iterator it = delMe.begin();
			typename std::set<TKey>::const_iterator itEnd = delMe.end();
			for(; it != itEnd; ++it)
			{
				Iterator ir = _data.find(*it);
				doRemove(ir);
			}
		}

		TStrategy _strategy;
		mutable DataHolder _data;
		mutable TMutex _mutex;
	private:
		AbstractCache(const AbstractCache&);
		AbstractCache& operator= (const AbstractCache&);
	};
}

#endif