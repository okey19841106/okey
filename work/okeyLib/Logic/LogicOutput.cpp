#include "PreCom.h"
#include "LogicOutput.h"
#include "LogicTreeBase.h"

namespace okey
{
	LogicOutput::LogicOutput():m_type(-1),
		m_index(-1),
		m_offset(0),
		m_size(0)
	{

	}
	LogicOutput::~LogicOutput()
	{

	}

	int32 LogicOutput_Int::GetValue(LogicTreeBase* pLogic, int32 dev) 
	{
		if (!pLogic)
		{
			return dev;
		}
		return *((int32*)((char*)pLogic + m_offset));
	}
	float LogicOutput_Float::GetValue(LogicTreeBase* pLogic, float dev)
	{
		if (!pLogic)
		{
			return dev;
		}
		return *((float*)((char*)pLogic + m_offset));
	}
	char* LogicOutput_Char::GetValue(LogicTreeBase* pLogic, char* dev)
	{
		if (!pLogic)
		{
			return dev;
		}
		return (char*)pLogic + m_offset;
	}

	void* LogicOutput_Ptr::GetValue(LogicTreeBase* pLogic, void* dev)
	{
		{
			if (!pLogic)
			{
				return dev;
			}
			return (void*)((char*)pLogic + m_offset);
		}
	}
	LogicOutputManager::LogicOutputManager(){}

	LogicOutputManager::~LogicOutputManager(){}

	LogicOutput* LogicOutputManager::GetOutput(int32 index)
	{
		if (index < 0 || index > MAX_LOGIC_IN_OUT_PUT)
		{
			return NULL;
		}
		return m_outputList[index];
	}
	void LogicOutputManager::Clear()
	{
		m_outputCount = 0;
		for (int32 i = 0; i < MAX_LOGIC_IN_OUT_PUT ; ++i)
		{
			m_outputList[i] = NULL;
		}
	}
	bool LogicOutputManager::AddOutput(LogicOutput* pOut)
	{
		if (!pOut)
		{
			return false;
		}
		for (int32 i = 0; i < MAX_LOGIC_IN_OUT_PUT; ++i)
		{
			if (m_outputList[i] == NULL)
			{
				m_outputList[i] = pOut;
				pOut->SetIndex(i);
				++m_outputCount;
				return true;
			}
		}
		return false;
	}

	int32 LogicOutputManager::GetValue(int32 index,LogicTreeBase* pLogic, int32 dev)
	{
		LogicOutput* pLogicop = GetOutput(index);
		if (!pLogic || !pLogicop)
		{
			return dev;
		}
		return pLogicop->GetValue(pLogic,dev);
	}
	float LogicOutputManager::GetValue(int32 index,LogicTreeBase* pLogic, float dev)
	{
		LogicOutput* pLogicop = GetOutput(index);
		if (!pLogic || !pLogicop)
		{
			return dev;
		}
		return pLogicop->GetValue(pLogic,dev);
	}
	char* LogicOutputManager::GetValue(int32 index,LogicTreeBase* pLogic, char* dev)
	{
		LogicOutput* pLogicop = GetOutput(index);
		if (!pLogic || !pLogicop)
		{
			return dev;
		}
		return pLogicop->GetValue(pLogic,dev);
	}
	void* LogicOutputManager::GetValue(int32 index,LogicTreeBase* pLogic, void* dev)
	{
		LogicOutput* pLogicop = GetOutput(index);
		if (!pLogic || !pLogicop)
		{
			return dev;
		}
		return pLogicop->GetValue(pLogic,dev);
	}

}