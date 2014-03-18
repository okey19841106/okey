#include "PreCom.h"
#include "ParamPool.h"

namespace okey
{

	ParamPool::ParamPool():m_InitDataID(-1),m_ParamBuffersize(0),
		m_ParamBuffer(NULL),
		m_owner(NULL),
		m_paramDef(NULL),
		m_ParamBlockCount(0),
		m_bUserBuffer(false),
		PreParamCallFun(NULL),
		PostParamCallFun(NULL)
	{
		for (int32 i = 0; i<PARAM_BLOCK_SIZE; ++i )
		{
			m_ParamBlock[i] = 0;
		}	
	}

	ParamPool::ParamPool(ParamDef* pDef):m_InitDataID(-1),m_ParamBuffersize(0),
		m_ParamBuffer(NULL),
		m_owner(NULL),
		m_ParamBlockCount(0),
		m_bUserBuffer(false),
		PreParamCallFun(NULL),
		PostParamCallFun(NULL)
	{
		SetParamDef(pDef);
		for (int32 i = 0; i<PARAM_BLOCK_SIZE; ++i )
		{
			m_ParamBlock[i] = 0;
		}	
	}

	ParamPool::~ParamPool()
	{
		if (PreParamCallFun)
		{
			delete PreParamCallFun;
			PreParamCallFun = NULL;
		}
		if (PostParamCallFun)
		{
			delete PostParamCallFun;
			PostParamCallFun = NULL;
		}
		if (m_ParamBuffer)
		{
			FreeParamBuffer();
		}
	}

	void ParamPool::SetParamDef(ParamDef* pDef)
	{
		if (!pDef)
		{
			return;
		}
		m_paramDef = pDef;
		m_ParamBuffersize = pDef->GetSize();
		int32 tMax = pDef->GetMaxParamIndex();
		m_ParamBlockCount = tMax/PARAM_COUNT_IN_BLOCK + 1;
	}

	uint32 ParamPool::DirtyCheck(int32 index)
	{
		if (index < 0 || index >PARAM_BLOCK_SIZE)
		{
			return 0;
		}
		return m_ParamBlock[index];
	}

	void ParamPool::ClearDirty(int32 index)
	{
		if (index < 0 || index >PARAM_BLOCK_SIZE)
		{
			return;
		}
		m_ParamBlock[index] = 0;
	}
	bool ParamPool::DirtyCheck()
	{
		for (int32 i = 0; i < PARAM_BLOCK_SIZE; ++i)
		{
			if (DirtyCheck(i))
			{
				return true;
			}
		}
		return false;
	}
	bool ParamPool::ClearDirty()
	{
		for (int32 i = 0; i < PARAM_BLOCK_SIZE; ++i)
		{
			ClearDirty(i);
		}
		return true;
	}
	bool ParamPool::ParamDirtyCheck(int32 index)
	{
		if (index < 0 || index > PARAM_COUNT_IN_POOL)
		{
			return false;
		}
		int32 nBlock = index/PARAM_COUNT_IN_BLOCK;
		int32 nPos = index % PARAM_COUNT_IN_BLOCK;
		return (m_ParamBlock[nBlock] & (0x00000001<<nPos));
	}
	void ParamPool::ClearParamDirty(int32 index)
	{
		if (index < 0 || index > PARAM_COUNT_IN_POOL)
		{
			return;
		}
		int32 nBlock = index/PARAM_COUNT_IN_BLOCK;
		int32 nPos = index % PARAM_COUNT_IN_BLOCK;
		m_ParamBlock[nBlock] &= ~(0x00000001<<nPos);
	}
	void ParamPool::SetParamDirty(int32 index)
	{
		if (index < 0 || index > PARAM_COUNT_IN_POOL)
		{
			return;
		}
		int32 nBlock = index/PARAM_COUNT_IN_BLOCK;
		int32 nPos = index % PARAM_COUNT_IN_BLOCK;
		m_ParamBlock[nBlock] |= (0x00000001<<nPos);
	}
// 	void ParamPool::UpdateTimeGate(int32 delta)
// 	{
// 		int cn = m_paramDef->GetMaxParamIndex();
// 		for (int32 i = 0; i < cn; ++i)
// 		{
// 			ParamBase* pParam = m_paramDef->GetParam(i);
// 			if (pParam && pParam->IsTimeGateParam())
// 			{
// 				pParam->UpdateTimeGate(m_ParamBuffer,delta);
// 			}
// 		}
// 	}

	char* ParamPool::Data2Buffer(char* pBuffer)
	{
		if (!pBuffer || !m_ParamBuffer)
		{
			return NULL;
		}
		memcpy(pBuffer, m_ParamBuffer, m_ParamBuffersize);
		return pBuffer + m_ParamBuffersize;
	}

	char* ParamPool::Buffer2Data(char* pBuffer)
	{
		if (!pBuffer || !m_ParamBuffer)
		{
			return NULL;
		}
		memcpy( m_ParamBuffer, pBuffer, m_ParamBuffersize);
		return pBuffer + m_ParamBuffersize;
	}

	bool ParamPool::AllocParamBuffer()
	{
		if (!m_paramDef)
		{
			return false;
		}
		if (m_ParamBuffer)
		{
			FreeParamBuffer();
		}
		m_ParamBuffer = m_paramDef->MakeBuffer();
		memset(m_ParamBuffer, 0, m_ParamBuffersize);
		m_bUserBuffer = false;
		return true;
	}

	void ParamPool::FreeParamBuffer()
	{
		if (!m_paramDef)
		{
			return;
		}
		if (!m_ParamBuffer || m_bUserBuffer)
		{
			return;
		}
		m_paramDef->FreeBuffer(m_ParamBuffer);
	}

	void ParamPool::SetParamBuffer(char* pBuffer)
	{
		if (!pBuffer)
		{
			return;
		}
		if (m_ParamBuffer)
		{
			FreeParamBuffer();
		}
		m_ParamBuffer = pBuffer;
		m_bUserBuffer = true;
	}

    //±»Ωœ∏¥‘”°£°£°£°£°£°£°£°£
	bool ParamPool::Read(char* pBuffer, bool bDirty )
	{
		if (!pBuffer)
		{
			return false;
		}
		uint8 nCount = (uint8)(*pBuffer);
		char* tmpBuffer = pBuffer + sizeof(uint8);
		for (int32 i = 0 ; i < nCount; ++i )
		{
			ParamStreamInfo *info = (ParamStreamInfo*)tmpBuffer;
			tmpBuffer += ParamStreamInfo::size();
			uint32 tFlag = info->BlockFlag;
			for (int32 j = 0; j < PARAM_COUNT_IN_BLOCK; ++j)
			{
				if (tFlag & (0x00000001 << j))
				{
					int32 cPos = info->BlockIndex*PARAM_COUNT_IN_BLOCK + j;
					ParamBase* pParam = m_paramDef->GetParam(cPos);
					if (!pParam)
					{
						continue;
					}
					if (PreParamCallFun)
					{
						(*PreParamCallFun)(this, pParam->GetIndex());
					}
					tmpBuffer = pParam->ParamRead(m_ParamBuffer,tmpBuffer);
					if (PostParamCallFun)
					{
						(*PostParamCallFun)(this, pParam->GetIndex());
					}
					if (bDirty)
					{
						SetParamDirty(cPos);
					}
				}
			}

		}
		return true;

	}


	bool ParamPool::Write(char* pBuffer, int32& nBufSize, int32& nStartPos, uint32 nFlag, bool bAll, bool bClearDirty)
	{
		if (nBufSize <(int32) (ParamStreamInfo::size() + sizeof(uint8)) || ! pBuffer)
		{
			nBufSize = 0;
			return true;
		}
		if (!bAll && !DirtyCheck())
		{
			nBufSize = 0;
			return true;
		}
		int32 sBlock = nStartPos/PARAM_COUNT_IN_BLOCK;
		if (sBlock > PARAM_BLOCK_SIZE )
		{
			nBufSize = 0;
			return true;
		}
		uint32 curBufferSize = nBufSize;
		nBufSize = 0;
		int32 sPos = nStartPos%PARAM_COUNT_IN_BLOCK;
		uint32 tFlag = 0;
		bool bNull = true;
		bool bBlockNull = true;
		uint8* pCount = (uint8*)pBuffer;
		(*pCount) = 0;
		char* tmpBuffer = pBuffer + sizeof(uint8);
		curBufferSize -= sizeof(uint8);
		nBufSize += sizeof(uint8);
		for (int32 i = sBlock; i < m_ParamBlockCount; ++i)
		{
			bBlockNull = true;
			tFlag = 0;
			if (curBufferSize < ParamStreamInfo::size())
			{
				return false;
			}
			ParamStreamInfo *info = (ParamStreamInfo*)tmpBuffer;
			tmpBuffer += ParamStreamInfo::size();
			curBufferSize -= ParamStreamInfo::size();
			nBufSize += ParamStreamInfo::size();
			for (int32 j = sPos; j < PARAM_COUNT_IN_BLOCK; ++j)
			{
				int32 cPos = i*PARAM_COUNT_IN_BLOCK + j;
				nStartPos = cPos;
				ParamBase* pParam = m_paramDef->GetParam(cPos);
				if (!pParam || !pParam->CheckFlag(nFlag))
				{
					continue;
				}
				if (!bAll && !ParamDirtyCheck(cPos))
				{
					continue;
				}
				if (pParam->GetParamSize() > (int32)curBufferSize)
				{
					if (!bBlockNull)
					{
						++(*pCount);
						info->BlockFlag = tFlag;
						info->BlockIndex = i;
					}
					else
					{
						tmpBuffer += ParamStreamInfo::size();
						curBufferSize -= ParamStreamInfo::size();
						nBufSize += ParamStreamInfo::size();
						return false;
						
					}
				}
				tFlag |= (0x00000001 << j);
				tmpBuffer = pParam->ParamWirte(m_ParamBuffer, tmpBuffer);
				if (bClearDirty)
				{
					ClearParamDirty(cPos);
				}
				curBufferSize -= pParam->GetParamSize();
				nBufSize += pParam->GetParamSize();
				bNull = false;
				bBlockNull = false;
			}
			if (!bBlockNull)
			{
				++(*pCount);
				info->BlockFlag = tFlag;
				info->BlockIndex = i;
			}
			else
			{
				tmpBuffer += ParamStreamInfo::size();
				curBufferSize -= ParamStreamInfo::size();
				nBufSize += ParamStreamInfo::size();
				if (curBufferSize < ParamStreamInfo::size())
				{
					return false;
				}
			}
		}
		if (bNull)
		{
			nStartPos = -1;
			nBufSize = 0;
			return true;
		}
		return true;
	}

	void ParamPool::PrintTheParam()
	{
		if (!m_paramDef)
		{
			printf("ParamDef is null...\n");
		}
		//int32 defs = 
		for (int32 i = 0; i <= m_paramDef->GetMaxParamIndex(); ++i)
		{
			ParamBase* pParamBase = m_paramDef->GetParam(i);
			if (!pParamBase)
			{
				continue;
			}
			if (pParamBase->TypeCheck(typeid(uint8)))
			{
				Param<uint8>* pParam = (Param<uint8>*)pParamBase;
				printf("%d\t%s\t%d\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(int8)))
			{
				Param<int8>* pParam = (Param<int8>*)pParamBase;
				printf("%d\t%s\t%d\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(uint16)))
			{
				Param<uint16>* pParam = (Param<uint16>*)pParamBase;
				printf("%d\t%s\t%d\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(int16)))
			{
				Param<int16>* pParam = (Param<int16>*)pParamBase;
				printf("%d\t%s\t%d\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(uint32)))
			{
				Param<uint32>* pParam = (Param<uint32>*)pParamBase;
				printf("%d\t%s\t%u\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(int32)))
			{
				Param<int32>* pParam = (Param<int32>*)pParamBase;
				printf("%d\t%s\t%d\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(uint64)))
			{
				Param<uint64>* pParam = (Param<uint64>*)pParamBase;
				printf("%d\t%s\t%llu\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(int64)))
			{
				Param<int64>* pParam = (Param<int64>*)pParamBase;
				printf("%d\t%s\t%lld\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(f32)))
			{
				Param<f32>* pParam = (Param<f32>*)pParamBase;
				printf("%d\t%s\t%f\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(f64)))
			{
				Param<f64>* pParam = (Param<f64>*)pParamBase;
				printf("%d\t%s\t%lf\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValue(m_ParamBuffer));
			}
			else if (pParamBase->TypeCheck(typeid(char*)))
			{
				ParamStr* pParam = (ParamStr*)pParamBase;
				printf("%d\t%s\t%s\n",pParam->GetIndex(), pParam->GetName(), pParam->GetValueString(m_ParamBuffer));
			}
		}
	}
}