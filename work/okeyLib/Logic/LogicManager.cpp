#include "PreCom.h"
#include "LogicManager.h"
#include "LogicTreeBase.h"
#include "LogicGroup.h"
#include "LogicGroupDef.h"

namespace okey
{
	LogicManagerBase::LogicManagerBase()
	{
		for (int32 i = 0; i < MAX_LOGIC_GROUP_LIST; ++i)
		{
			m_logicDefList[i] = NULL;
		}
	}
	LogicManagerBase::~LogicManagerBase()
	{
		Clear();
	}
	bool LogicManagerBase::Load(const char* path)
	{
		return false;
	}
	LogicTreeBase* LogicManagerBase::MakeLogic(int32 id)
	{
		LogicTreeBase* res = m_logicList[id].Pop_Head();
		if(!res)
		{
			if (m_logicDefList[id])
			{
				m_logicDefList[id]->Create();
			}
		}
		if (!res)
		{
			return NULL;
		}
		res->Reset();
		LogicGroup* pGroup = res->GetLogicGroup();
		if (pGroup)
		{
			pGroup->Reset();
		}
		return res;
	}
	bool LogicManagerBase::FreeLogic(LogicTreeBase* pLogic, bool bDelete)
	{
		int32 logicid = pLogic->GetLogicID();
		bool bNeedDel = false;
		if (logicid < 0 || logicid > MAX_LOGIC_LIST)
		{
			bNeedDel = true;
		}
		if (bNeedDel || bNeedDel)
		{
			LogicGroup* pGroup = pLogic->GetLogicGroup();
			if (!pGroup)
			{
				pLogic->Free();
			}
			else
			{
				for (int32 i = 0; i < MAX_LOGIC_LIST; ++i)
				{
					LogicTreeBase* tmp = pGroup->GetLogic(i);
					if (!tmp)
					{
						continue;
					}
					//factory.delete(tmp);
				}
				//factroy.delete(pGroup);
			}
		}
		else
			m_logicList[logicid].Add(pLogic);
		return true;
	}
	void LogicManagerBase::FreeMemory()
	{
		for (int32 i = 0; i < MAX_LOGIC_LIST; ++i)
		{
			LogicTreeBase* tmp = m_logicList[i].Pop_Back();
			while(tmp)
			{
				//factory.delete(tmp);
				tmp = m_logicList[i].Pop_Back();
			}
		}
	}

	LogicGroupDef* LogicManagerBase::GetLogicGroupDefine(int32 id)
	{
		if (id < 0 || id > MAX_LOGIC_LIST)
		{
			return NULL;
		}
		return m_logicDefList[id];
	}

	void LogicManagerBase::Clear()
	{
		for (int32 i = 0; i < MAX_LOGIC_LIST; ++i)
		{
			delete m_logicDefList[i];
			LogicTreeBase* tmp = m_logicList[i].Pop_Back();
			while(tmp)
			{
				//factory.delete(tmp);
				tmp = m_logicList[i].Pop_Back();
			}
		}
		
	}

	LogicDataManager::LogicDataManager(LogicManagerBase* mgr):m_pManager(mgr){}

	LogicDataManager::~LogicDataManager()
	{
		Clear();
	}
	bool LogicDataManager::Load(const char* sFile, CfgLoaderBase* pLoader)
	{
		return false;
	}
	void LogicDataManager::Clear()
	{
		for(int32 i = 0; i < DATA_GROUP_MAX; ++i)
		{
			delete m_datagrouplist[i];
		}
	}

	bool LogicDataManager::InitLogic(LogicTreeBase* pLogic, int32 dataid)
	{
		if (!pLogic || dataid < 0)
		{
			return false;
		}
		int32 logicid = pLogic->GetLogicID();
		DataBufferBase* pData = GetDataBuffer(logicid, dataid);
		if (pData)
		{
			pLogic->Buffer2Data(pData->GetBuffer(), Type_Print);
			return true;
		}
		else
		{
			pData = GetDataBuffer(logicid,0);
			if (!pData)
			{
				return false;
			}
			pLogic->Buffer2Data(pData->GetBuffer(), Type_Print);
			return true;
		}
		return false;

	}

	void LogicManagerSingleton::PrintClass()
	{

	}
}