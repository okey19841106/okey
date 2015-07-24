/********************************************************************
	created:	2015/07/10
	created:	16:17
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_LOG_CHANNEL_H__
#define __BASE_LOG_CHANNEL_H__

#include "CRefcounter.h"
#include "Configurable.h"

namespace okey
{

#define MAX_LOG_LINE_BUFF 4096

	class Message;

	class Channel: public Configurable, public CRefCounter
	{
	public:
		enum Priority
		{
			PRIO_FATAL = 1,   /// A fatal error.
			PRIO_CRITICAL,    /// A critical error. 
			PRIO_ERROR,       /// An error. 
			PRIO_WARNING,     /// A warning.
			PRIO_NOTICE,      /// A notice
			PRIO_INFORMATION, /// An informational message
			PRIO_DEBUG,       /// A debugging message.
			PRIO_TRACE        /// A tracing message.
		};
	public:
		Channel();
		virtual void Open();
		virtual void Close();
		void Log(int32 pro, char const* msg, ...);
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
	protected:
		virtual ~Channel();
		virtual void logInstance(int32 pro, const char* msg) = 0;
	private:
		Channel(const Channel&);
		Channel& operator = (const Channel&);
	};
}

#endif