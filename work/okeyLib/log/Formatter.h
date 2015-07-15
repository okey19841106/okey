/********************************************************************
	created:	2015/07/15
	created:	16:28
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __LOG_FORMATTER_H__
#define __LOG_FORMATTER_H__

#include "Configurable.h"
#include "CRefcounter.h"

namespace okey
{
	class Message;

	class Formatter: public Configurable, public CRefCounter
	{
	public:
		Formatter();
		virtual ~Formatter();
		virtual void Format(const Message& msg, std::string& text) = 0;
		void SetProperty(const std::string& name, const std::string& value);
		std::string GetProperty(const std::string& name) const;
	};
}

#endif