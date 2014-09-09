/********************************************************************
	created:	2014/08/22
	created:	15:16
	author:		
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_HASH_MAP_H___
#define __OKEY_HASH_MAP_H___

#ifdef WINDOWS
#include <hash_map>
#else
#include <ext/hash_map>
#endif

namespace okey
{
#ifdef WINDOWS
#define HM_NAMESPACE	stdext
	using stdext::hash_map;
#else
#define HM_NAMESPACE	__gnu_cxx
	using __gnu_cxx::hash_map;
#endif
}

#ifndef WINDOWS
#include <string>

namespace __gnu_cxx
{
	using std::string;
	template<> struct hash<unsigned long long>
	{
		size_t operator()(const unsigned long long& __x)const
		{
			return (size_t)__x;
		}
	};

	template<> struct hash<string>
	{
		size_t operator()(const string& s)const
		{
			return __stl_hash_string(s.c_str());
		}
	};
}
#else
	struct string_less : public std::binary_function<std::string, std::string, bool>  
	{   
	public:   
		result_type operator()(const first_argument_type& _Left, const second_argument_type& _Right) const   
		{   
			return(_Left.compare(_Right) < 0 ? true : false);   
		}   
	};  
#endif


#endif