#include "PreCom.h"
#include "SqlConnection.h"


namespace okey
{
	
	SqlConnection::SqlConnection()
	{

	}

	SqlConnection::~SqlConnection()
	{

	}

	void SqlConnection::DestroyConnection(SqlConnection* con)
	{
		delete con;
		con = NULL;
	}

	void SqlConnection::AsynQuery(const std::string& sql, Template::Function<void (SqlQueryResult*)> callback)
	{

	}

	void SqlConnection::FreeQueryResult(SqlQueryResult* result)
	{
		delete result;
		result = NULL;
	}

	void SqlConnection::AsynUpdate(const std::string& sql, Template::Function<void (int32, uint64)> callback)
	{

	}

	void SqlConnection::ProcessAsynResult()
	{
		while(!_queryResults.IsEmpty())
		{
			AsynQueryResult ret;
			_queryResults.Pop(ret);
			ret._fun(ret._result);
			FreeQueryResult(ret._result);
		}
		while(!_updateResults.IsEmpty())
		{
			AsynUpdateResult ret;
			_updateResults.Pop(ret);
			ret._fun(ret._ret, ret._insertID);
		}
	}

	std::string SqlConnection::EscapeString(const void* src, size_t len)
	{
		char* temp = new char[2* len + 1];
		EscapeString(temp, src, len);
		std::string sql(temp);
		delete [] temp;
		return sql;
	}

	void SqlConnection::PutQueryResult(Template::Function<void (SqlQueryResult*)> callback, SqlQueryResult* result)
	{
		_queryResults.Push(AsynQueryResult(result,callback));
	}

	void SqlConnection::PutUpdateResult(Template::Function<void (int32, uint64)> callback, int32 ret, uint64 insertid)
	{
		_updateResults.Push(AsynUpdateResult(ret, insertid, callback));
	}
}