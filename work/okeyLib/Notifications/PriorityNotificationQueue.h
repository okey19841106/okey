/********************************************************************
	created:	2015/01/22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PRIORITY_NOTIFICATION_QUEUE_H__
#define __PRIORITY_NOTIFICATION_QUEUE_H__

#include "Notification.h"
#include <map>
#include <deque>
#include "Thread/Mutex.h"
#include "Thread/Event.h"

namespace okey
{
	class NotificationCenter;

	class  PriorityNotificationQueue
	{
	public:
		PriorityNotificationQueue();
		~PriorityNotificationQueue();
		void EnqueueNotification(Notification::Ptr pNotification, int32 priority);		/// Enqueues the given notification by adding it to
		Notification* DequeueNotification();		/// Dequeues the next pending notification.
		Notification* WaitDequeueNotification();		/// Dequeues the next pending notification.
		Notification* WaitDequeueNotification(uint32 milliseconds);		/// Dequeues the next pending notification.
		void Dispatch(NotificationCenter& notificationCenter);		/// Dispatches all queued notifications to the given
		void WakeUpAll();		/// Wakes up all threads that wait for a notification.
		bool Empty() const;		/// Returns true iff the queue is empty.
		int32 GetSize() const;		/// Returns the number of notifications in the queue.
		void Clear();		/// Removes all notifications from the queue.
		bool HasIdleThreads() const;			/// Returns true if the queue has at least one thread waiting for a notification.
		static PriorityNotificationQueue& DefaultQueue();		/// Returns a reference to the default NotificationQueue.
	protected:
		Notification::Ptr dequeueOne();
	private:
		typedef std::multimap<int32, Notification::Ptr> NfQueue;
		struct WaitInfo
		{
			Notification::Ptr pNf;
			Event             nfAvailable;
		};
		typedef std::deque<WaitInfo*> WaitQueue;

		NfQueue           _nfQueue;
		WaitQueue         _waitQueue;
		mutable FastMutex _mutex;
	};
}

#endif