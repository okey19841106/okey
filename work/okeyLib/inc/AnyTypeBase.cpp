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
			pBuffer = m_pArray->Read(pObj,pBuffer);
			pObj += m_pArray->GetSize();
		}
		return pBuffer;
	}

	char* TAnyTypeArray::Write(void* pClassObj, char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		//assert(m_pArray)
		char* pObj = (char*)pClassObj;
		for (uint32 i = 0; i < nElem; ++i)
		{
			pBuffer = m_pArray->Write(pObj,pBuffer);
			pObj += m_pArray->GetSize();
		}
		return pBuffer;
	}

	TAnyTypeStr::TAnyTypeStr(uint32 nCount)
	{
		m_size = nCount + sizeof(uint16);
		m_CharSize = nCount;
		m_typeinfo = TYPE_STR;
	}

	char* TAnyTypeStr::Read(void* pClassObj,char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		int32 len = *((uint16*)pBuffer);
		char* tmpBuf = pBuffer + sizeof(uint16);
		len = len > m_CharSize ? m_CharSize:len;
		memset((char*)pClassObj,0,m_CharSize);
		memcpy(pClassObj,tmpBuf,len);
		return tmpBuf + len;
	}

	char* TAnyTypeStr::Write(void* pClassObj, char* pBuffer)
	{
		if (!pClassObj || !pBuffer)
		{
			return NULL;
		}
		*(uint16*)pBuffer = m_CharSize;
		char* tmpBuf = pBuffer + sizeof(uint16);
		memcpy(tmpBuf,pClassObj,m_CharSize);
		return tmpBuf + m_CharSize;
	}
}




