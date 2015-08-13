/********************************************************************
	created:	2014/03/05
	author:		okey
	
	purpose:	enum的反射机制。
*********************************************************************/


#ifndef __OKEY_ENUM_H__
#define __OKEY_ENUM_H__

#include <string>
#include "HashMap.h"

namespace okey
{
	template <typename Enum_T> 
	class EnumHelper 
	{ 
	public: 
		static const char * ToString(Enum_T e) 
		{ 
			for(int i = 0; i < _countof(EnumHelper<Enum_T>::s_allEnums); i++) 
			{ 
				if( s_allEnums[i] == e) 
					return s_allEnumNames[i]; 
			} 
			return NULL; 
		} 

	private: 
		static const char* s_typeName; 
		static Enum_T s_allEnums[]; 
		static char s_singleEnumStr[]; 
		static const char* s_allEnumNames[]; 

		static void SplitEnumDefString() 
		{ 
			char * p = s_singleEnumStr; 
			while( isspace(*p) ) p++; 
			for(int i = 0; i < _countof(EnumHelper<Enum_T>::s_allEnums); i++) 
			{ 
				s_allEnumNames[i] = p; 
				while( *p == '_' || isdigit(*p) || isalpha(*p) ) p++; 
				bool meet_comma = ( *p == ',' ); 
				*p++ = '\0'; 
				if( !meet_comma ) 
				{ 
					while( *p && *p != ',') p++; 
					if( *p ) p++; 
				} 
				while( *p && isspace(*p) ) p++; 
			} 
		} 
	}; 

#define TO_ENUM_ITEM(...)  __VA_ARGS__ 
#define STRINGIZE(...)  #__VA_ARGS__ 
	
#define REFLECT_ENUM(enum_type_name, enum_list)\
template<> enum_type_name EnumHelper<enum_type_name>::s_allEnums[] = \
	{\
	TO_ENUM_ITEM(enum_list)\
	};\
	template<> const char* EnumHelper<enum_type_name>::s_allEnumNames[_countof(EnumHelper<enum_type_name>::s_allEnums)];\
	template<> char EnumHelper<enum_type_name>::s_singleEnumStr[] = STRINGIZE(enum_list);\
	template<> const char * EnumHelper<enum_type_name>::s_typeName = (EnumHelper<enum_type_name>::SplitEnumDefString(), #enum_type_name);

	template<typename Enum_T>
	class TEnumType
	{
	public:
		typedef hash_map<std::string, Enum_T>::const_iterator const_iterator;
		int32 GetEnumValue(const std::string& str)
		{
			hash_map<std::string, Enum_T>::iterator itr = _strtoid.find(str);
			if (itr == _strtoid)
			{
				return -1;
			}
			return itr->second;
		}
		std::string GetEnumString(Enum_T enum_value)
		{
			hash_map<Enum_T, std::string>::iterator itr = _idtostr.find(enum_value);
			//assert()
			return itr->second;
		}
		const_iterator enum_begin(){return _strtoid.begin();}
		const_iterator enum_end(){return _strtoid.end();}
		int32 GetMaxValue()
		{
			hash_map<Enum_T,std::string>::reverse_iterator riter = _idtostr.rbegin();
			if (riter == _idtostr.rend())
			{
				return -1;
			}
			return riter->first;
		}
		static TEnumType* GetInstance(){return &_enum_type;}
	private:
		hash_map<std::string, Enum_T> _strtoid;
		hash_map<Enum_T, std::string> _idtostr;
		static TEnumType _enum_type;
	};

	template<typename Enum_T> TEnumType<Enum_T>::_enum_type;

}


#endif