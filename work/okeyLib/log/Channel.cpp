#include "PreCom.h"
#include "Channel.h"
#include "Exception.h"

namespace okey
{
	Channel::Channel()
	{

	}
	void Channel::Open()
	{

	}

	void Channel::Close()
	{

	}

	void Channel::SetProperty(const std::string& name, const std::string& value)
	{
		throw PropertyNotSupportedException(name);
	}

	std::string Channel::GetProperty(const std::string& name) const
	{
		throw PropertyNotSupportedException(name);
	}
}