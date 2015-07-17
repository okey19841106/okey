/********************************************************************
	created:	2015/07/17
	created:	11:23
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __NULL_CHANNEL_H__
#define __NULL_CHANNEL_H__

#include "Channel.h"

namespace okey
{
	class NullChannel: public Channel
	{
	public:
		NullChannel(){}
		~NullChannel(){}
		void Log(const Message& msg){}
		void SetProperty(const std::string& name, const std::string& value){}
	};

}

#endif