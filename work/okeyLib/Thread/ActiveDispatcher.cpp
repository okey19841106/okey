#include "PreCom.h"
#include "ActiveDispatcher.h"


namespace okey
{
	namespace
	{
		class MethodNotification: public Notification
		{
		public:
			MethodNotification(ActiveRunnableBase::Ptr pRunnable):
			  _pRunnable(pRunnable)
			  {
			  }

			  ActiveRunnableBase::Ptr GetRunnable() const
			  {
				  return _pRunnable;
			  }

		private:
			ActiveRunnableBase::Ptr _pRunnable;
		};

		class StopNotification: public Notification
		{
		};
	}

	ActiveDispatcher::ActiveDispatcher()
	{
		_thread.Start(*this);
	}

	ActiveDispatcher::ActiveDispatcher(Thread::Priority prio)
	{
		_thread.SetOSPriority(prio);
		_thread.Start(*this);
	}

	ActiveDispatcher::~ActiveDispatcher()
	{
		try
		{
			Stop();
		}
		catch (...)
		{
		}
	}

	void ActiveDispatcher::Start(ActiveRunnableBase::Ptr pRunnable)
	{
		_queue.EnqueueNotification(new MethodNotification(pRunnable));
	}

	void ActiveDispatcher::Cancel()
	{
		_queue.Clear();
	}

	void ActiveDispatcher::Run()
	{
		AutoPtr<Notification> pNf = _queue.WaitDequeueNotification();
		while (pNf && !dynamic_cast<StopNotification*>(pNf.get()))
		{
			MethodNotification* pMethodNf = dynamic_cast<MethodNotification*>(pNf.get());
			//poco_check_ptr (pMethodNf);
			ActiveRunnableBase::Ptr pRunnable = pMethodNf->GetRunnable();
			pRunnable->AddRef(); // run will release
			pRunnable->Run();
			pNf = _queue.WaitDequeueNotification();
		}
	}

	void ActiveDispatcher::Stop()
	{
		_queue.Clear();
		_queue.WakeUpAll();
		_queue.EnqueueNotification(new StopNotification);
		_thread.Join();
	}
}
