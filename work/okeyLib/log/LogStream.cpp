#include "PreCom.h"
#include "LogStream.h"
#include "Logger.h"

namespace okey
{
	LogStreamBuf::LogStreamBuf(Logger& logger, Channel::Priority priority):
		_logger(logger),_priority(priority)
	{

	}

	LogStreamBuf::~LogStreamBuf()
	{

	}

	void LogStreamBuf::SetPriority(Channel::Priority priority)
	{
		_priority = priority;
	}

	int LogStreamBuf::writeToDevice(char c)
	{
		if (c == '\n' || c == '\r')
		{
			_logger.log(_message, _priority);
		}
		else _message += c;
		return c;
	}

	LogIOS::LogIOS(Logger& logger, Channel::Priority priority):_buf(logger,priority)
	{

	}

	LogIOS::~LogIOS()
	{

	}

	LogStreamBuf* LogIOS::rdbuf()
	{
		return &_buf;
	}

	LogStream::LogStream(Logger& logger, Channel::Priority priority):LogIOS(logger,priority),std::ostream(&_buf)
	{

	}

	LogStream::LogStream(const std::string& loggerName, Channel::Priority priority):LogIOS(Logger::GetLogger(loggerName), priority),
		std::ostream(&_buf)
	{

	}
	LogStream::~LogStream()
	{

	}

	LogStream& LogStream::Fatal()
	{
		return Priority(Channel::PRIO_FATAL);
	}

	LogStream& LogStream::Fatal(const std::string& message)
	{
		_buf.GetLogger().Fatal(message);
		return Priority(Channel::PRIO_FATAL);
	}

	LogStream& LogStream::Critical()
	{
		return Priority(Channel::PRIO_CRITICAL);
	}

	LogStream& LogStream::Critical(const std::string& message)
	{
		_buf.GetLogger().Critical(message);
		return Priority(Channel::PRIO_CRITICAL);
	}

	LogStream& LogStream::Error()
	{
		return Priority(Channel::PRIO_ERROR);
	}

	LogStream& LogStream::Error(const std::string& message)
	{
		_buf.GetLogger().Error(message);
		return Priority(Channel::PRIO_ERROR);
	}

	LogStream& LogStream::Warning()
	{
		return Priority(Channel::PRIO_WARNING);
	}

	LogStream& LogStream::Warning(const std::string& message)
	{
		_buf.GetLogger().Warning(message);
		return Priority(Channel::PRIO_WARNING);
	}

	LogStream& LogStream::Notice()
	{
		return Priority(Channel::PRIO_NOTICE);
	}

	LogStream& LogStream::Notice(const std::string& message)
	{
		_buf.GetLogger().Notice(message);
		return Priority(Channel::PRIO_NOTICE);
	}

	LogStream& LogStream::Information()
	{
		return Priority(Channel::PRIO_INFORMATION);
	}

	LogStream& LogStream::Information(const std::string& message)
	{
		_buf.GetLogger().Information(message);
		return Priority(Channel::PRIO_INFORMATION);
	}

	LogStream& LogStream::Debug()
	{
		return Priority(Channel::PRIO_DEBUG);
	}

	LogStream& LogStream::Debug(const std::string& message)
	{
		_buf.GetLogger().Debug(message);
		return Priority(Channel::PRIO_DEBUG);
	}

	LogStream& LogStream::Trace()
	{
		return Priority(Channel::PRIO_TRACE);
	}

	LogStream& LogStream::Trace(const std::string& message)
	{
		_buf.GetLogger().Trace(message);
		return Priority(Channel::PRIO_TRACE);
	}

	LogStream& LogStream::Priority(Channel::Priority priority)
	{
		_buf.SetPriority(priority);
		return *this;
	}
}