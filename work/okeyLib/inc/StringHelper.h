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
#include "Exception.h"


namespace okey
{
	class StringHelper
	{
	public:
		template<typename T>
		static T ToValue(const char* valstr);

		template<typename T>
		static T ToValue(const std::string& s)
		{
			return StringHelper::ToValue<T>(s.c_str());
		}

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

		static char toLower(char ch)
		{
			return (char)tolower(ch);
		}
		static char toUpper(char ch)
		{
			return (char)toupper(ch);
		}
		static void TrimAllSpace(char* ptr);
		static void Trim(char* ptr);
		static void Trim(std::string& str);
		static void Tokenize(const std::string&str, std::vector<std::string>& strs, const std::string& delimit = ";");
		template<typename T>
		static std::string ToHexString(T v, int32 wide);
	};

	template<>
	inline int64 StringHelper::ToValue<int64>(const char* valstr)
	{
		int64 value = 0;
		tsscanf(valstr,"%"INT64_FROMAT,&value);
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
		tsscanf(valstr,"%"UINT64_FORMAT,&value);
		return value;
	}

	template<>
	inline uint32 StringHelper::ToValue<uint32>(const char* valstr)
	{
		uint32 value = 0;
		tsscanf(valstr, "%u",&value);
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
	inline std::string StringHelper::ToString<int32>(int32 val)
	{
		char buf[64] = {0};
		tsnprintf(buf, 64, "%d", val);
		return buf;
	}

	template<>
	inline std::string StringHelper::ToString<int64>(int64 val)
	{
		char buf[64] = {0};
		tsnprintf(buf, 64, "%"INT64_FROMAT, val);
		return buf;
	}

	template<>
	inline std::string StringHelper::ToString<uint32>(uint32 val)
	{
		char buf[64] = {0};
		tsnprintf(buf, 64, "%u", val);
		return buf;
	}

	template<>
	inline std::string StringHelper::ToString<uint64>(uint64 val)
	{
		char buf[64] = {0};
		tsnprintf(buf, 64, "%"UINT64_FORMAT, val);
		return buf;
	}

	template<>
	inline std::string StringHelper::ToString<f64>(f64 val)
	{
		char buf[64] = {0};
		tsnprintf(buf, 64, "%f", val);
		return buf;
	}

	template <class S>
	int icompare(const S& str1, const S& str2)
	{
		typename S::const_iterator it1(str1.begin());
		typename S::const_iterator end1(str1.end());
		typename S::const_iterator it2(str2.begin());
		typename S::const_iterator end2(str2.end());
		while (it1 != end1 && it2 != end2)
		{
			typename S::value_type c1(StringHelper::toLower(*it1));
			typename S::value_type c2(StringHelper::toLower(*it2));
			if (c1 < c2)
				return -1;
			else if (c1 > c2)
				return 1;
			++it1; ++it2;
		}

		if (it1 == end1)
			return it2 == end2 ? 0 : -1;
		else
			return 1;
	}

	template <class S>
	int icompare(
		const S& str,
		typename S::size_type pos,
		typename S::size_type n,
		const typename S::value_type* ptr)
	{
		typename S::size_type sz = str.size();
		if (pos > sz) pos = sz;
		if (pos + n > sz) n = sz - pos;
		typename S::const_iterator it  = str.begin() + pos; 
		typename S::const_iterator end = str.begin() + pos + n;
		while (it != end && *ptr)
		{
			typename S::value_type c1(StringHelper::toLower(*it));
			typename S::value_type c2(StringHelper::toLower(*ptr));
			if (c1 < c2)
				return -1;
			else if (c1 > c2)
				return 1;
			++it; ++ptr;
		}

		if (it == end)
			return *ptr == 0 ? 0 : -1;
		else
			return 1;
	}

	template <class S>
	int icompare(
		const S& str,
		const typename S::value_type* ptr)
	{
		return icompare(str, 0, str.size(), ptr);
	}

	template< >
	inline std::string StringHelper::ToHexString<int64>(int64 v, int32 wide)
	{
		//poco_assert (width > 0 && width < 64);
		char buffer[64];
		tsnprintf(buffer, 64, INT64_FROMAT_X, wide, v);
		return buffer;
	}

	template< >
	inline std::string StringHelper::ToHexString<uint64>(uint64 v, int32 wide)
	{
		char buffer[64];
		tsnprintf(buffer, 64, INT64_FROMAT_X, wide, v);
		return buffer;
	}

#define TO_HEX_STRING_INT(value, wide)	\
	StringHelper::ToHexString<int64>((int64)value, wide)

	class StringTokenizer
	{
	public:
		enum Options
		{
			TOK_IGNORE_EMPTY = 1, /// ignore empty tokens
			TOK_TRIM         = 2  /// remove leading and trailing whitespace from tokens
		};

		typedef std::vector<std::string>::const_iterator Iterator;
		StringTokenizer(const std::string& str, const std::string& separators, int options = 0);
		~StringTokenizer();
		Iterator begin() const;
		Iterator end() const;
		const std::string& operator [] (std::size_t index) const;
		std::size_t count() const;

	private:
		StringTokenizer(const StringTokenizer&);
		StringTokenizer& operator=(const StringTokenizer&);
		std::vector<std::string> _tokens;
	};

	inline StringTokenizer::Iterator StringTokenizer::begin() const
	{
		return _tokens.begin();
	}

	inline StringTokenizer::Iterator StringTokenizer::end() const
	{
		return _tokens.end();
	}

	inline const std::string& StringTokenizer::operator [] (std::size_t index) const
	{
		if (index >= _tokens.size()) 
			throw RangeException();
		return _tokens[index];
	}

	inline std::size_t StringTokenizer::count() const
	{
		return _tokens.size();
	}
}