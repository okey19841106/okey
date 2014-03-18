#include "PreCom.h"
#include "LogicGroupDef.h"
#include "LogicGroup.h"
#include <algorithm>

namespace okey
{
	bool LogicGroupDef::AddLogicNodeDef(LogicNodeDef& node)
	{
		m_nodeList.push_back(node);
		std::sort(m_nodeList.begin(),m_nodeList.end(), LogicMemberCmp());
		if (!node.pClass)
		{
			return false;
		}
		else
		{
			CClass* pClassParent = node.pClass;
			while (pClassParent)
			{
				m_classSize += pClassParent->GetClassSize();
				pClassParent = pClassParent->GetParent();
			}
			std::vector<LogicMember>::iterator itr = node.m_MemberList.begin();
			for(;itr != node.m_MemberList.end(); ++itr)
			{
				if ( itr->name== "" || itr->name.empty() || 
					itr->refname == "" || itr->refname.empty() )
				{
					continue;
				}
				CTypeBase *pType = node.pClass->GetMember(itr->refname.c_str());
				if (!pType)
				{
					continue;
				}
				LogicMemberMap::iterator iitr;
				iitr = m_logicMemberMap.find(itr->name.c_str());
				if (iitr != m_logicMemberMap.end())
				{
					continue;
				}
				m_logicMemberMap[itr->name.c_str()] = std::make_pair<int32, CTypeBase*>(node.nGroupID, pType);
			}
			return true;
		}
	}
	LogicTreeBase* LogicGroupDef::Create()
	{
		if (m_nodeList.empty())
		{
			return NULL;
		}
		LogicGroup* pGroup = NULL;//LogicFatory...
		pGroup->SetLogicGroupDef(this);
		LogicTreeBase* pRoot = NULL;
		{
			std::vector<LogicNodeDef>::iterator itr = m_nodeList.begin();
			for (;itr!=m_nodeList.end(); ++itr)
			{
				LogicTreeBase* pNode = NULL;//LogicFatory.new("itr->name.c_str()")
				if (!pNode)
				{
					continue;
				}
				pNode->SetLogicGroup(pGroup);
				pNode->SetGroupIndex(itr->nGroupID);
				pNode->SetLogicID(itr->nLogicID);
				pGroup->AddLogic(pNode);
				for (int32 i = 0; i < MAX_LOGIC_IN_OUT_PUT; ++i)
				{
					if (itr->m_InputInfo[i].LogicIndex == -1)
					{
						continue;
					}
					pNode->LinkInput(i, itr->m_InputInfo[i].LogicIndex, 
						itr->m_InputInfo[i].OutputIndex);
				}
			}
		}
		{
			std::vector<LogicNodeDef>::iterator itr = m_nodeList.begin();
			for (;itr!=m_nodeList.end(); ++itr)
			{
				if (itr->nParentID == -1)
				{
					pRoot = pGroup->GetLogic(itr->nGroupID);
					continue;
				}
				LogicTreeBase* pParent = pGroup->GetLogic(itr->nParentID);
				LogicTreeBase* pChild = pGroup->GetLogic(itr->nGroupID); //¸Ð¾õÏñLogicid
				if (pParent && pChild && (pParent != pChild))
				{
					pParent->AddChild(pChild);
				}
			}
		}
		return pRoot;
	}

	void LogicGroupDef::SetMemberValue(const char* name, int32 val, LogicGroup* pGroup)
	{
		if (!name || !pGroup)
		{
			return;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember<int32>* pMem = (CClassMember<int32>*) pType;
			pMem->SetValue(pGroup->GetLogic(logicGroupid), val);
		}
	}
	void LogicGroupDef::SetMemberValue(const char* name, float val, LogicGroup* pGroup)
	{
		if (!name || !pGroup)
		{
			return;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember<float>* pMem = (CClassMember<float>*) pType;
			pMem->SetValue(pGroup->GetLogic(logicGroupid), val);
		}
	}
	void LogicGroupDef::SetMemberValue(const char* name, const char* val, LogicGroup* pGroup)
	{
		if (!name || !val || !pGroup)
		{
			return;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember_String* pMem = (CClassMember_String*) pType;
			pMem->SetValue(pGroup->GetLogic(logicGroupid), val);
		}
	}

	int32 LogicGroupDef::GetMemberValue(const char* name, int32 defval, LogicGroup* pGroup)
	{
		if (!name  || !pGroup)
		{
			return defval;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember<int32>* pMem = (CClassMember<int32>*) pType;
			return pMem->GetValue(pGroup->GetLogic(logicGroupid));
		}
		return defval;
	}
	float LogicGroupDef::GetMemberValue(const char* name, float defval, LogicGroup* pGroup)
	{
		if (!name  || !pGroup)
		{
			return defval;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember<float>* pMem = (CClassMember<float>*) pType;
			return pMem->GetValue(pGroup->GetLogic(logicGroupid));
		}
		return defval;
	}

	char* LogicGroupDef::GetMemberValue(const char* name, char* defval, LogicGroup* pGroup)
	{
		if (!name  || !pGroup)
		{
			return defval;
		}
		LogicMemberMap::iterator itr = m_logicMemberMap.find(name);
		if (itr != m_logicMemberMap.end())
		{
			int32 logicGroupid = itr->second.first;
			CTypeBase* pType = itr->second.second;
			CClassMember_String* pMem = (CClassMember_String*) pType;
			return (char*)pMem->GetValue(pGroup->GetLogic(logicGroupid));
		}
		return defval;
	}
}