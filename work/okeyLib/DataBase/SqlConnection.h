/********************************************************************
	created:	2015/08/31
	created:	14:51
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SQL_CONNECTION_H__
#define __SQL_CONNECTION_H__

#include <string>

namespace okey
{
	class SqlConnection
	{
	public:
		SqlConnection();
		virtual ~SqlConnection();

		static SqlConnection* CreateConnection(const std::string& dbtype);
		static void DestroyConnection(SqlConnection* con);

		virtual bool Open(const char* dbhost, uint16 dbport, const std::string& dbname, const std::string& username,const std::string& passwd) = 0;
		virtual void Close() = 0;

		virtual void ThreadStart(){}
		virtual void ThreadStop(){}
		virtual bool BeginTransaction(){return true;}
		virtual bool CommitTransaction(){return true;}
		virtual bool RollbackTransaction(){return true;}
		virtual SqlQueryResult* Query(const std::string& sql)=0;
		void AsynQuery(const std::string& sql, QueryCallback* callback);
		void FreeQueryResult(SqlQueryResult* result);
		void int32 Update(const std::string& sql, uint64* insertID = NULL) = 0;
		void AsynUpdate(const std::string& sql, UpdateCallback* callback);
		void ProcessAsynResult();

		//转义字符串。bin这类的。
		virtual size_t EscapeString(char* dest, const void* src, size_t len)
		{
			strncpy(dest, (const char*)src, len);
			return len;
		}
		std::string EscapeString(const void* src, size_t len);
		virtual std::string ErrorMsg() = 0;

	protected:
		void PutQueryResult(QueryCallback*, SqlQueryResult*);
		void PutUpdateResult(UpdateCallback*, int32, uint64);

		// 查询队列
		// 更新队列
		//处理线程
	};
}

#endif