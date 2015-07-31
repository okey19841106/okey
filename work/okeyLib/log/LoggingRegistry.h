/********************************************************************
	created:	2015/07/16
	created:	10:24
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOGGING_REGISTRY_H__
#define __LOGGING_REGISTRY_H__

#include "Channel.h"
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
		
		void RegisterChannel(const std::string& name, Channel* pChannel);
		
		void UnRegisterChannel(const std::string& name);
		void UnRegisterFormatter(const std::string& name);
		void Clear();
		static LoggingRegistry& GetDefaultRegistry();
	private:
		typedef AutoPtr<Channel>   ChannelPtr;
		
		typedef std::map<std::string, ChannelPtr> ChannelMap;
		

		ChannelMap   _channelMap;
		
		mutable FastMutex _mutex;
	};
}

#endif