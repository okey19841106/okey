/********************************************************************
	created:	2015/07/16
	created:	10:24
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOGGING_REGISTRY_H__
#define __LOGGING_REGISTRY_H__

#include "Channel.h"
#include "Formatter.h"
#include <string>
#include <map>
#include "Thread/Mutex.h"
#include "AutoPtr.h"


namespace okey
{
	class LoggingRegistry
	{
	public:
		LoggingRegistry();
		~LoggingRegistry();
		Channel* GetChannelForName(const std::string& name) const;
		Formatter* GetFormatterForName(const std::string& name) const;
		void RegisterChannel(const std::string& name, Channel* pChannel);
		void RegisterFormatter(const std::string& name, Formatter* pFormatter);
		void UnRegisterChannel(const std::string& name);
		void UnRegisterFormatter(const std::string& name);
		void Clear();
		static LoggingRegistry& GetDefaultRegistry();
	private:
		typedef AutoPtr<Channel>   ChannelPtr;
		typedef AutoPtr<Formatter> FormatterPtr;
		typedef std::map<std::string, ChannelPtr> ChannelMap;
		typedef std::map<std::string, FormatterPtr> FormatterMap;

		ChannelMap   _channelMap;
		FormatterMap _formatterMap;
		mutable FastMutex _mutex;
	};
}

#endif