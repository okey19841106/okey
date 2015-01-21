/********************************************************************
	created:	2015/01/20
	created:	15:33
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __THREAD_ACTIVE_DISPATCHER_H__
#define __THREAD_ACTIVE_DISPATCHER_H__

#include "Runnable.h"
#include "Thread.h"
#include "ActiveRunnable.h"
#include "ActivieStarter.h"
#include "Notifications/NotificationQueue.h"

namespace okey
{

	class ActiveDispatcher: protected Runnable
	{
	public:
		ActiveDispatcher();		/// Creates the ActiveDispatcher.
		ActiveDispatcher(Thread::Priority prio);		/// Creates the ActiveDispatcher and sets the priority of its thread.
		virtual ~ActiveDispatcher();		/// Destroys the ActiveDispatcher.
		void Start(ActiveRunnableBase::Ptr pRunnable);		/// Adds the Runnable to the dispatch queue.
		void Cancel();		/// Cancels all queued methods.

	protected:
		void Run();
		void Stop();

	private:
		Thread            _thread;
		NotificationQueue _queue;
	};

	template <>
	class ActiveStarter<ActiveDispatcher>
		/// A specialization of ActiveStarter
		/// for ActiveDispatcher.
	{
	public:
		static void Start(ActiveDispatcher* pOwner, ActiveRunnableBase::Ptr pRunnable)
		{
			pOwner->Start(pRunnable);
		}
	};
}


#endif