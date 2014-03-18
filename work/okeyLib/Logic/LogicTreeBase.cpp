#include "PreCom.h"
#include "LogicTreeBase.h"
#include "LogicGroup.h"

namespace okey
{
	LogicTreeBase::LogicTreeBase():m_bActive(false),
	m_bChildFirst(false),m_bselfFinish(false),
	m_bChildFinish(false),m_pOwnerGroup(NULL),
	m_GroupIndex(-1),m_LogicID(-1)//,
	//m_nextLogic(NULL),m_prevLogic(NULL),m_pList(NULL)
	{

	}

	LogicTreeBase::~LogicTreeBase()
	{

	}
	void LogicTreeBase::OnReset()
	{
		m_bActive = true;
		m_bChildFirst = false;
		m_bselfFinish = false;
		m_bChildFinish = false;
		ActiveChild();
	}
	char* LogicTreeBase::Buffer2Data(char* pBuffer, int32 flag)
	{
		char* tmpBuffer = NULL/* = Read(pBuffer,flag)*/;
		TreeNodeBase* pChild = GetNextChild(NULL);
		OnBuffer2Data();
		while (pChild)
		{
			LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
			tmpBuffer = pLogic->Buffer2Data(tmpBuffer,flag);
			pChild = GetNextChild(pChild);
		}
		return tmpBuffer;
	}

	char* LogicTreeBase::Data2Buffer(char* pBuffer, int32 flag)
	{
		char* tmpBuffer = NULL /*= Write(pBuffer,flag)*/;
		TreeNodeBase* pChild = GetNextChild(NULL);
		OnData2Buffer();
		while (pChild)
		{
			LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
			tmpBuffer = pLogic->Data2Buffer(tmpBuffer,flag);
			pChild = GetNextChild(pChild);
		}
		return tmpBuffer;
	}

	void LogicTreeBase::DoProcess()
	{
		ProcessSelf();
		ProcessChild();
	}

	bool LogicTreeBase::AddChildLogic(LogicTreeBase* pLogic)
	{
		if (pLogic && m_pOwnerGroup && (m_pOwnerGroup != pLogic->GetLogicGroup()))
		{
			m_pOwnerGroup->AddLogic(pLogic);
			pLogic->SetLogicGroup(m_pOwnerGroup);
			//pLogic->SetLogicID(m_LogicID); //认为有问题
			TreeNodeBase::AddChild(pLogic);
			return true;
		}
		return false;
	}

	bool LogicTreeBase::RemoveChildLogic(LogicTreeBase* pLogic)
	{
		if (!pLogic)
		{
			return false;
		}
		pLogic->SetLogicGroup(NULL);
		TreeNodeBase::RemoveChild(pLogic);
		return true;
	}

	bool LogicTreeBase::ProcessSelf()
	{
		if (!m_bActive || m_bselfFinish)
		{
			return false;
		}
		UpdateInput();
		PrevProcess();
		if (Process())
		{
			m_bselfFinish = true;
			m_bActive = false;
		}
		PostProcess();
		return true;
	}

	bool LogicTreeBase::ProcessChild()
	{
		if (m_bChildFirst)
		{
			if (!IsChildActive())
			{
				return false;
			}
			m_bChildFinish = true;
			TreeNodeBase* pChild = GetNextChild(NULL);
			while (pChild)
			{
				LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
				pLogic->ProcessSelf();
				pLogic->PrevProcessChild();
				pLogic->ProcessChild();
				pLogic->PostProcessChild();
				pChild = GetNextChild(pChild);
			}
		}
		else
		{
			if (!IsChildActive())
			{
				return false;
			}
			m_bChildFinish = true;
			TreeNodeBase* pChild = GetNextChild(NULL);
			while (pChild)
			{
				LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
				pLogic->ProcessSelf();
				pChild = GetNextChild(pChild);
			}
			pChild = GetNextChild(NULL);
			while (pChild)
			{
				LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
				pLogic->PrevProcessChild();
				pLogic->ProcessChild();
				pLogic->PostProcessChild();
				if (!pLogic->IsFinish())
				{
					m_bChildFinish = false;
				}
				pChild = GetNextChild(pChild);
			}

		}
		return true;
	}

	void LogicTreeBase::Reset(bool bActive)
	{
		OnReset();
		if (bActive)
		{
			ResetChild(bActive);
		}
	}
	void LogicTreeBase::ResetChild(bool bActive)
	{
		TreeNodeBase* pChild = GetNextChild(NULL);
		while (pChild)
		{
			LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
			pLogic->Reset(bActive);
			pChild = GetNextChild(pChild);
		}
	}
	bool LogicTreeBase::IsFinish()
	{
		if( (m_bselfFinish && m_bChildFinish) ||
			(m_pOwnerGroup && m_pOwnerGroup->IsTerminate()))
		{
			return true;
		}
		return false;
	}
	void LogicTreeBase::SetFinish()
	{
		m_bselfFinish = true;
		m_bChildFinish = true;
		m_ChildActive = false;
	}

	bool LogicTreeBase::LinkInput(int32 i, int32 outLogicIndex, int32 OutputIndex)
	{
		if (i < 0 || i > MAX_LOGIC_IN_OUT_PUT)
		{
			return false;
		}
		m_InputInfo[i].LogicIndex = outLogicIndex;
		m_InputInfo[i].OutputIndex = OutputIndex;
		return true;
	}

	void LogicTreeBase::Free()
	{
		TreeNodeBase* pChild = GetNextChild(NULL);
		while (pChild)
		{
			LogicTreeBase* pLogic = (LogicTreeBase*)pChild;
			pLogic->Free();
			pChild = GetNextChild(pChild);
		}
		//LogicFactory::GetSigleton().Delete(this);
	}

	bool LogicTreeBase::TerminataLogic()
	{
		if (m_pOwnerGroup)
		{
			m_pOwnerGroup->Terminate();
			return true;
		}
		return false;
	}
	void LogicTreeBase::ReActive()
	{
		m_bActive = true;
	}	
}