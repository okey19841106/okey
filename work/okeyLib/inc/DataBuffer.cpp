#include "PreCom.h"
#include "DataBuffer.h"
#include <cassert>

namespace okey
{

	DataBufferEx::DataBufferEx(int32 size)
	{
		assert(size > 0);
		m_buffer = (char*)::malloc(size);
		memset(m_buffer, 0 , size);
	}

	DataBufferEx::~DataBufferEx()
	{
		if (m_buffer)
		{
			::free(m_buffer);
			m_buffer = NULL;
		}
	}

	DataGroup::DataGroup():m_size(0)
	{
		for (int32 i = 0; i < MAX_DATA_LIST; ++i)
		{
			m_datalist[i] = NULL;
		}
	}

	DataGroup::~DataGroup()
	{
		for (int32 i = 0; i < MAX_DATA_LIST; ++i)
		{
			if (m_datalist[i])
			{
				delete m_datalist[i];
				m_datalist[i] = NULL;
			}
		}
	}

	bool DataGroup::Init(int32 size)
	{
		if (size <= 16)
		{
			m_size = 16;
		}
		else if (size <= 32)
		{
			m_size = 32;
		}
		else if (size <= 64)
		{
			m_size = 64;
		}
		else if (size <= 128)
		{
			m_size = 128;
		}
		else if (size <= 256)
		{
			m_size = 256;
		}
		else if (size <= 512)
		{
			m_size = 512;
		}
		else if (size <= 1024)
		{
			m_size = 1024;
		}
		else if (size <= 2048)
		{
			m_size = 2048;
		}
		else 
		{
			return false;
		}
		return true;

	}

	bool DataGroup::CreateDataBuffer(int32 dataID)
	{
		if (dataID < 0 || dataID >= MAX_DATA_LIST || m_datalist[dataID])
		{
			return false;
		}
		DataBufferBase * pData = NULL;
		int32 nCreateSize = ((m_size>>4)+1)<<4;
		pData = new DataBufferEx(nCreateSize);
		if (!pData)
		{
			return false;
		}
		m_datalist[dataID] = pData;
		return true;
	}

	DataBufferBase* DataGroup::GetDataBuffer(int32 dataID)
	{
		if (dataID < 0 || dataID >= MAX_DATA_LIST || !m_datalist[dataID])
		{
			return NULL;
		}
		return m_datalist[dataID];
	}

	bool DataGroup::AddDataBuffer(int32 dataID, char* pBuffer, int32 nSize)
	{
		if (dataID < 0 || dataID >= MAX_DATA_LIST || !m_datalist[dataID] || !pBuffer)
		{
			return false;
		}
		int32 nRealSize = ((nSize > m_size) ? m_size:nSize);
		memcpy(m_datalist[dataID]->GetBuffer(), pBuffer, nRealSize);
		return true;
	}

	DataBufferBase* DataManager::GetDataBuffer(int32 dataGroupID, int32 dataID)
	{
		if (dataGroupID < 0 || dataGroupID >= DATA_GROUP_MAX || dataID < 0 || dataID >= MAX_DATA_LIST)
		{
			return NULL;
		}
		if (!m_datagrouplist[dataGroupID])
		{
			return NULL;
		}
		return m_datagrouplist[dataGroupID]->GetDataBuffer(dataID);
	}
	DataManager::DataManager()
	{
		for (int32 i = 0; i < DATA_GROUP_MAX; ++i)
		{
			m_datagrouplist[i] = NULL;
		}
	}
	DataManager::~DataManager()
	{

	}

}