#include "PreCom.h"
#include "Notification.h"
#include <typeinfo>


namespace okey
{
	Notification::Notification()
	{

	}

	std::string Notification::GetName() const
	{
		return typeid(*this).name();
	}

	Notification::~Notification()
	{

	}
}