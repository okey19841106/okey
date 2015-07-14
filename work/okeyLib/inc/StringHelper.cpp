#include "PreCom.h"
#include "StringHelper.h"
#include "AsciiCharacter.h"
#include "Exception.h"

namespace okey
{
	void StringHelper::TrimAllSpace(char* ptr)
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

	void StringHelper::Trim(char* ptr)
	{
		if (!ptr)
		{
			return;
		}
		char* stptr = ptr;
		char* sptr = ptr;
		char* eptr = ptr + strlen(ptr) - 1 ;
		char* endptr = eptr + 1; //'\0'
		bool flag = false;
		while(eptr != ptr && !flag)
		{
			switch(*eptr)
			{
			case ' ':
			case '\r':
			case '\n':
			case '\t':
				endptr = eptr--;
				break;
			default:
				*endptr = 0;
				flag = true;
				break;
			}
		}
		flag = false;
		bool isMove = false;
		while(*ptr != 0 && !flag)
		{
			switch(*ptr)
			{
			case ' ':
			case '\r':
			case '\n':
			case '\t':
				isMove = true;
				++ptr;
				break;
			default:
				sptr = ptr;
				flag = true;
				break;
			}
		}
		if (flag)
		{
			size_t len = strlen(sptr);
			memmove(stptr,sptr,len);
			*(stptr + len) = 0;
		}
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

	StringTokenizer::StringTokenizer(const std::string& str, const std::string& separators, int options)
	{
		std::string::const_iterator it1 = str.begin();
		std::string::const_iterator it2;
		std::string::const_iterator it3;
		std::string::const_iterator end = str.end();

		while (it1 != end)
		{
			if (options & TOK_TRIM)
			{
				while (it1 != end && AsciiCharacter::IsSpace(*it1)) ++it1;
			}
			it2 = it1;
			while (it2 != end && separators.find(*it2) == std::string::npos) ++it2;
			it3 = it2;
			if (it3 != it1 && (options & TOK_TRIM))
			{
				--it3;
				while (it3 != it1 && AsciiCharacter::IsSpace(*it3)) --it3;
				if (!AsciiCharacter::IsSpace(*it3)) ++it3;
			}
			if (options & TOK_IGNORE_EMPTY)
			{
				if (it3 != it1)
					_tokens.push_back(std::string(it1, it3));
			}
			else
			{
				_tokens.push_back(std::string(it1, it3));
			}
			it1 = it2;
			if (it1 != end) ++it1;
		}
	}

	StringTokenizer::~StringTokenizer()
	{

	}

	
}