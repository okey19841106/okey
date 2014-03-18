#ifndef __LOGGER_H__
#define __LOGGER_H__

 


#include "Types.h"
#include <sstream>
#include "Thread/Mutex.h"

namespace okey
{


	class Logger
	{
	public:
		Logger();
		Logger( const std::string& fileName );
		~Logger();

	public:
		void Debug( const std::string& msg );

		void Info( const std::string& msg );
		void Warn( const std::string& msg );
		void Error( const std::string& msg );
		void Fatal( const std::string& msg );

	private:
		std::ostream* m_OutStream;
		bool m_OnlyToCout;

		Mutex m_pMutex;
	};

#define LOG_DEBUG( logger, msg ) \
{ \
	std::ostringstream format_msg; \
	format_msg << msg; \
	logger.Debug( format_msg.str() ); \
}

#define LOG_INFO( logger, msg ) \
{ \
	std::ostringstream format_msg; \
	format_msg << msg; \
	logger.Info( format_msg.str() ); \
}

#define  LOG_WARN( logger, msg ) \
{ \
	std::ostringstream format_msg; \
	format_msg << msg; \
	logger.Warn( format_msg.str() ); \
}

#define LOG_ERROR( logger, msg ) \
{ \
	std::ostringstream format_msg; \
	format_msg << msg; \
	logger.Error( format_msg.str() ); \
}

#define LOG_FATAL( logger, msg ) \
{ \
	std::ostringstream format_msg; \
	format_msg << msg; \
	logger.Fatal( format_msg.str() ); \
}
	extern Logger logger;
} //namespace okey



#endif //LOGGER_H
