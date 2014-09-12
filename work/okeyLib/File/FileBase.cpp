#include "PreCom.h"
#include "FileBase.h"


namespace okey
{
	bool FileBase::Close()
	{
		if (m_pFile)
		{
			fclose(m_pFile);
			m_pFile = NULL;
		}
		return true;
	}

	bool FileBase::IsFileExist(const std::string& sName)
	{
		FILE* f = fopen(sName.c_str(), "rb");
		if(f)  // The file exists.
		{
			fclose(f);
			return true;
		}
		return false;
	}
}