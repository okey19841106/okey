#include "PreCom.h"
#include "SqlConnection.h"
#include "Task/Task.h"
#include "Thread/Thread.h"
#include "AutoPtr.h"

namespace okey
{
	
	class AsynQueryTask: public Task
	{
	public:
		AsynQueryTask(SqlConnection* c, const std::string& sql, Template::Function<void (SqlQueryResult*)> f):Task("AsynQueryTask"),
			_pConn(c), _sql(sql), _fun(f)
		{

		}
		~AsynQueryTask()
		{

		}
		void RunTask()
		{
			SqlQueryResult* result = _pConn->Query(_sql.c_str());
			if (_fun.empty())
			{
				_pConn->FreeQueryResult(result);
			}
			else
			{
				_pConn->PutQueryResult(_fun, result);
			}
		}
	protected:
		SqlConnection* _pConn;
		std::string _sql;
		Template::Function<void (SqlQueryResult*)> _fun;
	};

	class AsynUpdateTask: public Task
	{
	public:
		AsynUpdateTask(SqlConnection* c, const std::string& sql, Template::Function<void (int32, uint64)> f):Task("AsynUpdateTask"),
			_pConn(c), _sql(sql), _fun(f)
		{

		}
		~AsynUpdateTask()
		{

		}
		void RunTask()
		{
			uint64 insertid = 0;
			int32 ret= _pConn->Update(_sql.c_str(), &insertid);
			if (!_fun.empty())
			{
				_pConn->PutUpdateResult(_fun,ret,insertid);
			}
		}
	protected:
		SqlConnection* _pConn;
		std::string _sql;
		Template::Function<void (int32, uint64)> _fun;
	};

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
		if (_thread == NULL)
		{
			_thread = new Thread();
			_thread->Start(*this);
		}
		
	}

	void SqlConnection::FreeQueryResult(SqlQueryResult* result)
	{
		delete result;
		result = NULL;
	}

	void SqlConnection::AsynUpdate(const std::string& sql, Template::Function<void (int32, uint64)> callback)
	{
		if (_thread == NULL)
		{
			_thread = new Thread();
			_thread->Start(*this);
		}
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

	void SqlConnection::Run()
	{
		ThreadStart();
		Task* pTask = GetTask();
		while(pTask != NULL)
		{
			{
				AutoPtr<Task> taskPtr(pTask);
				pTask->RunTask();
			}
			pTask = GetTask();
		}
		ThreadStop();
	}

	void SqlConnection::StartTask(Task* pTask)
	{
		
		{
			FastMutex::ScopedLock lock(_mutex);
			_taskList.push_back(pTask);
		}
		_event.Signal();

	}

	Task* SqlConnection::GetTask()
	{
		_mutex.Lock();
		while (_taskList.empty())
		{
			if (_exit)
			{
				_mutex.UnLock();
				return NULL;
			}
			_event.Wait(_mutex);
		}
		Task* pTask = _taskList.front();
		_taskList.pop_front();
		_mutex.UnLock();
		return pTask;
	}
}