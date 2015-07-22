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