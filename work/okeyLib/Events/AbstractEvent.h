/********************************************************************
	created:	2015/01/23
	created:	13:47
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __ABSTRACT_EVENT_H__
#define __ABSTRACT_EVENT_H__

namespace okey
{
	template<class TArgs, class TStrategy, class TDelegate, class TMutex = FastMutex>
	class AbstractEvent
	{
	public:
		typedef TArgs Args;
		AbstractEvent():_executeAsync(this, AbstractEvent::executeAsyncImpl),_enabled(true){}
		AbstractEvent(const TStrategy& strat):_executeAsync(this, &AbstractEvent::executeAsyncImpl),_strategy(strat),_enabled(true){}
		virtual ~AbstractEvent(){}
		void operator += (const TDelegate& aDelegate)
		{
			typename TMutex::ScopedLock lock(_mutex);
			_strategy.Add(aDelegate);
		}
		void operator -= (const TDelegate& aDelegate)
		{
			typename TMutex::ScopedLock lock(_mutex);
			_strategy.Remove(aDelegate);
		}
		void operator () (const void* pSender, TArgs& args)
		{
			Notify(pSender, args);
		}

		void operator () (TArgs& args)
		{
			Notify(NULL, args);
		}
		void Notify(const void* pSender, TArgs& args)
		{
			Poco::ScopedLockWithUnlock<TMutex> lock(_mutex);
			if (!_enabled) 
				return;
			TStrategy strategy(_strategy);
			lock.UnLock();
			strategy.Notify(pSender, args);
		}
		ActiveResult<TArgs> NotifyAsync(const void* pSender, const TArgs& args)
		{
			NotifyAsyncParams params(pSender, args);
			{
				typename TMutex::ScopedLock lock(_mutex);
				params._ptrStrat = SharedPtr<TStrategy>(new TStrategy(_strategy));
				params._enabled  = _enabled;
			}
			ActiveResult<TArgs> result = _executeAsync(params);
			return result;
		}
		void Enable()
		{
			typename TMutex::ScopedLock lock(_mutex);
			_enabled = true;
		}
		void Disable()
		{
			typename TMutex::ScopedLock lock(_mutex);
			_enabled = false;
		}
		bool IsEnabled() const
		{
			typename TMutex::ScopedLock lock(_mutex);
			return _enabled;
		}

		void Clear()
		{
			typename TMutex::ScopedLock lock(_mutex);
			_strategy.clear();
		}

		bool Empty() const
		{
			typename TMutex::ScopedLock lock(_mutex);
			return _strategy.empty();
		}
	protected:
		struct NotifyAsyncParams
		{
			SharedPtr<TStrategy> _ptrStrat;
			const void* _pSender;
			TArgs       _args;
			bool        _enabled;
			/// Default constructor reduces the need for TArgs to have an empty constructor, only copy constructor is needed.
			NotifyAsyncParams(const void* pSend, const TArgs& a):_ptrStrat(), _pSender(pSend), _args(a), _enabled(true)
			{
			}
		};
		TArgs executeAsyncImpl(const NotifyAsyncParams& par)
		{
			if (!par._enabled)
			{
				return par._args;
			}

			NotifyAsyncParams params = par;
			TArgs retArgs(params._args);
			params._ptrStrat->Notify(params.pSender, retArgs);
			return retArgs;
		}
		TStrategy _strategy; /// The strategy used to notify observers.
		bool      _enabled;  /// Stores if an event is enabled. 
		mutable TMutex _mutex;
		ActiveMethod<TArgs, NotifyAsyncParams, AbstractEvent> _executeAsync;
	private:
		AbstractEvent(const AbstractEvent& other);
		AbstractEvent& operator = (const AbstractEvent& other);
	};
}

#endif