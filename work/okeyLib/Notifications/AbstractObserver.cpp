#include "PreCom.h"
#include "AbstractObserver.h"


namespace okey
{
	AbstractObserver::AbstractObserver()
	{
	}


	AbstractObserver::AbstractObserver(const AbstractObserver& observer)
	{
	}


	AbstractObserver::~AbstractObserver()
	{
	}


	AbstractObserver& AbstractObserver::operator = (const AbstractObserver& observer)
	{
		return *this;
	}
}