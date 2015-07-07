/********************************************************************
	created:	2015/07/07
	created:	11:14
	author:		okey
	
	purpose:	
*********************************************************************/

#include "Thread/Runnable.h"
#include "TimeSpan.h"

namespace okey
{
	class SocketReactor: public Runnable
	{
	public:
		SocketReactor();
		~SocketReactor();
		explicit SocketReactor(const TimeSpan& timeout);

		void Run();
		void Stop(); //stop the reactor
		void SetTimeout(const TimeSpan& timeout);
		const TimeSpan& GetTimeout() const;
		void addEventHandler(const Socket& socket, const AbstractObserver& observer);
		void removeEventHandler(const Socket& socket, const AbstractObserver& observer);
	protected:
		virtual void OnTimeout();// call if timeout
		virtual void OnIdle();//call if no socket
		virtual void OnShutdown();// call if terminate
		virtual void OnBusy();//call if busy and at least on notification has been dispatched.
		void Dispatch(const Socket& socket, SocketNotification* pNotification);
		void Dispatch(SocketNotification* pNotification);
	private:
		typedef AutoPtr<SocketNotifier> NotifierPtr;
		typedef AutoPtr<SocketNotification> NotificationPtr;
		typedef std::map<Socket, NotificationPtr> EventHandlerMap;
		void Dispatch(NotifierPtr& pNotifer, SocketNotification* pNotification);


	};
}