/********************************************************************
	created:	2014/09/20
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __FILE_INI_H__
#define __FILE_INI_H__

#include <map>
#include <vector>
#include "VectorString.h"

namespace okey
{
	class FileINI
	{
		typedef std::map<std::string, std::string>  ValueList;
		typedef std::map<std::string, ValueList> SectionList;
	public:
		FileINI();
		FileINI(const std::string& filename);
		virtual ~FileINI();
		
		bool Open(const std::string& filename);
		bool Write();
		template<typename T>
		bool GetValue(const std::string& section, const std::string& key, T& ret)
		{
			SectionList::iterator itr = m_SectionList.find(section);
			if (itr == m_SectionList.end())
			{
				return false;
			}
			ValueList::iterator itr_v = itr->second.find(key);
			if (itr_v == itr->second.end())
			{
				return false;
			}
			ret = StringHelper::ToValue<T>(itr_v->second);
			return true;
		}

		template<typename T>
		void SetValue(const std::string& section, const std::string& key, const T& value)
		{
			std::string szVa = StringHelper::ToString<T>(value);
			SectionList::iterator itr = m_SectionList.find(section);
			if (itr == m_SectionList.end())
			{
				ValueList tmp;
				tmp.insert(std::make_pair(key, szVa));
				m_SectionList.insert(std::make_pair(section, tmp));
				return;
			}
			ValueList::iterator itr_v = itr->second.find(key);
			if (itr_v == itr->second.end())
			{
				itr->second.insert(std::make_pair(key, szVa));
				return;
			}
			itr_v->second = szVa;
			return;
		}
	protected:
		bool Parse(const BinString& buf);
		void GetLine(const BinString& buf, std::vector<std::string>& lineList);
		bool isSection(std::string& line);
		bool GetKeyValue(std::string& line, std::pair<std::string, std::string>& ret);
	private:
		std::string m_Filename;
		SectionList m_SectionList;
	};

	template<>
	inline bool FileINI::GetValue<std::string>(const std::string& section, const std::string& key, std::string& ret)
	{
		SectionList::iterator itr = m_SectionList.find(section);
		if (itr == m_SectionList.end())
		{
			return false;
		}
		ValueList::iterator itr_v = itr->second.find(key);
		if (itr_v == itr->second.end())
		{
			return false;
		}
		ret = itr_v->second;
		return true;
	}

	template<>
	inline void FileINI::SetValue<std::string>(const std::string& section, const std::string& key, const std::string& value)
	{
		SectionList::iterator itr = m_SectionList.find(section);
		if (itr == m_SectionList.end())
		{
			ValueList tmp;
			tmp.insert(std::make_pair(key, value));
			m_SectionList.insert(std::make_pair(section, tmp));
			return;
		}
		ValueList::iterator itr_v = itr->second.find(key);
		if (itr_v == itr->second.end())
		{
			itr->second.insert(std::make_pair(key, value));
			return;
		}
		itr_v->second = value;
		return;
	}
}


#endif