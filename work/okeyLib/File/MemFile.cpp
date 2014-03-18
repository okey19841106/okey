#include "PreCom.h"
#include "MemFile.h"
#include "Fuction.h"


namespace okey
{
	MemFile::MemFile():m_pMem(NULL),m_startMem(NULL),m_pEndMem(NULL),m_DeCodeFun(NULL)
	{

	}

	MemFile::~MemFile()
	{

	}

	bool MemFile::Open(const char* filename)
	{
		if (!filename)
		{
			return false;
		}
		FILE* m_pFile = fopen(filename, "rb");
		if(NULL == m_pFile) return FALSE;

		fseek(m_pFile, 0, SEEK_END);
		int32 nFileSize = ftell(m_pFile);
		fseek(m_pFile, 0, SEEK_SET);

		//¶ÁÈëÄÚ´æ
		m_startMem = new char[nFileSize+1];
		fread(m_startMem, 1, nFileSize, m_pFile);
		m_startMem[nFileSize] = 0;
		if (m_DeCodeFun)
		{
			char* ret = NULL;
			int32 retcount;
			(*m_DeCodeFun)(m_startMem, nFileSize, ret, retcount);
			delete []m_startMem;
			if ( ret== NULL || retcount == 0 )
			{
				m_startMem = NULL;
				return false;
			}
			m_startMem = ret;
			m_pMem = ret;
			m_pEndMem = m_startMem + retcount + 1;
		}
		else
		{
			m_pMem = m_startMem;
			m_pEndMem = m_startMem +nFileSize+1;
		}
		return true;
	}

	bool MemFile::ReadLine(char* buffer, int32 len)
	{
		if (buffer == NULL || m_pMem == NULL)
		{
			return false;
		}
		if (m_pMem == m_startMem)
		{
			m_pMem = (char*)GetNextLine(buffer, len, NULL);
		}
		else
		{
			m_pMem = (char*)GetNextLine(buffer,len,m_pMem);
		}
		return true;
	}

	bool MemFile::IsEnd()
	{
		return m_startMem == m_pEndMem;
	}


	bool MemFile::Close()
	{
		fclose(m_pFile);
		if (m_startMem)
		{
			delete []m_startMem;
			m_startMem = 0;
		}
		return true;
	}

	const char* MemFile::GetNextLine(char* pStringBuf, int32 nBufSize, const char* pMemory)
	{
		const char* pMem = NULL;
		if (!pMemory)
		{
			pMem = m_startMem;
		}
		else
		{
			pMem = pMemory;
		}
		if(pMem >= m_pEndMem || *pMem==0) return NULL;

		while(pMem < m_pEndMem && pMem-pMemory+1<nBufSize && 
			*pMem != 0 && *pMem != '\r' && *pMem != '\n') *(pStringBuf++) = *(pMem++);
		//add 'null' end
		*pStringBuf = 0;
		//skip all next \r and \n
		while(pMem < m_pEndMem && *pMem != 0 && (*pMem=='\r' || *pMem=='\n')) pMem++;
		return pMem;
	}
}