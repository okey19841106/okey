#include "PreCom.h"
#include "FileIni.h"
#include "File.h"

namespace okey
{
#define WARNING_INI_FILE_SIZE	8192
	FileINI::FileINI()
	{

	}

	FileINI::FileINI(const std::string& filename)
	{
		Open(filename);
	}

	FileINI::~FileINI()
	{

	}

	bool FileINI::Open(const std::string& filename)
	{
		if(!File::IsFileExist(filename))
			return false;
		m_Filename = filename;
		try
		{
			File file(filename, File::acRead);
			BinString vs;
			file.FillAllBuffer(vs);
			Parse(vs);
			//assert(Parse(vs));
		}
		catch (...)
		{
			//assert(false);
			return false;
		}
		return true;
	}

	bool FileINI::Parse(BinString& buf)
	{
		ValueList mpKey;
		std::string section;

		while (true) 
		{
			std::string line = GetLine(buf);
		}
// 			if (line.empty() || IsComment(line))
// 			{
// 				if (IsOffsetEnd()) 
// 				{
// 					break;
// 				} 
// 				else 
// 				{
// 					continue;
// 				}
// 
// 			}
// 
// 			if (IsSection(line)) 
// 			{
// 				if (section.empty()) 
// 				{
// 					section = GetSectionNameFromLine(line);
// 					continue;
// 				} 
// 
// 				m_mpValue.insert(std::make_pair(section, mpKey));
// 				section = GetSectionNameFromLine(line);
// 				mpKey.clear();
// 			} 
// 			else 
// 			{
// 				if (section.empty()) 
// 				{
// 					continue;
// 				}
// 				std::string strKey = GetKeyNameFromLine(line);
// 				if (!strKey.empty()) 
// 				{
// 					mpKey.insert(std::make_pair(strKey, GetKeyValueFromLine(line)));
// 				}
// 			}
// 		}
// 
// 		if (!section.empty()) 
// 		{
// 			m_mpValue.insert(std::make_pair(section, mpKey));
// 		}

		return true;
	}

	std::string FileINI::GetLine(BinString& buf)
	{
 		if(buf.size() == 0)
 			return std::string();
		std::string line;
		BinString::iterator itr = buf.begin();
		for (;itr != buf.end();)
		{
			if (*itr == '\r')
			{
				if ( *(++itr) == '\n')
				{
					break;
				}
				line.push_back('\r');
			}
			else if (*itr == '\n')
			{
				break;
			}
			line.push_back(*itr);
			++itr;
		}
		return line;
	}
}