#include "PreCom.h"
#include "StringHelper.h"


namespace okey
{
	void StringHelper::Trim(char* ptr)
	{
		if (!ptr)
		{
			return;
		}
		char* endptr = ptr;

		while(*ptr != 0)
		{
			switch(*ptr)
			{
			case ' ':
			case '\r':
			case '\n':
			case '\t':
				break;
			default:
				*endptr++ = *ptr;
				break;
			}
			++ptr;
		}
		*endptr = 0;
	}

	inline std::string& ltrim(std::string &str) {  
		std::string::iterator p = std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace)));  
		str.erase(str.begin(), p);  
		return str;  
	}  

	inline std::string& rtrim(std::string &str) {  
		std::string::reverse_iterator p = std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int , int>(isspace)));  
		str.erase(p.base(), str.end());  
		return str;  
	}  

	void StringHelper::Trim(std::string& str)
	{
		ltrim(rtrim(str));
	}

	void StringHelper::Tokenize(const std::string&str, std::vector<std::string>& strs, const std::string& delimit)
	{
		if (str.empty() || delimit.empty())
		{
			return;
		}

		size_t pos = str.find_first_not_of(delimit.c_str());
		size_t index = 0;

		while(pos != std::string::npos)
		{
			index = str.find_first_of(delimit.c_str(), pos);
			if (index == std::string::npos)
			{
				index = str.length();
			}
			strs.push_back(str.substr(pos, index - pos));
			pos = str.find_first_not_of(delimit.c_str(), index);
		}
	}
}