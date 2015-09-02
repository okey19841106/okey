/********************************************************************
	created:	2015/08/31
	created:	14:51
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SQL_CONNECTION_H__
#define __SQL_CONNECTION_H__

#include <string>
#include "Template/TFunctoion.h"
#include "FQueue.h"
#include "Thread/Runnable.h"
#include "Task/TaskManager.h"
#include "Thread/Condition.h"

namespace okey
{
	class SqlQueryResult;
	class Thread;

	class SqlConnection : public Runnable
	{
		friend class AsynQueryTask;
		friend class AsynUpdateTask;

	public:


		SqlConnection();
		virtual ~SqlConnection();

		template<typename Command_Type>
		static SqlConnection* CreateConnection(const std::string& dbtype)
		{
			return new Command_Type();
		}
		static void DestroyConnection(SqlConnection* con);

		virtual bool Open(const char* dbhost, uint16 dbport, const std::string& dbname, const std::string& username,const std::string& passwd) = 0;
		virtual void Close() = 0;

		virtual void ThreadStart(){}
		virtual void ThreadStop(){}
		virtual bool BeginTransaction(){return true;}
		virtual bool CommitTransaction(){return true;}
		virtual bool RollbackTransaction(){return true;}
		virtual SqlQueryResult* Query(const std::string& sql)=0;

		void AsynQuery(const std::string& sql, Template::Function<void (SqlQueryResult*)> callback);
		void FreeQueryResult(SqlQueryResult* result);
		virtual int32 Update(const std::string& sql, uint64* insertID = NULL) = 0;
		void AsynUpdate(const std::string& sql, Template::Function<void (int32, uint64)> callback);
		void ProcessAsynResult();

		//转义字符串。bin这类的。
		virtual size_t EscapeString(char* dest, const void* src, size_t len)
		{
			strncpy(dest, (const char*)src, len);
			return len;
		}
		std::string EscapeString(const void* src, size_t len);
		virtual std::string ErrorMsg() = 0;
		void Run();
	protected:
		void StartTask(Task* pTask);
		void PutQueryResult(Template::Function<void (SqlQueryResult*)>, SqlQueryResult*);
		void PutUpdateResult(Template::Function<void (int32, uint64)>, int32, uint64);
		Task* GetTask();

		struct AsynQueryResult
		{
			AsynQueryResult():_result(NULL){}
			AsynQueryResult(SqlQueryResult* r, Template::Function<void (SqlQueryResult*)> f):_result(r),_fun(f){}
			SqlQueryResult* _result;
			Template::Function<void (SqlQueryResult*)> _fun;
		};

		struct AsynUpdateResult
		{
			AsynUpdateResult():_ret(0),_insertID(0){}
			AsynUpdateResult(int32 r, uint64 id, Template::Function<void (int32, uint64)> f):_ret(r),_insertID(id),_fun(f){}
			int32 _ret;
			uint64 _insertID;
			Template::Function<void (int32, uint64)> _fun;
		};
		// 查询队列
		FQueue<AsynQueryResult> _queryResults;
		// 更新队列
		FQueue<AsynUpdateResult> _updateResults;
		//处理线程
		bool _exit;
		Thread* _thread;
		
		std::list<Task*> _taskList;
		FastMutex _mutex;
		Condition _event;
	};


}

#endif