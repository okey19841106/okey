/********************************************************************
	created:	2015/07/16
	created:	10:54
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

 

#include <map>
#include "Channel.h"
#include "Thread/Mutex.h"
#include <vector>
#include <sstream>


namespace okey
{
	class Exception;

	class Logger: public Channel
	{
	public:
		inline const std::string& GetName() const{return _name;}
		inline int32 GetLevel() const{return _level;}
		void SetChannel(Channel* pChannel);
		Channel* GetChannel() const;
		void SetLevel(int32 level);
		void SetLevel(const std::string& level);
		void SetProperty(const std::string& name, const std::string& value);
		void Log(const Exception& exc);
		void Log(const Exception& exc, const char* file, int line);
		void Fatal(const std::string& msg);
		void Fatal(const std::string& msg, const char* file, int line);
		void Critical(const std::string& msg);
		void Critical(const std::string& msg, const char* file, int line);
		void Error(const std::string& msg);
		void Error(const std::string& msg, const char* file, int line);
		void Warning(const std::string& msg);
		void Warning(const std::string& msg, const char* file, int line);
		void Notice(const std::string& msg);
		void Notice(const std::string& msg, const char* file, int line);
		void Information(const std::string& msg);
		void Information(const std::string& msg, const char* file, int line);
		void Debug(const std::string& msg);
		void Debug(const std::string& msg, const char* file, int line);
		void Trace(const std::string& msg);
		void Trace(const std::string& msg, const char* file, int line);
		void Dump(const std::string& msg, const void* buffer, std::size_t length, Channel::Priority prio = Channel::PRIO_DEBUG);
		inline bool IsLevel(int level) const{return _level >= level;}
		inline bool IsFatal() const{return _level >= Channel::PRIO_FATAL;}
		inline bool IsCritical() const{return _level >= Channel::PRIO_CRITICAL;}
		inline bool IsError() const{return _level >= Channel::PRIO_ERROR;}
		inline bool IsWarning() const{return _level >= Channel::PRIO_WARNING;}
		inline bool IsNotice() const{return _level >= Channel::PRIO_NOTICE;}
		inline bool IsInformation() const{return _level >= Channel::PRIO_INFORMATION;}		
		inline bool IsDebug() const{return _level >= Channel::PRIO_DEBUG;}
		inline bool IsTrace() const{return _level >= Channel::PRIO_TRACE;}
	

		void log(const std::string& text, Channel::Priority prio);
		void log(const std::string& text, Channel::Priority prio, const char* file, int line);

		static void FormatDump(std::string& message, const void* buffer, std::size_t length);
		static void SetLevel(const std::string& name, int level);
		static void SetChannel(const std::string& name, Channel* pChannel);
		static void SetProperty(const std::string& loggerName, const std::string& propertyName, const std::string& value);
		static Logger& GetLogger(const std::string& name);
		static Logger& UnSafeGetLogger(const std::string& name);
		static Logger& CreateLogger(const std::string& name, Channel* pChannel, int32 level = Channel::PRIO_INFORMATION);
		static Logger& GetRoot();
		static Logger* HasLogger(const std::string& name);
		static void DestroyLogger(const std::string& name);
		static void ShutDown();
		static void GetNames(std::vector<std::string>& names);
		static int32 ParseLevel(const std::string& level);

		static const std::string ROOT; 
	protected:
		typedef std::map<std::string, Logger*> LoggerMap;
		Logger(const std::string& name, Channel* pChannel, int32 level);
		~Logger();
		virtual void logInstance(int32 pro, const char* msg);
		
		
		static Logger& parent(const std::string& name);
		static void add(Logger* pLogger);
		static Logger* find(const std::string& name);
	private:
		Logger();
		Logger(const Logger&);
		Logger& operator = (const Logger&);
		std::string _name;
		Channel*    _pChannel;
		int32       _level;
		static LoggerMap* _pLoggerMap;
		static Mutex      _mapMtx;
	};

	void Logger::logInstance(int32 pro, const char* msg)
	{
		if (_pChannel)
		{
			_pChannel->Log(pro,msg);
		}
	}

	inline void Logger::log(const std::string& text, Channel::Priority prio)
	{
		logInstance(prio,text.c_str());
	}

	inline void Logger::log(const std::string& text, Channel::Priority prio, const char* file, int line)
	{
		std::stringstream ss;
		ss<<"["<<file<<":"<<line<<"]"<<text;
		logInstance(prio,ss.str().c_str());
	}

	inline void Logger::Fatal(const std::string& msg)
	{
		log(msg,Channel::PRIO_FATAL);
	}
	inline void Logger::Fatal(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_FATAL,file,line);
	}
	inline void Logger::Critical(const std::string& msg)
	{
		log(msg,Channel::PRIO_CRITICAL);
	}
	inline void Logger::Critical(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_CRITICAL,file,line);
	}
	inline void Logger::Error(const std::string& msg)
	{
		log(msg,Channel::PRIO_ERROR);
	}
	inline void Logger::Error(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_ERROR,file,line);
	}
	inline void Logger::Warning(const std::string& msg)
	{
		log(msg,Channel::PRIO_WARNING);
	}
	inline void Logger::Warning(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_WARNING,file,line);
	}
	inline void Logger::Notice(const std::string& msg)
	{
		log(msg,Channel::PRIO_NOTICE);
	}
	inline void Logger::Notice(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_NOTICE,file,line);
	}
	inline void Logger::Information(const std::string& msg)
	{
		log(msg,Channel::PRIO_INFORMATION);
	}
	inline void Logger::Information(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_INFORMATION,file,line);
	}
	inline void Logger::Debug(const std::string& msg)
	{
		log(msg,Channel::PRIO_DEBUG);
	}
	inline void Logger::Debug(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_DEBUG,file,line);
	}
	inline void Logger::Trace(const std::string& msg)
	{
		log(msg,Channel::PRIO_TRACE);
	}
	inline void Logger::Trace(const std::string& msg, const char* file, int line)
	{
		log(msg,Channel::PRIO_TRACE,file,line);
	}
} //namespace okey



#endif //LOGGER_H
