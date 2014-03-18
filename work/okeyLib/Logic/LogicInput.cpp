#include "PreCom.h"
#include "LogicInput.h"
#include "LogicTreeBase.h"
#include "LogicOutput.h"
#include "LogicGroup.h"

namespace okey
{
	LogicInput::LogicInput():m_type(-1),
	m_index(-1),
	m_offset(0),
	m_size(0)
	{

	}
	LogicInput::~LogicInput()
	{

	}

	bool LogicInput_Int::Update(LogicTreeBase* pInlogic,
		LogicTreeBase* pOutLogic,	int32 nLinkedOutIndex)
	{
		if (!pInlogic || !pOutLogic || nLinkedOutIndex > MAX_LOGIC_IN_OUT_PUT ||
			nLinkedOutIndex < 0)
		{
			return false;
		}
		*((int32*)((char*)pInlogic + m_offset)) = pOutLogic->GetOutputInt(nLinkedOutIndex);
		return true;
	}

	bool LogicInput_Float::Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
	int32 nLinkedOutIndex)
	{
		if (!pInlogic || !pOutLogic || nLinkedOutIndex > MAX_LOGIC_IN_OUT_PUT ||
			nLinkedOutIndex < 0)
		{
			return false;
		}
		*((float*)((char*)pInlogic + m_offset)) = pOutLogic->GetOutputFloat(nLinkedOutIndex);
		return true;
	}

	bool LogicInput_Char::Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
	int32 nLinkedOutIndex)
	{
		if (!pInlogic || !pOutLogic || nLinkedOutIndex > MAX_LOGIC_IN_OUT_PUT ||
			nLinkedOutIndex < 0)
		{
			return false;
		}
		LogicOutput* pOutput = pOutLogic->GetOutput(nLinkedOutIndex);
		if (!pOutput)
		{
			return false;
		}
		int32 tsize = (m_size < pOutput->GetSize())?m_size:pOutput->GetSize();
		memcpy((char*)pInlogic + m_offset, (char*)pOutLogic + pOutput->GetOffset(), tsize);
		return true;
	}

	bool LogicInput_Ptr::Update(LogicTreeBase* pInlogic, LogicTreeBase* pOutLogic, 
	int32 nLinkedOutIndex)
	{
		if (!pInlogic || !pOutLogic || nLinkedOutIndex > MAX_LOGIC_IN_OUT_PUT ||
			nLinkedOutIndex < 0)
		{
			return false;
		}
		LogicOutput* pOutput = pOutLogic->GetOutput(nLinkedOutIndex);
		if (!pOutput)
		{
			return false;
		}
		memcpy((char*)pInlogic + m_offset, (char*)pOutLogic + pOutput->GetOffset(), sizeof(void*));
		return true;
	}

	LogicInputManager::LogicInputManager(){}

	LogicInputManager::~LogicInputManager(){}

	LogicInput* LogicInputManager::GetInput(int32 index)
	{
		if (index < 0 || index > MAX_LOGIC_IN_OUT_PUT)
		{
			return NULL;
		}
		return m_inputList[index];
	}
	
	bool LogicInputManager::Update(LogicTreeBase* pLogic)
	{
		if (!pLogic)
		{
			return false;
		}
		LogicGroup* pGroup = pLogic->GetLogicGroup();
		if (!pGroup)
		{
			return false;
		}
		for (int32 i = 0; i< MAX_LOGIC_IN_OUT_PUT; ++i)
		{
			if (!m_inputList[i])
			{
				continue;
			}
			LogicTreeBase* pOutputLogic = pGroup->GetLogic(pLogic->m_InputInfo[i].LogicIndex);
			if (!pOutputLogic)
			{
				continue;
			}
			m_inputList[i]->Update(pLogic, pOutputLogic, pLogic->m_InputInfo[i].OutputIndex);
		}
		return true;
	}

	void LogicInputManager::Clear()
	{
		m_inputCount = 0;
		for (int32 i = 0; i < MAX_LOGIC_IN_OUT_PUT ; ++i)
		{
			m_inputList[i] = NULL;
		}
	}
	bool LogicInputManager::AddInput(LogicInput* pInput)
	{
		if (!pInput)
		{
			return false;
		}
		for (int32 i = 0; i < MAX_LOGIC_IN_OUT_PUT; ++i)
		{
			if (m_inputList[i] == NULL)
			{
				m_inputList[i] = pInput;
				pInput->SetIndex(i);
				++m_inputCount;
				return true;
			}
		}
		return false;
	}
}