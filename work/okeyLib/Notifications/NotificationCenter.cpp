#include "PreCom.h"
#include "NotificationCenter.h"
#include "AbstractObserver.h"

namespace okey
{
	NotificationCenter::NotificationCenter()
	{

	}
	NotificationCenter::~NotificationCenter()
	{

	}
	void NotificationCenter::AddObserver(const AbstractObserver& observer)
	{
		Mutex::ScopedLock lock(_mutex);
		_observers.push_back(observer.Clone());
	}
	void NotificationCenter::RemoveObserver(const AbstractObserver& observer)
	{
		Mutex::ScopedLock lock(_mutex);
		for (ObserverList::iterator it = _observers.begin(); it != _observers.end(); ++it)
		{
			if (observer.Equals(**it))
			{
				(*it)->Disable();
				_observers.erase(it);
				return;
			}
		}
	}
	void NotificationCenter::PostNotification(Notification::Ptr pNotification)//自动清理notification的指针。
	{
		ScopedLockWithUnlock<Mutex> lock(_mutex);
		ObserverList observersToNotify(_observers);
		lock.UnLock();
		for (ObserverList::iterator it = observersToNotify.begin(); it != observersToNotify.end(); ++it)
		{
			(*it)->Notify(pNotification);
		}
	}
	bool NotificationCenter::HasObservers() const
	{
		Mutex::ScopedLock lock(_mutex);
		return !_observers.empty();
	}
	uint32 NotificationCenter::CountObservers() const
	{
		Mutex::ScopedLock lock(_mutex);
		return (uint32)_observers.size();
	}
	NotificationCenter& NotificationCenter::DefaultCenter()
	{
		static NotificationCenter s;
		return s;
	}
}
