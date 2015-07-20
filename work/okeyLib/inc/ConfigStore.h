/********************************************************************
	created:	2015/07/20
	created:	14:21
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __BASE_CONFIG_STORE_H__
#define __BASE_CONFIG_STORE_H__

#include <string>
#include "Configure.h"

namespace okey
{
	class ConfigStore
	{
		friend class Configure;
	public:
		ConfigStore(const std::string& path);
		virtual ~ConfigStore();

		inline const std::string& path() const{ return _path; }
	protected:
		virtual void read(Configure::Key& root) = 0;
		virtual void update(Configure::Key& root) = 0;
	private:
		std::string _path;

	};
}

#endif