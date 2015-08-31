/********************************************************************
	created:	2015/08/31
	created:	16:07
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SQL_QUERY_RESULT_H__
#define __SQL_QUERY_RESULT_H__

#include "StringHelper.h"

namespace okey
{
	class SqlField
	{
	public:
		enum DataType
		{
			DT_UNKNOWN = 0,
			DT_STRING = 1,
			DT_INTEGER = 2,
			DT_FLOAT = 3,
		};
	public:
		SqlField(const char* value, size_t len, DataType dataType):_value(value), _len(len),_type(dataType){}
		~SqlField(){}

#define SQL_FIELDTOINTEGER(T)	\
	operator T() const	\
	{	\
		if(_value == NULL) return 0;	\
		else if(DT_INTEGER == _type) return StringHelper::ToValue<T>(_value);	\
		else if(DT_FLOAT == _type) (T)return StringHelper::ToValue<f64>(_value);	\
		return 0;	\
	}
		SQL_FIELDTOINTEGER(int8)
		SQL_FIELDTOINTEGER(uint8)
		SQL_FIELDTOINTEGER(int16)
		SQL_FIELDTOINTEGER(uint16)
		SQL_FIELDTOINTEGER(int32)
		SQL_FIELDTOINTEGER(uint32)
		SQL_FIELDTOINTEGER(int64)
		SQL_FIELDTOINTEGER(uint64)

		operator f64() const
		{
			if (_value == NULL)
			{
				return 0;
			}
			else if (DT_INTEGER == _type || DT_FLOAT == _type)
			{
				return StringHelper::ToValue<f64>(_value);
			}
			return 0;
		}

		operator f32() const
		{
			return (f32)(operator double());
		}

		operator bool() const
		{
			if (DT_INTEGER == _type)
			{
				return StringHelper::ToValue<int32>(_value) != 0;
			}
			return false;
		}

		std::string GetString() const
		{
			if (_value == NULL)
			{
				return "";
			}
			else if (DT_STRING == _type)
			{
				return _value;
			}
			return "";
		}

		size_t GetBytes(void* buf, size_t len) const
		{
			if (_value == NULL)
			{
				return 0;
			}
			else if (len > _len)
			{
				len = _len;
			}
			memmove(buf, _value, len);
			return len;
		}

		size_t GetLength() const
		{
			return _len;
		}
	protected:
		const char* _value;
		size_t _len;
		DataType _type;
	};


	class SqlQueryResult
	{
	public:
		SqlQueryResult(){}
		virtual ~SqlQueryResult(){}

		virtual bool NextRow() = 0;
		virtual int32 GetFieldNum() const  = 0;
		virtual std::string GetFieldName(int32 idx) const = 0;
		virtual SqlField GetField(int32 idx) const = 0;
		virtual SqlField GetField(const char* name) const = 0;
		virtual uint64 GetNumOfRows() const = 0;
	};
}

#endif