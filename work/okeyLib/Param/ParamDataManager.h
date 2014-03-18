/********************************************************************
	created:	2013/06/12
	created:	12-6-2013   20:20
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __PARAM_DATA_MANAGER_H__
#define __PARAM_DATA_MANAGER_H__

#include "Types.h"
#include "DataBuffer.h"
#include "Singleton.h"
#include "Thread/Mutex.h"

namespace okey
{
	class ParamDefManager;
	class ParamPool;
	class CfgLoaderBase;

	class ParamDataManager: public DataManager, public Singleton<ParamDataManager,Mutex>
	{
	public:
		ParamDataManager(ParamDefManager* pDef);
		~ParamDataManager();
		bool InitParamPool(ParamPool* pPool, int32 dataID);
		bool Load(const char* sFile, CfgLoaderBase* pLoader);
	protected:
		ParamDefManager* m_pDefManager;
	private:

	};
}


#endif