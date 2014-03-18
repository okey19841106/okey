#include "PreCom.h"
#include "LogicGroup.h"
#include "LogicGroupDef.h"

namespace okey
{
	LogicGroup::LogicGroup():m_classSize(0),m_pDef(NULL),
	m_bTerminate(false)
	{

	}
	LogicGroup::~LogicGroup()
	{
		
	}
	void LogicGroup::SetLogicGroupDef(LogicGroupDef* pDef)
	{
		if (!pDef)
		{
			return;
		}
		m_classSize = pDef->GetClassSize();
		m_pDef = pDef;
	}
	bool LogicGroup::AddLogic(LogicTreeBase* pLogic)
	{
		if (!pLogic)
		{
			return false;
		}
		int32 index = pLogic->GetGroupIndex();
		m_logicList[index] = pLogic;
		return true;
	}
}