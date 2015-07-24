#include "PreCom.h"
#include "Channel.h"
#include "Exception.h"

namespace okey
{
	Channel::Channel()
	{

	}

	Channel::~Channel()
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

	void Channel::Log(int32 pro, char const* msg, ...)
	{
		char szBuf[MAX_LOG_LINE_BUFF] = {0};
		va_list args;
		va_start(args, msg);
		tvsnprintf(szBuf,MAX_LOG_LINE_BUFF - 1, msg, args);
		va_end(args);
		logInstance(pro, szBuf);	
	}

}