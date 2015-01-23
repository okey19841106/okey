/********************************************************************
	created:	2015/01/23
	created:	14:36
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NOTIFICATION_STRATEGY_H__
#define __NOTIFICATION_STRATEGY_H__

namespace okey
{
	template <class TArgs, class TDelegate> 
	class NotificationStrategy
	{
	public:
		NotificationStrategy(){}
		virtual ~NotificationStrategy(){}
		virtual void Notify(const void* sender, TArgs& arguments) = 0;	/// Sends a notification to all registered delegates
		virtual void Add(const TDelegate& delegate) = 0;	/// Adds a delegate to the strategy
		virtual void Remove(const TDelegate& delegate) = 0;	/// Removes a delegate from the strategy, if found.Does nothing if the delegate has not been added.
		virtual void Clear() = 0;		/// Removes all delegates from the strategy
		virtual bool Empty() const = 0;
	};
}

#endif