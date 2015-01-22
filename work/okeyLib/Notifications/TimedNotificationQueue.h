/********************************************************************
	created:	2015/01/22
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __TIMED_NOTIFICATION_QUEUE_H_
#define __TIMED_NOTIFICATION_QUEUE_H_

#include "Notification.h"
#include <map>
#include "TimeStamp.h"
#include "Thread/Mutex.h"
#include "Thread/Event.h"

namespace okey
{
	class NotificationCenter;

	class  TimedNotificationQueue
	{
	public:
		TimedNotificationQueue();
		~TimedNotificationQueue();
		void EnqueueNotification(Notification::Ptr pNotification, TimeStamp timestamp);		/// Enqueues the given notification by adding it to
		Notification* DequeueNotification();		/// Dequeues the next pending notification.
		Notification* WaitDequeueNotification();		/// Dequeues the next pending notification.
		Notification* WaitDequeueNotification(uint32 milliseconds);		/// Dequeues the next pending notification.
		bool Empty() const;		/// Returns true iff the queue is empty.
		int32 GetSize() const;		/// Returns the number of notifications in the queue.
		void Clear();		/// Removes all notifications from the queue.
	protected:
		typedef std::multimap<TimeStamp, Notification::Ptr> NfQueue;
		Notification::Ptr dequeueOne(NfQueue::iterator& it);
		bool wait(uint32 interval);
	private:
		NfQueue           _nfQueue;
		Event			_nfAvailable;
		mutable FastMutex _mutex;
	};
}

#endif