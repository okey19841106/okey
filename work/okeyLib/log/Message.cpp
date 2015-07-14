#include "PreCom.h"
#include "Message.h"
#include "process/Process.h"
#include "Thread/Thread.h"

namespace okey
{
	Message::Message():
	_prio(PRIO_FATAL), 
		_tid(0), 
		_pid(0),
		_file(NULL),
		_line(NULL),
		_pMap(NULL) 
	{
		init();
	}
	
	Message::Message(const std::string& source, const std::string& text, Priority prio):
	_source(source),_text(text),_prio(prio), _tid(0), _pid(0),	_file(NULL), _line(NULL), _pMap(NULL) 
	{
		init();
	}

	Message::Message(const std::string& source, const std::string& text, Priority prio, const char* file, int32 line):
	_source(source),_text(text),_prio(prio), _tid(0), _pid(0),	_file(file), _line(line), _pMap(NULL) 
	{
		init();
	}

	Message::Message(const Message& msg):
	_source(msg._source),
		_text(msg._text),
		_prio(msg._prio),
		_time(msg._time),
		_tid(msg._tid),
		_thread(msg._thread),
		_pid(msg._pid),
		_file(msg._file),
		_line(msg._line)
	{
		if (msg._pMap)
			_pMap = new StringMap(*msg._pMap);
		else
			_pMap = NULL;
	}

	Message::Message(const Message& msg, const std::string& text):
	_source(msg._source),
		_text(text),
		_prio(msg._prio),
		_time(msg._time),
		_tid(msg._tid),
		_thread(msg._thread),
		_pid(msg._pid),
		_file(msg._file),
		_line(msg._line)
	{
		if (msg._pMap)
			_pMap = new StringMap(*msg._pMap);
		else
			_pMap = NULL;
	}

	Message::~Message()
	{
		delete _pMap;
	}

	Message& Message::operator = (const Message& msg)
	{
		if (&msg != this)
		{
			Message tmp(msg);
			Swap(tmp);
		}
		return *this;
	}

	void Message::Swap(Message& msg)
	{
		using std::swap;
		swap(_source, msg._source);
		swap(_text, msg._text);
		swap(_prio, msg._prio);
		swap(_time, msg._time);
		swap(_tid, msg._tid);
		swap(_thread, msg._thread);
		swap(_pid, msg._pid);
		swap(_file, msg._file);
		swap(_line, msg._line);
		swap(_pMap, msg._pMap);
	}

	void Message::SetSource(const std::string& src)
	{
		_source = src;
	}
	
	void Message::SetText(const std::string& text)
	{
		_text = text;
	}
	
	void Message::SetPriority(Priority prio)
	{
		_prio = prio;
	}
	
	void Message::SetTime(const TimeStamp& time)
	{
		_time = time;
	}
	
	void Message::SetThread(const std::string& thread)
	{
		_thread = thread;
	}
	
	void Message::SetTid(int32 tid)
	{
		_tid = tid;
	}
	
	void Message::SetPid(long pid)
	{
		_pid = pid;
	}
	
	void Message::SetSourceFile(const char* file)
	{
		_file = file;
	}
	
	void Message::SetSourceLine(int line)
	{
		_line = line;
	}
	
	const std::string& Message::operator [] (const std::string& param) const
	{
		if (_pMap)
			return (*_pMap)[param];
		else
			throw NotFoundException();
	}
	
	std::string& Message::operator [] (const std::string& param)
	{
		if (!_pMap)
			_pMap = new StringMap;
		return (*_pMap)[param];
	}

	void Message::init()
	{
		_pid = Process::GetID();
		Thread* pThread = Thread::Current();
		if (pThread)
		{
			_tid    = pThread->GetID();
			_thread = pThread->GetName();
		}
	}
}