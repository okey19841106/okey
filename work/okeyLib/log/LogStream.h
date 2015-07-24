/********************************************************************
	created:	2015/07/16
	created:	18:04
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_STREAM_H__
#define __LOG_STREAM_H__

#include "Logger.h"
#include "Stream/UnBufferedStreamBuf.h"

namespace okey
{
	class LogStreamBuf: public UnBufferedStreamBuf
	{
	public:
		LogStreamBuf(Logger& logger, Channel::Priority priority);
		~LogStreamBuf();
		void SetPriority(Channel::Priority priority);
		inline Channel::Priority GetPriority() const{return _priority;}
		inline Logger& GetLogger() const{return _logger;}
	private:
		int writeToDevice(char c);
	private:
		Logger&           _logger;
		Channel::Priority _priority;
		std::string       _message;
	};

	class LogIOS: public virtual std::ios
	{
	public:
		LogIOS(Logger& logger, Channel::Priority priority);
		~LogIOS();
		LogStreamBuf* rdbuf();
	protected:
		LogStreamBuf _buf;
	};

	class LogStream: public LogIOS, public std::ostream
	{
	public:
		LogStream(Logger& logger, Channel::Priority priority = Channel::PRIO_INFORMATION);
		LogStream(const std::string& loggerName, Channel::Priority priority = Channel::PRIO_INFORMATION);
		~LogStream();
		LogStream& Fatal();
		LogStream& Fatal(const std::string& message);
		LogStream& Critical();
		LogStream& Critical(const std::string& message);
		LogStream& Error();
		LogStream& Error(const std::string& message);
		LogStream& Warning();
		LogStream& Warning(const std::string& message);
		LogStream& Notice();
		LogStream& Notice(const std::string& message);
		LogStream& Information();
		LogStream& Information(const std::string& message);
		LogStream& Debug();
		LogStream& Debug(const std::string& message);
		LogStream& Trace();
		LogStream& Trace(const std::string& message);
		LogStream& Priority(Channel::Priority priority);
	};
}

#endif