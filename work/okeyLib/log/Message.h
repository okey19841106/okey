/********************************************************************
	created:	2015/07/14
	created:	15:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_MESSAGE_H__
#define __LOG_MESSAGE_H__

#include <string>
#include <map>
#include "TimeStamp.h"

namespace okey
{
	class Message
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
		Message();
		Message(const std::string& source, const std::string& text, Priority prio);
		Message(const std::string& source, const std::string& text, Priority prio, const char* file, int32 line);
		Message(const Message& msg);
		Message(const Message& msg, const std::string& text);
		~Message();
		Message& operator = (const Message& msg);
		void Swap(Message& msg);
		void SetSource(const std::string& src);
		inline const std::string& GetSource() const{return _source;}
		void SetText(const std::string& text);
		inline const std::string& GetText() const{return _text;}
		void SetPriority(Priority prio);
		inline Priority GetPriority() const{return _prio;}
		void SetTime(const TimeStamp& time);
		inline const TimeStamp& GetTime() const{return _time;}
		void SetThread(const std::string& thread);
		inline const std::string& GetThread() const{return _thread;}
		void SetTid(int32 tid);		/// Sets the numeric thread identifier for the message.
		inline int32 GetTid() const{return _tid;}		/// Returns the numeric thread identifier for the message.
		void SetPid(long pid);
		inline long GetPid() const{return _pid;}
		void SetSourceFile(const char* file);
		const char* GetSourceFile() const{return _file;}
		void SetSourceLine(int line);
		inline int32 GetSourceLine() const{return _line;}
		const std::string& operator [] (const std::string& param) const;
		std::string& operator [] (const std::string& param);
	protected:
		void init();
		typedef std::map<std::string, std::string> StringMap;
	private:	
		std::string _source;
		std::string _text;
		Priority    _prio;
		TimeStamp   _time;
		int32        _tid;
		std::string _thread;
		long        _pid;
		const char* _file;
		int32       _line;
		StringMap*  _pMap;
	};

	inline void Swap(Message& m1, Message& m2)
	{
		m1.Swap(m2);
	}
}

#endif