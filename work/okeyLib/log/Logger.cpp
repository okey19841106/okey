#include "PreCom.h"
#include "Logger.h"
#include "LoggingRegistry.h"
#include "StringHelper.h"
#include "Exception.h"

namespace okey
{
	Logger::LoggerMap* Logger::_pLoggerMap = NULL;
	Mutex      Logger::_mapMtx;
	const std::string Logger::ROOT;

	Logger::Logger(const std::string& name, Channel* pChannel, int32 level):
		_name(name),_pChannel(pChannel),_level(level)
	{
		if(_pChannel)
			_pChannel->AddRef();
	}

	Logger::~Logger()
	{
		if (_pChannel)
		{
			_pChannel->DecRef();
		}
	}

	void Logger::SetChannel(Channel* pChannel)
	{
		if (_pChannel)
		{
			_pChannel->DecRef();
		}
		_pChannel = pChannel;
		if (_pChannel)
		{
			_pChannel->AddRef();
		}
		
	}

	Channel* Logger::GetChannel() const
	{
		return _pChannel;
	}

	void Logger::SetLevel(int32 level)
	{
		_level = level;
	}
	void Logger::SetLevel(const std::string &level)
	{
		SetLevel(ParseLevel(level));
	}

	void Logger::SetProperty(const std::string& name, const std::string& value)
	{
		if (name == "channel")
			SetChannel(LoggingRegistry::GetDefaultRegistry().GetChannelForName(value));
		else if (name == "level")
			SetLevel(value);
		else 
			Channel::SetProperty(name, value);
	}

	void Logger::Log(const Message& msg)
	{
		if (_level >= msg.GetPriority() && _pChannel)
		{
			_pChannel->Log(msg);
		}
	}

	void Logger::Log(const Exception& exc)
	{
		Error(exc.displayText());
	}

	void Logger::Log(const Exception& exc, const char* file, int line)
	{
		Error(exc.displayText(),file, line);
	}

	void Logger::Dump(const std::string& msg, const void* buffer, std::size_t length, Message::Priority prio)
	{
		if (_level >= prio && _pChannel)
		{
			std::string text(msg);
			FormatDump(text, buffer, length);
			_pChannel->Log(Message(_name, text, prio));
		}
	}

	std::string Logger::format(const std::string& fmt, int argc, std::string argv[])
	{
		std::string result;
		std::string::const_iterator it = fmt.begin();
		while (it != fmt.end())
		{
			if (*it == '$')
			{
				++it;
				if (*it == '$')
				{
					result += '$';
				}
				else if (*it >= '0' && *it <= '9')
				{
					int i = *it - '0';
					if (i < argc)
						result += argv[i];
				}
				else
				{
					result += '$';
					result += *it;
				}
			}
			else 
				result += *it;
			++it;
		}
		return result;
	}

	Logger& Logger::parent(const std::string& name)
	{
		std::string::size_type pos = name.rfind('.');
		if (pos != std::string::npos)
		{
			std::string pname = name.substr(0, pos);
			Logger* pParent = find(pname);
			if (pParent)
				return *pParent;
			else
				return parent(pname);
		}
		else 
			return UnSafeGetLogger(ROOT);
	}

	void Logger::add(Logger* pLogger)
	{
		if (!_pLoggerMap)
			_pLoggerMap = new LoggerMap;
		_pLoggerMap->insert(LoggerMap::value_type(pLogger->GetName(), pLogger));
	}

	Logger* Logger::find(const std::string& name)
	{
		if (_pLoggerMap)
		{
			LoggerMap::iterator it = _pLoggerMap->find(name);
			if (it != _pLoggerMap->end())
				return it->second;
		}
		return 0;
	}

	std::string Logger::Format(const std::string& fmt, const std::string& arg)
	{
		std::string args[] =
		{
			arg
		};
		return format(fmt, 1, args);
	}

	std::string Logger::Format(const std::string& fmt, const std::string& arg0, const std::string& arg1)
	{
		std::string args[] =
		{
			arg0,arg1
		};
		return format(fmt, 2, args);
	}
	std::string Logger::Format(const std::string& fmt, const std::string& arg0, const std::string& arg1, const std::string& arg2)
	{
		std::string args[] =
		{
			arg0,arg1,arg2
		};
		return format(fmt, 3, args);
	}
	std::string Logger::Format(const std::string& fmt, const std::string& arg0, const std::string& arg1, const std::string& arg2, const std::string& arg3)
	{
		std::string args[] =
		{
			arg0,arg1,arg2,arg3
		};
		return format(fmt, 4, args);
	}
	void Logger::FormatDump(std::string& message, const void* buffer, std::size_t length)
	{
		const int BYTES_PER_LINE = 16;
		message.reserve(message.size() + length*6);
		if (!message.empty()) 
			message.append("\n");
		unsigned char* base = (unsigned char*) buffer;
		int addr = 0;
		while (addr < length)
		{
			if (addr > 0) message.append("\n");
			
			message.append(TO_HEX_STRING_INT(addr,4));
			message.append("  ");
			int offset = 0;
			while (addr + offset < length && offset < BYTES_PER_LINE)
			{
				message.append(TO_HEX_STRING_INT(base[addr + offset], 2));
				message.append(offset == 7 ? "  " : " ");
				++offset;
			}
			if (offset < 7) message.append(" ");
			while (offset < BYTES_PER_LINE) { message.append("   "); ++offset; }
			message.append(" ");
			offset = 0;
			while (addr + offset < length && offset < BYTES_PER_LINE)
			{
				unsigned char c = base[addr + offset];
				message += (c >= 32 && c < 127) ? (char) c : '.';
				++offset;
			}
			addr += BYTES_PER_LINE;
		}
	}
	void Logger::SetLevel(const std::string& name, int level)
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (_pLoggerMap)
		{
			std::string::size_type len = name.length();
			for (LoggerMap::iterator it = _pLoggerMap->begin(); it != _pLoggerMap->end(); ++it)
			{
				if (len == 0 || 
					(it->first.compare(0, len, name) == 0 && (it->first.length() == len || it->first[len] == '.')))
				{
					it->second->SetLevel(level);
				}
			}
		}
	}
	void Logger::SetChannel(const std::string& name, Channel* pChannel)
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (_pLoggerMap)
		{
			std::string::size_type len = name.length();
			for (LoggerMap::iterator it = _pLoggerMap->begin(); it != _pLoggerMap->end(); ++it)
			{
				if (len == 0 || 
					(it->first.compare(0, len, name) == 0 && (it->first.length() == len || it->first[len] == '.')))
				{
					it->second->SetChannel(pChannel);
				}
			}
		}
		
	}
	void Logger::SetProperty(const std::string& loggerName, const std::string& propertyName, const std::string& value)
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (_pLoggerMap)
		{
			std::string::size_type len = loggerName.length();
			for (LoggerMap::iterator it = _pLoggerMap->begin(); it != _pLoggerMap->end(); ++it)
			{
				if (len == 0 ||
					(it->first.compare(0, len, loggerName) == 0 && (it->first.length() == len || it->first[len] == '.')))
				{
					it->second->SetProperty(propertyName, value);
				}
			}
		}
	}

	Logger& Logger::GetLogger(const std::string& name)
	{
		Mutex::ScopedLock lock(_mapMtx);
		return UnSafeGetLogger(name);
	}

	Logger& Logger::UnSafeGetLogger(const std::string& name)
	{
		Logger* pLogger = find(name);
		if (!pLogger)
		{
			if (name == ROOT)
			{
				pLogger = new Logger(name, NULL, Message::PRIO_INFORMATION);
			}
			else
			{
				Logger& par = parent(name);
				pLogger = new Logger(name, par.GetChannel(), par.GetLevel());
			}
			add(pLogger);
		}
		return *pLogger;
	}
	Logger& Logger::CreateLogger(const std::string& name, Channel* pChannel, int32 level)
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (find(name)) 
			throw ExistsException();
		Logger* pLogger = new Logger(name, pChannel, level);
		add(pLogger);
		return *pLogger;
	}

	Logger& Logger::GetRoot()
	{
		Mutex::ScopedLock lock(_mapMtx);
		return UnSafeGetLogger(ROOT);
	}

	Logger* Logger::HasLogger(const std::string& name)
	{
		Mutex::ScopedLock lock(_mapMtx);
		return find(name);
	}

	void Logger::DestroyLogger(const std::string& name)
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (_pLoggerMap)
		{
			LoggerMap::iterator it = _pLoggerMap->find(name);
			if (it != _pLoggerMap->end())
			{
				it->second->DecRef();
				_pLoggerMap->erase(it);
			}
		}
	}

	void Logger::ShutDown()
	{
		Mutex::ScopedLock lock(_mapMtx);
		if (_pLoggerMap)
		{
			for (LoggerMap::iterator it = _pLoggerMap->begin(); it != _pLoggerMap->end(); ++it)
			{
				it->second->DecRef();
			}
			delete _pLoggerMap;
			_pLoggerMap = NULL;
		}
	}
	void Logger::GetNames(std::vector<std::string>& names)
	{
		Mutex::ScopedLock lock(_mapMtx);
		names.clear();
		if (_pLoggerMap)
		{
			for (LoggerMap::const_iterator it = _pLoggerMap->begin(); it != _pLoggerMap->end(); ++it)
			{
				names.push_back(it->first);
			}
		}
	}

	int32 Logger::ParseLevel(const std::string& level)
	{
		if (icompare(level, "none") == 0)
			return 0;
		else if (icompare(level, "fatal") == 0)
			return Message::PRIO_FATAL;
		else if (icompare(level, "critical") == 0)
			return Message::PRIO_CRITICAL;
		else if (icompare(level, "error") == 0)
			return Message::PRIO_ERROR;
		else if (icompare(level, "warning") == 0)
			return Message::PRIO_WARNING;
		else if (icompare(level, "notice") == 0)
			return Message::PRIO_NOTICE;
		else if (icompare(level, "information") == 0)
			return Message::PRIO_INFORMATION;
		else if (icompare(level, "debug") == 0)
			return Message::PRIO_DEBUG;
		else if (icompare(level, "trace") == 0)
			return Message::PRIO_TRACE;
		else
			throw InvalidArgumentException("Not a valid log level", level);
	}

	class AutoLoggerShutdown
	{
	public:
		AutoLoggerShutdown()
		{
		}
		~AutoLoggerShutdown()
		{
			Logger::ShutDown();
		}
	};


	namespace
	{
		static AutoLoggerShutdown als; //不用关心关闭。
	}
}
