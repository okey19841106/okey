/********************************************************************
	created:	2013/06/16
	created:	16-6-2013   20:49
	author:		okey
	
	purpose:	
*********************************************************************/
#include "PreCom.h"
#include "NormalFile.h"


namespace okey
{
	NormalFile::NormalFile()
	{

	}

	NormalFile::~NormalFile()
	{

	}

	bool NormalFile::Open(const char* filename)
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

	bool NormalFile::ReadLine(char* buffer, int32 len)
	{
		if (!buffer || IsEnd())
		{
			return false;
		}
		fgets(buffer, len, m_pFile);
	/*	isFirst = false;*/
		return true;
	}

	bool NormalFile::IsEnd()
	{
		if(feof(m_pFile))
			return true;
		else
			return false;
	}

	bool NormalFile::Close()
	{
		fclose(m_pFile);
		return true;
	}
}