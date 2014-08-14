#include "PreCom.h"
#include "AnyTypeBase.h"


namespace okey
{

	TTypeBase::TTypeBase()
	{
		m_size = 0;
		m_flag = 0;
	}
	TTypeBase::~TTypeBase()
	{

	}

	char* TTypeBase::Read(void* pClassObj,char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		memcpy(pClassObj, pBuffer, m_size);
		return pBuffer + m_size;
	}

	char* TTypeBase::Write(void* pClassObj, char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		memcpy(pBuffer, pClassObj, m_size);
		return pBuffer + m_size;
	}

	char* TAnyTypeArray::Read(void* pClassObj,char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		//assert(m_pArray)
		char* pObj = (char*)pClassObj;
		for (uint32 i = 0; i < nElem; ++i)
		{
			pBuffer = m_pArray[i].Read(pObj,pBuffer);
		}
		return pBuffer;
	}

	char* TAnyTypeArray::Write(void* pClassObj, char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		//assert(m_pArray)
		char* pObj = (char*)pClassObj;
		for (uint32 i = 0; i < nElem; ++i)
		{
			pBuffer = m_pArray[i].Write(pObj,pBuffer);
		}
		return pBuffer;
	}




}




