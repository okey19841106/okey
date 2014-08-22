/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:35
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __FACTORY_MANAGER_H__
#define __FACTORY_MANAGER_H__


#include "HashMap.h"

namespace okey
{

	class CFactoryArg0_Base;

	class FactoryManager_Arg0
	{
	public:
		FactoryManager_Arg0();
		~FactoryManager_Arg0();

		void CollectMemory();
		int64 GetUsageMemory();
		void* CreateObj(uint32 classID);
		void* CreateObj(const char* name);
		void FreeObj(void* ptr);

		void AddFactory(CFactoryArg0_Base* pFun);
		uint32 GetFactoryCount(){return (uint32)m_FactoryList.size();}

	public:
		static hash_map<uint32, std::string> m_UtilList;
	protected:
		hash_map<uint32, CFactoryArg0_Base*> m_FactoryList;
	};


	extern FactoryManager_Arg0& GetFactoryArg0();

}

#endif