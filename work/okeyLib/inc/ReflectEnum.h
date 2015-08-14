/********************************************************************
	created:	2014/03/05
	author:		okey
	
	purpose:	enum的反射机制。
*********************************************************************/
#ifndef __OKEY_ENUM_H__
#define __OKEY_ENUM_H__

#include <string>
#include "HashMap.h"
#include "DefineEnum.h"

namespace okey
{
	class EnumHelper
	{
	public:
		static EnumHelper GetInstance()
		{
			static EnumHelper s;
			return s;
		}
		template<typename T>
		void RegisterEnum(T eval, const char* vstr);
		template<typename Enum_T>
		int32 GetEnumValue(const std::string& str);
		template<typename Enum_T>
		std::string GetEnumString(Enum_T enum_value);
	private:
		EnumHelper()
		{
#undef  DECLARE_ENUM
#define DECLARE_ENUM(T) 

#undef REG_ENUM
#define REG_ENUM(eval) RegisterEnum(eval,#eval);

#undef REG_ENUM_ID
#define REG_ENUM_ID(eval, ID) REG_ENUM(eval)
#include "DefineEnum.h"
		}
		
	};

	template<typename Enum_T>
	class TEnumType
	{
		friend EnumHelper;
	public:
		typedef typename hash_map<std::string, Enum_T>::const_iterator const_iterator;
		int32 GetEnumValue(const std::string& str)
		{
			hash_map<std::string, Enum_T>::iterator itr = _strtoid.find(str);
			if (itr == _strtoid.end())
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
		static TEnumType<Enum_T> _enum_type;
	};

	template<typename Enum_T> TEnumType<Enum_T> TEnumType<Enum_T>::_enum_type;

	template<typename T>
	void EnumHelper::RegisterEnum(T eval, const char* vstr)
	{
		TEnumType<T>::_enum_type._strtoid[vstr] = eval;
		TEnumType<T>::_enum_type._idtostr[eval] = vstr;
	}

	template<typename Enum_T>
	int32 EnumHelper::GetEnumValue(const std::string& str)
	{
		return TEnumType<Enum_T>::_enum_type.GetEnumValue(str);
	}

	template<typename Enum_T>
	std::string EnumHelper::GetEnumString(Enum_T enum_value)
	{
		return TEnumType<Enum_T>::_enum_type.GetEnumString(enum_value);
	}

#define GET_ENUM_STRING(ENUM, eval)	\
	EnumHelper::GetInstance().GetEnumString<ENUM>(eval)

#define GET_ENUM_VALUE(ENUM, str)	\
	EnumHelper::GetInstance().GetEnumValue<ENUM>(str)

}


#endif