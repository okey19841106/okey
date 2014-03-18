/********************************************************************
	created:	2013/06/17
	created:	17-6-2013   23:20
	author:		okey
	
	purpose:	
*********************************************************************/


#ifndef __PARAM_DEF_MANAGER_H__
#define __PARAM_DEF_MANAGER_H__

#include "TManager.h"
#include "ParamDef.h"
#include "CircleList.h"
#include "Singleton.h"
#include "Thread/Mutex.h"

namespace okey
{
	class ParamDefManager: public TManager<ParamDef>, public Singleton<ParamDefManager, Mutex>
	{
		typedef CircleList<ParamDef*,512> ParamDefList;
	public:
		int32 GetCount(){return m_count;}
		bool Load(const char* path);
		template<typename tLock>
		bool AddObj(ParamDef* obj)
		{
			if (!obj || !obj->GetName())
			{
				return false;
			}
			int32 tindex = obj->GetID();
			if (GetObj(obj->GetName()))
			{
				return false;
			}
			m_Tmap[obj->GetName()] = obj;
			if (!m_DefList.Add(tindex,obj))
			{
				return false;
			}
			if (tindex > m_maxindex)
			{
				m_maxindex = tindex;
			}
			++m_count;
			if (!obj->GetBufferAlloc())
			{
				obj->SetBufferAlloc(new PoolAllocator<tLock>());
			}
			return true;
		}
		int32 GetMaxIndex(){return m_maxindex;}
		ParamDef* GetParamDef(uint32 index);
		ParamDefManager()
		{
			m_count = 0;
			m_maxindex = 0;
		}
		~ParamDefManager(){}
	protected:
	private:
		int32 m_count;
		int32 m_maxindex;
		ParamDefList m_DefList;
	private:
		ParamDefManager(const ParamDefManager&);
		ParamDefManager& operator=(const ParamDefManager&);
	};

	
}

#endif