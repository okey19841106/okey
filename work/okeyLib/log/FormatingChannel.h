/********************************************************************
	created:	2015/07/15
	created:	17:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_FORMATING_CHANNEL_H__
#define __LOG_FORMATING_CHANNEL_H__

#include "Channel.h"

namespace okey
{
	class Formatter;

	class FormatingChannel: public Channel
	{
	public:
		FormatingChannel();
		FormatingChannel(Formatter* pFormater);
		FormatingChannel(Formatter* pFormater, Channel* pChannel);
		void Open();
		void Close();
		void Log(const Message& msg) = 0;
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;

		void SetFormatter(Formatter* pFormatter);
		Formatter* GetFormatter() const;
		void SetChannel(Channel* pChannel);
		Channel* GetChannel() const;
	protected:
		~FormatingChannel();
	private:
		Formatter* _pFormatter;
		Channel* _pChannel;
	};
}

#endif