/********************************************************************
	created:	2015/01/20
	created:	17:48
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NOTIFICATION_CENTER_H__
#define __NOTIFICATION_CENTER_H__

#include "SharedPtr.h"
#include "Thread/Mutex.h"
#include "Notification.h"
#include <vector>

namespace okey
{
	class AbstractObserver;
	class NotificationCenter
	{
	public:
		NotificationCenter();
		~NotificationCenter();
		void AddObserver(const AbstractObserver& observer);		/// Registers an observer with the NotificationCenter.
		void RemoveObserver(const AbstractObserver& observer);		/// Unregisters an observer with the NotificationCenter.
		void PostNotification(Notification::Ptr pNotification);		/// Posts a notification to the NotificationCenter.
		bool HasObservers() const;		/// Returns true iff there is at least one registered observer.
		uint32 CountObservers() const;		/// Returns the number of registered observers.
		static NotificationCenter& DefaultCenter();		/// Returns a reference to the default
	private:
		typedef SharedPtr<AbstractObserver> AbstractObserverPtr;
		typedef std::vector<AbstractObserverPtr> ObserverList;

		ObserverList  _observers;
		mutable Mutex _mutex;
	};
}

#endif