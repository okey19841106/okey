/********************************************************************
	created:	2014/08/21
	created:	14:09
	author:		
	
	purpose:	
*********************************************************************/

#ifndef __T_CLASS_MANAGER_H__
#define __T_CLASS_MANAGER_H__

#include <string>
#include "HashMap.h"


namespace okey
{
	class TClass;

	class TClassManager
	{
	public:
		TClassManager();
		~TClassManager();

		void AddClass(TClass* pClass);
		TClass* GetClass(const std::string& name);
		uint32 GetClassCount()const;
	protected:

		hash_map<std::string, TClass*> m_classList;
	};

	extern inline TClassManager& GetTClassManager();

}

#endif