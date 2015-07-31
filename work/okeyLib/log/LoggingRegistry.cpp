#include "PreCom.h"
#include "LoggingRegistry.h"


namespace okey
{
	LoggingRegistry::LoggingRegistry()
	{

	}

	LoggingRegistry::~LoggingRegistry()
	{

	}
	Channel* LoggingRegistry::GetChannelForName(const std::string& name) const
	{
		FastMutex::ScopedLock lock(_mutex);
		ChannelMap::const_iterator it = _channelMap.find(name);
		if (it != _channelMap.end())
			return const_cast<Channel*>(it->second.get());
		else
			return NULL;
	}
// 	Formatter* LoggingRegistry::GetFormatterForName(const std::string& name) const
// 	{
// 		FastMutex::ScopedLock lock(_mutex);
// 		FormatterMap::const_iterator it = _formatterMap.find(name);
// 		if (it != _formatterMap.end())
// 			return const_cast<Formatter*>(it->second.get());
// 		else
// 			return NULL;
// 	}

	void LoggingRegistry::RegisterChannel(const std::string& name, Channel* pChannel)
	{
		FastMutex::ScopedLock lock(_mutex);
		_channelMap[name] = ChannelPtr(pChannel, true);
	}

// 	void LoggingRegistry::RegisterFormatter(const std::string& name, Formatter* pFormatter)
// 	{
// 		FastMutex::ScopedLock lock(_mutex);
// 		_formatterMap[name] = FormatterPtr(pFormatter, true);
// 	}

	void LoggingRegistry::UnRegisterChannel(const std::string& name)
	{
		FastMutex::ScopedLock lock(_mutex);
		
		ChannelMap::const_iterator it = _channelMap.find(name);
		if (it != _channelMap.end())
			_channelMap.erase(it);

	}

// 	void LoggingRegistry::UnRegisterFormatter(const std::string& name)
// 	{
// 		FastMutex::ScopedLock lock(_mutex);
// 
// 		FormatterMap::const_iterator it = _formatterMap.find(name);
// 		if (it != _formatterMap.end())
// 			_formatterMap.erase(it);
// 	}
	void LoggingRegistry::Clear()
	{
		FastMutex::ScopedLock lock(_mutex);

		_channelMap.clear();
		//_formatterMap.clear();
	}

	LoggingRegistry& LoggingRegistry::GetDefaultRegistry()
	{
		static LoggingRegistry sh;
		return sh;
	}
}