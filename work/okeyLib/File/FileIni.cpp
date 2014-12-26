#include "PreCom.h"
#include "FileIni.h"
#include "File.h"
#include "Stream/FileStream.h"
#include "StringHelper.h"

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
			File file(filename, File::acRead, File::AllowRead);
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

	bool FileINI::Parse(const BinString& buf)
	{
		ValueList mpKey;
		std::string section;
		std::vector<std::string> lineList;
		GetLine(buf,lineList);
		std::vector<std::string>::iterator itr = lineList.begin();
		for (; itr != lineList.end(); ++itr)
		{
			if (itr->empty())
			{
				continue;
			}
			std::string newline = *itr;
			size_t pos = itr->find(";");
			if (pos == 0)
			{
				continue;
			}
			else if (pos != std::string::npos)
			{
				newline = itr->substr(0, pos);
			}
			if (isSection(newline))
			{
				if (section.empty())
				{
					section = newline;
					continue;
				}
				m_SectionList.insert(std::make_pair(section, mpKey));
				mpKey.clear();
				section = newline;
			}
			else
			{
				if (section.empty())
				{
					continue;
				}
				std::pair<std::string, std::string> ret;
				if (GetKeyValue(newline, ret))
				{
					mpKey.insert(ret);
				}
			}
		}
		if (!section.empty())
		{
			m_SectionList.insert(std::make_pair(section,mpKey));
		}
		return true;
	}


	bool FileINI::isSection(std::string& line)
	{
		std::string::size_type stLeft = line.find("[");
		std::string::size_type stRight = line.find("]");
		if (!line.empty() && stLeft != std::string::npos && stRight != std::string::npos && stRight > stLeft) 
		{
			std::string section(line, stLeft + 1, stRight - stLeft - 1);
			StringHelper::Trim(section);
			line = section;
			return true;
		}
		return false;
	}
	
	bool FileINI::GetKeyValue(std::string& line, std::pair<std::string, std::string>& ret)
	{
		if (line.empty())
		{
			return false;
		}
		std::string::size_type stpos = line.find("=");
		if (stpos == 0)
		{
			return false;
		}
		std::string key;
		std::string value;
		if (stpos == std::string::npos) 
		{
			key = line;
			StringHelper::Trim(line);
			value = "";
		} 
		else 
		{
			key = line.substr(0,stpos);
			value = line.substr(stpos + 1,line.length() - stpos - 1);
			StringHelper::Trim(key);
			StringHelper::Trim(value);
		}
		ret = std::make_pair(key,value);
		return true;
	}
 			
	void FileINI::GetLine(const BinString& buf, std::vector<std::string>& lineList)
	{
		lineList.clear();
 		if(buf.size() == 0)
 			return;
		std::string line;
		BinString::const_iterator itr = buf.begin();
		for (;itr != buf.end();++itr)
		{
			if (*itr == '\r')
			{
				++itr;
				if ( *itr == '\n' || *itr == 0)
				{
					lineList.push_back(line);
					line.clear();
					continue;
				}
				line.push_back('\r');
			}
			else if (*itr == '\n')
			{
				lineList.push_back(line);
				line.clear();
				continue;
			}
			else if(*itr == 0)
			{
				lineList.push_back(line);
				line.clear();
				continue;
			}
			line.push_back(*itr);
		}
		if (!line.empty())
		{
			lineList.push_back(line);
		}
	}

	bool FileINI::Write()
	{
		if (m_Filename.empty())
		{
			return false;
		}
		FileOutputStream file(m_Filename,File::AllowNone, File::Truncate);
		SectionList::iterator itr = m_SectionList.begin();
		for (; itr != m_SectionList.end(); ++itr)
		{
			file<<"["<<itr->first<<"]"<<std::endl;
			ValueList::iterator itr_v = itr->second.begin();
			for (; itr_v != itr->second.end(); ++itr_v)
			{
				file<<itr_v->first<<" = "<<itr_v->second << std::endl;
			}
			file<<std::endl;
		}
		return true;
	}
}