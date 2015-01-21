/********************************************************************
	created:	2015/01/20
	created:	18:04
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_OBSERVER_H__
#define __OKEY_OBSERVER_H__

namespace okey
{
	class Notification;

	class  AbstractObserver
	{
	public:
		AbstractObserver();
		AbstractObserver(const AbstractObserver& observer);
		virtual ~AbstractObserver();
		AbstractObserver& operator = (const AbstractObserver& observer);
		virtual void Notify(Notification* pNf) const = 0;
		virtual bool Equals(const AbstractObserver& observer) const = 0;
		virtual bool Accepts(Notification* pNf) const = 0;
		virtual AbstractObserver* Clone() const = 0;
		virtual void Disable() = 0;
	};
}

#endif