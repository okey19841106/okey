#include "PreCom.h"
#include "SqlConnection.h"


namespace okey
{
	SqlConnection* SqlConnection::CreateConnection(const std::string& dbtype)
	{
		return NULL;
	}

	void SqlConnection::DestroyConnection(SqlConnection* con)
	{
		delete con;
		con = NULL;
	}

	void SqlConnection::AsynQuery(const std::string& sql, QueryCallback* callback)
	{

	}

	void SqlConnection::FreeQueryResult(SqlQueryResult* result)
	{

	}

	void SqlConnection::AsynUpdate(const std::string& sql, UpdateCallback* callback)
	{

	}

	void SqlConnection::ProcessAsynResult()
	{

	}

	std::string SqlConnection::EscapeString(const void* src, size_t len)
	{
		char* temp = new char[2* len + 1];
		EscapeString(temp, src, len);
		std::string sql(temp);
		delete [] temp;
		return sql;
	}
}