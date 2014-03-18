#include "PreCom.h"
#include "ParamDef.h"
#include "Allocator.h"
#include "ParamBase.h"

namespace okey
{
	ParamDef::ParamDef()
	{
		m_poolsize = 0 ;
		m_cid = 0;
		m_maxindex = 0;
		m_count = 0;
		m_palloc = NULL;
	}

	bool ParamDef::AddParam(ParamBase* pParam)
	{
		if (!pParam || !pParam->GetName())
		{
			return false;
		}
		int32 tIndex = pParam->GetIndex();
		if (GetParam(pParam->GetName()))
		{
			return false;
		}
		if (!m_plist.Add(tIndex,pParam))
		{
			return false;
		}
		m_pmap[pParam->GetName()] = pParam;
		if (tIndex > m_maxindex)
		{
			m_maxindex = tIndex;
		}
		++m_count;
		m_poolsize += pParam->GetParamSize();
// 		if (pParam->IsTimeGateParam())
// 		{
// 			 m_poolsize += sizeof(int32);
// 		}
		return true;

	}

	ParamBase* ParamDef::GetParam(int32 index)
	{
		return m_plist.Get(index);
	}

	ParamBase* ParamDef::GetParam(const char* name)
	{
		ParamMap::iterator itr = m_pmap.find(name);
		if (itr == m_pmap.end())
		{
			return NULL;
		}
		return itr->second;
	}

	bool ParamDef::SetBufferAlloc(Allocator* pAlloc)
	{
		if (!pAlloc)
		{
			return false;
		}
		m_palloc = pAlloc;
		m_palloc->Init(m_poolsize);
		MemoryHead mh;
		mh.AllocInfo = m_cid;
		mh.MemInfo = 0;
		m_palloc->SetMemoryInfo(mh);
		return true;
	}

	char* ParamDef::MakeBuffer()
	{
		return (char*)m_palloc->DLMalloc(m_poolsize);
	}

	void ParamDef::FreeBuffer(char* ptr)
	{
		if (!ptr)
		{
			return;
		}
		m_palloc->DLFree(ptr);
	}
}