/********************************************************************
	created:	2015/07/16
	created:	16:27
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOGGING_FACTORY_H__
#define __LOGGING_FACTORY_H__

#include "Channel.h"
#include "Formatter.h"
#include "Instantiator.h"
#include "DynamicFactory.h"

namespace okey
{
	class LoggingFactory
	{
	public:
		typedef AbstractInstantiator<Channel>   ChannelInstantiator;
		typedef AbstractInstantiator<Formatter> FormatterFactory;
		LoggingFactory();
		~LoggingFactory();
		void RegisterChannelClass(const std::string& className, ChannelInstantiator* pFactory);
		void RegisterFormatterClass(const std::string& className, FormatterFactory* pFactory);
		Channel* CreateChannel(const std::string& className) const;
		Formatter* CreateFormatter(const std::string& className) const;
		static LoggingFactory& GetDefaultFactory();
	private:
		void registerBuiltins();
		DynamicFactory<Channel>   _channelFactory;
		DynamicFactory<Formatter> _formatterFactory;
	};
}

#endif