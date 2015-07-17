#include "PreCom.h"
#include "LogStream.h"

namespace okey
{
	LogStreamBuf::LogStreamBuf(Logger& logger, Message::Priority priority):
		_logger(logger),_priority(priority)
	{

	}

	LogStreamBuf::~LogStreamBuf()
	{

	}

	void LogStreamBuf::SetPriority(Message::Priority priority)
	{
		_priority = priority;
	}

	int LogStreamBuf::writeToDevice(char c)
	{
		if (c == '\n' || c == '\r')
		{
			Message msg(_logger.GetName(), _message, _priority);
			_message.clear();
			_logger.Log(msg);
		}
		else _message += c;
		return c;
	}

	LogIOS::LogIOS(Logger& logger, Message::Priority priority):_buf(logger,priority)
	{

	}

	LogIOS::~LogIOS()
	{

	}

	LogStreamBuf* LogIOS::rdbuf()
	{
		return &_buf;
	}

	LogStream::LogStream(Logger& logger, Message::Priority priority):LogIOS(logger,priority),std::ostream(&_buf)
	{

	}

	LogStream::LogStream(const std::string& loggerName, Message::Priority priority):LogIOS(Logger::GetLogger(loggerName), priority),
		std::ostream(&_buf)
	{

	}
	LogStream::~LogStream()
	{

	}

	LogStream& LogStream::Fatal()
	{
		return Priority(Message::PRIO_FATAL);
	}

	LogStream& LogStream::Fatal(const std::string& message)
	{
		_buf.GetLogger().Fatal(message);
		return Priority(Message::PRIO_FATAL);
	}

	LogStream& LogStream::Critical()
	{
		return Priority(Message::PRIO_CRITICAL);
	}

	LogStream& LogStream::Critical(const std::string& message)
	{
		_buf.GetLogger().Critical(message);
		return Priority(Message::PRIO_CRITICAL);
	}

	LogStream& LogStream::Error()
	{
		return Priority(Message::PRIO_ERROR);
	}

	LogStream& LogStream::Error(const std::string& message)
	{
		_buf.GetLogger().Error(message);
		return Priority(Message::PRIO_ERROR);
	}

	LogStream& LogStream::Warning()
	{
		return Priority(Message::PRIO_WARNING);
	}

	LogStream& LogStream::Warning(const std::string& message)
	{
		_buf.GetLogger().Warning(message);
		return Priority(Message::PRIO_WARNING);
	}

	LogStream& LogStream::Notice()
	{
		return Priority(Message::PRIO_NOTICE);
	}

	LogStream& LogStream::Notice(const std::string& message)
	{
		_buf.GetLogger().Notice(message);
		return Priority(Message::PRIO_NOTICE);
	}

	LogStream& LogStream::Information()
	{
		return Priority(Message::PRIO_INFORMATION);
	}

	LogStream& LogStream::Information(const std::string& message)
	{
		_buf.GetLogger().Information(message);
		return Priority(Message::PRIO_INFORMATION);
	}

	LogStream& LogStream::Debug()
	{
		return Priority(Message::PRIO_DEBUG);
	}

	LogStream& LogStream::Debug(const std::string& message)
	{
		_buf.GetLogger().Debug(message);
		return Priority(Message::PRIO_DEBUG);
	}

	LogStream& LogStream::Trace()
	{
		return Priority(Message::PRIO_TRACE);
	}

	LogStream& LogStream::Trace(const std::string& message)
	{
		_buf.GetLogger().Trace(message);
		return Priority(Message::PRIO_TRACE);
	}

	LogStream& LogStream::Priority(Message::Priority priority)
	{
		_buf.SetPriority(priority);
		return *this;
	}
}