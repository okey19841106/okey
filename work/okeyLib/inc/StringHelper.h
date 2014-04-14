/********************************************************************
	created:	2014/04/14
	created:	15:19
	author:		
	
	purpose:	
*********************************************************************/

#include "Types.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#ifdef WINDOWS

#define STRING_HELPER_SNPRINTF _snprintf_s
#define STRING_HELPER_SSCANF sscanf_s
#define STRING_HELPER_STRNCPY(DES,SRC,LEN) strncpy_s(DES,LEN,SRC,LEN)
#define STRING_HELPER_STRDUP _strdup

#else

#define STRING_HELPER_SNPRINTF snprintf
#define STRING_HELPER_SSCANF sscanf
#define STRING_HELPER_STRNCPY(DES,SRC,LEN) strncpy(DES,SRC,LEN)
#define STRING_HELPER_STRDUP strdup

#endif

namespace okey
{
	class StringHelper
	{
	public:
		template<typename T>
		static T ToValue(const char* valstr);

		template<typename T>
		static std::string ToString(T val);

		static void ToUpper(char* str)
		{
			while( *str != 0)
			{
				(*str) = (char)toupper(*str);
				++str;
			}
		}

		static void ToUpper(std::string& str)
		{
			std::transform(str.begin(),str.end(),str.begin(),toupper);
		}

		static void ToLower(char* str)
		{
			while( *str != 0)
			{
				*str = (char)tolower(*str);
				++str;
			}
		}

		static void ToLower(std::string& str)
		{
			std::transform(str.begin(),str.end(),str.begin(),tolower);
		}

		static void Trim(char* ptr);
		static void Tokenize(const std::string&str, std::vector<std::string>& strs, const std::string& delimit = ";");
	};

	template<>
	inline int64 StringHelper::ToValue<int64>(const char* valstr)
	{
		int64 value = 0;
		STRING_HELPER_SSCANF(valstr,"%"INT64_FROMAT,&value);
		return value;
	}

	template<>
	inline int32 StringHelper::ToValue<int32>(const char* valstr)
	{
		return atoi(valstr);
	}

	template<>
	inline int16 StringHelper::ToValue<int16>(const char* valstr)
	{
		return (int16)atoi(valstr);
	}

	template<>
	inline int8 StringHelper::ToValue<int8>(const char* valstr)
	{
		return (int8)atoi(valstr);
	}

	template<>
	inline uint64 StringHelper::ToValue<uint64>(const char* valstr)
	{
		uint64 value = 0;
		STRING_HELPER_SSCANF(valstr,"%"UINT64_FORMAT,&value);
		return value;
	}

	template<>
	inline uint32 StringHelper::ToValue<uint32>(const char* valstr)
	{
		uint32 value = 0;
		STRING_HELPER_SSCANF(valstr, "%u",&value);
		return value;
	}

	template<>
	inline uint16 StringHelper::ToValue<uint16>(const char* valstr)
	{
		return (uint16)StringHelper::ToValue<uint32>(valstr);
	}

	template<>
	inline uint8 StringHelper::ToValue<uint8>(const char* valstr)
	{
		return (uint8)StringHelper::ToValue<uint32>(valstr);
	}

	template<>
	inline f64 StringHelper::ToValue<f64>(const char* valstr)
	{
		return strtod(valstr,NULL);
	}

	template<>
	static std::string StringHelper::ToString<int32>(int32 val)
	{
		char buf[64] = {0};
		STRING_HELPER_SNPRINTF(buf, 64, "%d", val);
		return buf;
	}

	template<>
	static std::string StringHelper::ToString<int64>(int64 val)
	{
		char buf[64] = {0};
		STRING_HELPER_SNPRINTF(buf, 64, "%"INT64_FROMAT, val);
		return buf;
	}

	template<>
	static std::string StringHelper::ToString<uint32>(uint32 val)
	{
		char buf[64] = {0};
		STRING_HELPER_SNPRINTF(buf, 64, "%u", val);
		return buf;
	}

	template<>
	static std::string StringHelper::ToString<uint64>(uint64 val)
	{
		char buf[64] = {0};
		STRING_HELPER_SNPRINTF(buf, 64, "%"UINT64_FORMAT, val);
		return buf;
	}

	template<>
	static std::string StringHelper::ToString<f64>(f64 val)
	{
		char buf[64] = {0};
		STRING_HELPER_SNPRINTF(buf, 64, "%f", val);
		return buf;
	}
}