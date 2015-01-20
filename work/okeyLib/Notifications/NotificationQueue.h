/********************************************************************
	created:	2015/01/20
	created:	17:09
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NOTIFICATION_QUEUE_H__
#define __NOTIFICATION_QUEUE_H__

#include "Notification.h"
#include <deque>
#include "Thread/Event.h"
#include "Thread/Mutex.h"


namespace okey
{
	class NotificationCenter;

	class  NotificationQueue
	{
	public:
		NotificationQueue();
		~NotificationQueue();
		void EnqueueNotification(Notification::Ptr pNotification);		/// Enqueues the given notification by adding it to
		
		void EnqueueUrgentNotification(Notification::Ptr pNotification);		/// Enqueues the given notification by adding it to
		

		Notification* DequeueNotification();		/// Dequeues the next pending notification.
		

		Notification* WaitDequeueNotification();		/// Dequeues the next pending notification.
		

		Notification* WaitDequeueNotification(long milliseconds);		/// Dequeues the next pending notification.
		

		void Dispatch(NotificationCenter& notificationCenter);		/// Dispatches all queued notifications to the given
		

		void WakeUpAll();		/// Wakes up all threads that wait for a notification.

		bool Empty() const;		/// Returns true iff the queue is empty.

		int GetSize() const;		/// Returns the number of notifications in the queue.

		void Clear();		/// Removes all notifications from the queue.

		bool HasIdleThreads() const;			/// Returns true if the queue has at least one thread waiting for a notification.

		static NotificationQueue& DefaultQueue();		/// Returns a reference to the default NotificationQueue.

	protected:
		Notification::Ptr dequeueOne();
	private:
		typedef std::deque<Notification::Ptr> NfQueue;
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