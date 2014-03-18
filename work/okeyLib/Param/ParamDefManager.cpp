#include "PreCom.h"
#include "ParamDefManager.h"
#include "PoolAllocator.h"
#include "XML.h"
#include "ParamBase.h"

namespace okey
{

	bool ParamDefManager::Load(const char* path)
	{
		if (!path)
		{
			return false;
		}
		XmlDocument doc;
		if(!doc.LoadFile(path))
		{
			printf("load paramdef Error:%s\n",doc.ErrorDesc());
			return false;
		}
		XmlElement* pRoot = doc.RootElement();
		if (!pRoot)
		{
			return false;
		}
		XmlElement* pParamBaseEl = pRoot->FirstChildElement("dynamicparam");
		while(pParamBaseEl)
		{
			ParamDef* pDef = new ParamDef;
			if (!pDef)
			{
				return false;
			}
			pDef->SetName(pParamBaseEl->Attribute("name"));
			int32 tId;
			pParamBaseEl->Attribute("id",&tId);
			pDef->SetID(tId);
			XmlElement* pParamElement = pParamBaseEl->FirstChildElement("param");
			int32 offset = 0;
			while(pParamElement)
			{
				std::string type = pParamElement->Attribute("type");
				std::string paramname = pParamElement->Attribute("name");
				int32 nID;
				int32 nflag;
				std::string tMax = pParamElement->Attribute("max");
				std::string tMin = pParamElement->Attribute("min");
				pParamElement->Attribute("id",&nID);
				pParamElement->Attribute("flag",&nflag);
				ParamBase *pParamBase = NULL;
				if (type == "uint8")
				{
					pParamBase = new Param<uint8>();
					((Param<uint8>*)pParamBase)->SetMaxValue((uint8)atoi(tMax.c_str()));
					((Param<uint8>*)pParamBase)->SetMinValue((uint8)atoi(tMin.c_str()));
				}
				else if (type == "int8")
				{
					pParamBase = new Param<int8>();
					((Param<int8>*)pParamBase)->SetMaxValue((int8)atoi(tMax.c_str()));
					((Param<int8>*)pParamBase)->SetMinValue((int8)atoi(tMin.c_str()));
				}
				else if (type == "uint16")
				{
					pParamBase = new Param<uint16>();
					((Param<uint16>*)pParamBase)->SetMaxValue((uint16)atoi(tMax.c_str()));
					((Param<uint16>*)pParamBase)->SetMinValue((uint16)atoi(tMin.c_str()));
				}
				else if (type == "int16")
				{
					pParamBase = new Param<int16>();
					((Param<int16>*)pParamBase)->SetMaxValue((int16)atoi(tMax.c_str()));
					((Param<int16>*)pParamBase)->SetMinValue((int16)atoi(tMin.c_str()));
				}
				else if (type == "uint32")
				{
					pParamBase = new Param<uint32>();
					((Param<uint32>*)pParamBase)->SetMaxValue((uint32)atoul(tMax.c_str()));
					((Param<uint32>*)pParamBase)->SetMinValue((uint32)atoul(tMin.c_str()));
				}
				else if (type == "int32")
				{
					pParamBase = new Param<int32>();
					((Param<int32>*)pParamBase)->SetMaxValue((int32)atoi(tMax.c_str()));
					((Param<int32>*)pParamBase)->SetMinValue((int32)atoi(tMin.c_str()));
				}
				else if (type == "uint64")
				{
					pParamBase = new Param<uint64>();
					((Param<uint64>*)pParamBase)->SetMaxValue((uint64)atoull(tMax.c_str()));
					((Param<uint64>*)pParamBase)->SetMinValue((uint64)atoull(tMin.c_str()));
				}
				else if (type == "int64")
				{
					pParamBase = new Param<int64>();
					((Param<int64>*)pParamBase)->SetMaxValue((int64)atoll(tMax.c_str()));
					((Param<int64>*)pParamBase)->SetMinValue((int64)atoll(tMin.c_str()));
				}
				else if (type == "f32")
				{
					pParamBase = new Param<f32>();
					((Param<f32>*)pParamBase)->SetMaxValue((f32)atol(tMax.c_str()));
					((Param<f32>*)pParamBase)->SetMinValue((f32)atol(tMin.c_str()));
				}
				else if (type == "f64")
				{
					pParamBase = new Param<f64>();
					((Param<f64>*)pParamBase)->SetMaxValue((f64)atol(tMax.c_str()));
					((Param<f64>*)pParamBase)->SetMinValue((f64)atol(tMin.c_str()));
				}
				else if (type == "char8")
				{
					pParamBase = new ParamStr(8);
				}
				else if (type == "char16")
				{
					pParamBase = new ParamStr(16);
				}
				else if (type == "char32")
				{
					pParamBase = new ParamStr(32);
				}
				else if (type == "char64")
				{
					pParamBase = new ParamStr(64);
				}
				else if (type == "char128")
				{
					pParamBase = new ParamStr(128);
				}
// 				else if (type == "char256")最长就128个。
// 				{
// 					pParamBase = new ParamStr(256);
// 				}
				if (pParamBase)
				{
					pParamBase->SetName(paramname.c_str());
					pParamBase->SetID(tId);
					pParamBase->SetIndex(nID);
					pParamBase->SetFlag(nflag);
					pParamBase->SetOffset(offset);
					offset += pParamBase->GetParamSize();
					pDef->AddParam(pParamBase);
				}
				pParamElement = pParamElement->NextSiblingElement("param");
			}
			AddObj<Mutex>(pDef);
			pParamBaseEl = pParamBaseEl->NextSiblingElement("dynamicparam");
		}
		XmlElement* pParamStatic = pRoot->FirstChildElement("staticparam");
		while(pParamBaseEl)
		{
			XmlElement* pParamElement = pParamBaseEl->FirstChildElement("param");
			while(pParamElement)
			{
				pParamElement = pParamElement->NextSiblingElement("param");
			}
			pParamStatic = pParamBaseEl->NextSiblingElement("staticparam");
		}
		return true;
	}
// 	bool ParamDefManager::AddObj(ParamDef* obj)
// 	{
// 		if (!obj || !obj->GetName())
// 		{
// 			return false;
// 		}
// 		int32 tindex = obj->GetIndex();
// 		if (GetObj(obj->GetName()))
// 		{
// 			return false;
// 		}
// 		m_Tmap[obj->GetName()] = obj;
// 		if (!m_DefList.Add(tindex,obj))
// 		{
// 			return false;
// 		}
// 		if (tindex > m_maxindex)
// 		{
// 			m_maxindex = tindex;
// 		}
// 		++m_count;
// 		if (!obj->GetBufferAlloc())
// 		{
// 			obj->SetBufferAlloc(new PoolAllocator<NoLock>());
// 		}
// 		return true;
// 	}
	ParamDef* ParamDefManager::GetParamDef(uint32 index)
	{
		return m_DefList.Get(index);
	}

}