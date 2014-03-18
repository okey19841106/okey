#include "PreCom.h"
#include "ParamDataManager.h"
#include "ParamDefManager.h"
#include "ParamPool.h"
#include "File/cfgloader.h"
#include <sstream>

namespace okey
{
	ParamDataManager::ParamDataManager(ParamDefManager* pDef):m_pDefManager(pDef)
	{
	}

	ParamDataManager::~ParamDataManager()
	{
	}

	bool ParamDataManager::InitParamPool(ParamPool* pPool, int32 dataID)
	{
		if(!pPool || !pPool->GetParamDef())
			return false;
		int32 index = pPool->GetParamDef()->GetID();
		DataBufferBase* pData = GetDataBuffer(index, dataID);
		if(!pData)
			return false;
		if(!pPool->Buffer2Data(pData->GetBuffer()))
			return false;
		pPool->SetDataID(dataID);
		return true;
	}

	bool ParamDataManager::Load(const char* sFile, CfgLoaderBase* pLoader)
	{
		if (!sFile || !pLoader || !m_pDefManager)
		{
			return false;
		}
		for (int32 i = 0; i < m_pDefManager->GetMaxIndex() + 1; ++i)
		{
			std::stringstream str;
			str<<sFile<<i<<".dbf";
			if (!pLoader->Load(str.str().c_str()))
			{
				printf("Load %s files\n",sFile);
				return false;
			}
			LabelVector tLabel;
			if(!pLoader->GetLabel(tLabel))
			{
				printf("Empty file...\n",sFile);
				return false;
			}
			ParamDef* pDef = m_pDefManager->GetParamDef(i);
			if (!pDef)
			{
				continue;
			}
			int32 lsize = pDef->GetSize();
			m_datagrouplist[i] = new DataGroup();
			m_datagrouplist[i]->Init(lsize);
			//CreateDataBuffer()
			ParamPool tPool;
			tPool.SetParamDef(pDef);
			tPool.AllocParamBuffer();
			for(int32 j = 0; j < pLoader->GetLineCount(); ++j)
			{
				ValueVector tmpValue;
				if(!pLoader->GetValueList(j,tmpValue))
				{
					continue;
				}
				int32 index = -1;
				bool bFirstIndex = true;
				for(int32 k = 0; k < pLoader->GetColCount();++k)
				{
					std::string sVal;
					if ((int32)tmpValue.size() < k)
					{
						sVal = "0";
					}
					else
					{
						sVal = tmpValue[k];
					}
					if (tLabel[k] == "ID" || tLabel[k] == "id")
					{
						index = atoi(sVal.c_str());
						bFirstIndex = false;
					}
					else
					{
						ParamBase* pParam = pDef->GetParam(k);
						if (!pParam || tLabel[k] != pParam->GetName() )
						{
							continue;
						}
						if (pParam->TypeCheck(typeid(uint8)))
						{
							uint8 u8Value = (uint8)atoi(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(), u8Value, false );
						}
						else if (pParam->TypeCheck(typeid(int8)))
						{
							int8 i8Value = (int8)atoi(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),i8Value,false );
						}
						else if (pParam->TypeCheck(typeid(uint16)))
						{
							uint16 u16Value = (uint16)atoi(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),u16Value,false );
						}
						else if (pParam->TypeCheck(typeid(int16)))
						{
							int16 i16Value = (int16)atoi(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),i16Value,false );
						}
						else if (pParam->TypeCheck(typeid(uint32)))
						{
							uint32 u32Value = (uint32)atoul(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),u32Value,false );
						}
						else if (pParam->TypeCheck(typeid(int32)))
						{
							int32 i32Value = (int32)atoi(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),i32Value,false );
						}
						else if (pParam->TypeCheck(typeid(uint64)))
						{
							uint64 u64Value = (uint64)atoull(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),u64Value,false );
						}
						else if (pParam->TypeCheck(typeid(int64)))
						{
							int64 i64Value = (int64)atoll(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),i64Value,false );
						}
						else if (pParam->TypeCheck(typeid(f32)))
						{
							f32 f32Value = (f32)atof(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),f32Value,false );
						}
						else if (pParam->TypeCheck(typeid(f64)))
						{
							f64 f64Value = (f64)atof(sVal.c_str());
							tPool.SetValue(tLabel[k].c_str(),f64Value,false );
						}
						else if (pParam->TypeCheck(typeid(char*)))
						{
							tPool.SetStringValue(tLabel[k].c_str(),sVal.c_str(),false);
						}
					}
					
				}
				if (index == -1)
				{
					m_datagrouplist[i]->CreateDataBuffer(j);
					m_datagrouplist[i]->AddDataBuffer(j, tPool.GetParamBuffer(), tPool.GetParamBufferSize());
				}
				else
				{
					m_datagrouplist[i]->CreateDataBuffer(index);
					m_datagrouplist[i]->AddDataBuffer(index, tPool.GetParamBuffer(), tPool.GetParamBufferSize());
				}
				
			}
		}
		return true;
	}
}