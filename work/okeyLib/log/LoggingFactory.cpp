#include "PreCom.h"
#include "LoggingFactory.h"


namespace okey
{
	LoggingFactory::LoggingFactory()
	{
		registerBuiltins();
	}

	LoggingFactory::~LoggingFactory()
	{

	}

	void LoggingFactory::RegisterChannelClass(const std::string& className, ChannelInstantiator* pFactory)
	{
		_channelFactory.RegisterClass(className,pFactory);
	}

// 	void LoggingFactory::RegisterFormatterClass(const std::string& className, FormatterFactory* pFactory)
// 	{
// 		_formatterFactory.RegisterClass(className,pFactory);
// 	}

	Channel* LoggingFactory::CreateChannel(const std::string& className) const
	{
		return _channelFactory.CreateInstance(className);
	}

// 	Formatter* LoggingFactory::CreateFormatter(const std::string& className) const
// 	{
// 		return _formatterFactory.CreateInstance(className);
// 	}

	LoggingFactory& LoggingFactory::GetDefaultFactory()
	{
		static LoggingFactory sh;
		return sh;
	}

	void LoggingFactory::registerBuiltins()
	{
		//手动去写。。添加的日志channel
	}
}