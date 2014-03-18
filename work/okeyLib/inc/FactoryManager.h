/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:35
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __FACTORY_MANAGER_H__
#define __FACTORY_MANAGER_H__

#include "Types.h"
#include "TManager.h"
#include "Factory.h"

namespace okey
{
	

	class FactoryManagerArg0Base: public TManager<CFactoryArg0_Base>
	{
	public:
		//void PrintClass();
		FactoryManagerArg0Base(){}
		~FactoryManagerArg0Base(){}
		void CollectMemory();
		int64 GetUsageMemory();
		void* CreateObj(const char* name);
		void FreeObj(const char* name, void* ptr);
		
	protected:
	private:
		
	};

	class FactoryManagerArg0: public FactoryManagerArg0Base
	{
	public:
		static FactoryManagerArg0& GetSingleton()
		{
			static FactoryManagerArg0 m_instance;
			return m_instance;
		}
	protected:
	private:
		FactoryManagerArg0(){}
		~FactoryManagerArg0(){}
		FactoryManagerArg0(const FactoryManagerArg0&);
		FactoryManagerArg0& operator=(const FactoryManagerArg0&);
	};

#define s_FactoryManager FactoryManagerArg0::GetSingleton()
}

#endif