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
	class Message;

	class Channel: public Configurable, public CRefCounter
	{
	public:
		Channel();
		virtual void Open();
		virtual void Close();
		virtual void Log(const Message& msg) = 0;
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
	protected:
		~Channel();
	private:
		Channel(const Channel&);
		Channel& operator = (const Channel&);
	};
}

#endif