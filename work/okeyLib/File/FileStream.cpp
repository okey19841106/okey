
#include "PreCom.h"
#include "FFile.h"


namespace okey
{
	FFile::FFile()
	{

	}

	FFile::~FFile()
	{

	}

	bool FFile::Open(const char* filename)
	{
		if (!filename)
		{
			return false;
		}
		m_pFile = fopen(filename, "rb");
		if (m_pFile)
		{
			/*isFirst = true;*/
			return true;
		}
		return false;
	}

	bool FFile::ReadLine(char* buffer, int32 len)
	{
		if (!buffer || IsEnd())
		{
			return false;
		}
		fgets(buffer, len, m_pFile);
	/*	isFirst = false;*/
		return true;
	}

	bool FFile::IsEnd()
	{
		if(feof(m_pFile))
			return true;
		else
			return false;
	}

	bool FFile::Close()
	{
		fclose(m_pFile);
		return true;
	}
}