#include "PreCom.h"
#include "FormatingChannel.h"
#include "Formatter.h"
#include "Message.h"

namespace okey
{
	FormatingChannel::FormatingChannel():_pFormatter(NULL),_pChannel(NULL)
	{

	}

	FormatingChannel::FormatingChannel(Formatter* pFormater):_pFormatter(pFormater),_pChannel(NULL)
	{
		if (_pFormatter) 
			_pFormatter->AddRef();
	}

	FormatingChannel::FormatingChannel(Formatter* pFormater, Channel* pChannel):_pFormatter(pFormater),_pChannel(pChannel)
	{
		if (_pFormatter) 
			_pFormatter->AddRef();
		if (_pChannel)
			_pChannel->AddRef();
	}

	void FormatingChannel::Open()
	{
		if (_pChannel)
		{
			_pChannel->Open();
		}
	}

	void FormatingChannel::Close()
	{
		if (_pChannel)
		{
			_pChannel->Close();
		}
	}

	FormatingChannel::~FormatingChannel()
	{
		if (_pChannel)  
			_pChannel->DecRef();
		if (_pFormatter) 
			_pFormatter->DecRef();
	}

	void FormatingChannel::Log(const Message& msg)
	{
		if (_pChannel)
		{
			if (_pFormatter)
			{
				std::string text;
				_pFormatter->Format(msg, text);
				_pChannel->Log(Message(msg, text));
			}
			else
			{
				_pChannel->Log(msg);
			}
		}
	}

	void FormatingChannel::SetProperty(const std::string& name, const std::string& value)
	{

	}

	std::string FormatingChannel::GetProperty(const std::string& name) const
	{

	}

	void FormatingChannel::SetFormatter(Formatter* pFormatter)
	{
		if (_pFormatter) 
			_pFormatter->DecRef();
		_pFormatter = pFormatter;
		if (_pFormatter) 
			_pFormatter->AddRef();
	}
	
	Formatter* FormatingChannel::GetFormatter() const
	{
		return _pFormatter;
	}

	void FormatingChannel::SetChannel(Channel* pChannel)
	{
		if (_pChannel) 
			_pChannel->DecRef();
		_pChannel = pChannel;
		if (_pChannel) 
			_pChannel->AddRef();
	}

	Channel* FormatingChannel::GetChannel() const
	{
		return _pChannel;
	}
}

