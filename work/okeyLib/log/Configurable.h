/********************************************************************
	created:	2015/07/10
	created:	16:14
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_CONFIGUREABLE_H__
#define __BASE_CONFIGUREABLE_H__

#include <string>

namespace okey
{
	class Configurable
	{
	public:
		Configurable(){}
		virtual ~Configurable(){}

		virtual void SetProperty(const std::string& name, const std::string& value) = 0;
		virtual std::string GetProperty(const std::string& name) const = 0;
	};
}

#endif