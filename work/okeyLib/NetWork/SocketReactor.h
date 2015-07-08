/********************************************************************
	created:	2015/07/07
	created:	11:14
	author:		okey
	
	purpose:	
*********************************************************************/

#include "Thread/Runnable.h"
#include "TimeSpan.h"
#include "Notifications/Observer.h"
#include "AutoPtr.h"
#include <map>

namespace okey
{
	class Socket;
	class SocketNotification;
	class SocketNotifier;

	class SocketReactor: public Runnable
	{
	public:
		SocketReactor();
		~SocketReactor();
		explicit SocketReactor(const TimeSpan& timeout);
		void Init();
		void Run();
		void Stop(); //stop the reactor
		void SetTimeout(const TimeSpan& timeout);
		const TimeSpan& GetTimeout() const;
		void AddEventHandler(const Socket& socket, const AbstractObserver& observer);
		void RemoveEventHandler(const Socket& socket, const AbstractObserver& observer);
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
		typedef std::map<Socket, NotifierPtr> EventHandlerMap;
		void Dispatch(NotifierPtr& pNotifer, SocketNotification* pNotification);

		enum
		{
			DEFAULT_TIMEOUT = 250000
		};

		bool _stop;
		TimeSpan  _timeout;
		EventHandlerMap _handlers;
		NotificationPtr _pReadableNotification;
		NotificationPtr _pWritableNotification;
		NotificationPtr _pErrorNotification;
		NotificationPtr _pTimeoutNotification;
		NotificationPtr _pIdleNotification;
		NotificationPtr _pShutdownNotification;
		FastMutex _mutex;

		friend class SocketNotifier;
	};
}