#include "PreCom.h"
#include "TaskManager.h"
#include "Thread/ThreadPool.h"
#include "TaskNotification.h"

namespace okey
{
	const int32 TaskManager::MIN_PROGRESS_NOTIFICATION_INTERVAL = 100; // 100 millisecond;

	TaskManager::TaskManager():_threadPool(ThreadPool::defaultPool())
	{

	}

	TaskManager::TaskManager(ThreadPool& pool):_threadPool(pool)
	{

	}

	TaskManager::~TaskManager()
	{
		
	}

	void TaskManager::Start(Task* pTask)
	{
		TaskPtr pAutoTask(pTask);
		FastMutex::ScopedLock lock(_mutex);
		pAutoTask->SetOwner(this);
		pAutoTask->SetState(Task::TASK_STARTING);
		_taskList.push_back(pAutoTask);
		try
		{
			_threadPool.Start(*pAutoTask,pAutoTask->name());
		}
		catch(...)
		{
			_taskList.pop_back();
			throw;
		}
	}
	void TaskManager::CancelAll()
	{
		FastMutex::ScopedLock lock(_mutex);
		for(TaskList::iterator itr = _taskList.begin(); itr != _taskList.end(); ++itr)
		{
			(*itr)->Cancel();
		}
	}

	void TaskManager::JoinAll()
	{
		_threadPool.JoinAll();
	}

	TaskManager::TaskList TaskManager::taskList() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _taskList;
	}

	void TaskManager::AddObserver(const AbstractObserver& observer)
	{
		_nc.AddObserver(observer);
	}

	void TaskManager::RemoveObserver(const AbstractObserver& observer)
	{
		_nc.RemoveObserver(observer);
	}

	void TaskManager::PostNotification(const Notification::Ptr& pNf)
	{
		_nc.PostNotification(pNf);
	}

	void TaskManager::TaskStarted(Task* pTask)
	{
		_nc.PostNotification(new TaskStartedNotification(pTask));
	}

	void TaskManager::TaskProgress(Task* pTask, f32 progress)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_lastProgressNotification.isElapsed(MIN_PROGRESS_NOTIFICATION_INTERVAL))
		{
			_lastProgressNotification = TimeStamp.CurrentTime();
			_nc.PostNotification(new TaskProgressNotification(pTask,progress));
		}
	}

	void TaskManager::TaskCancelled(Task* pTask)
	{
		_nc.PostNotification(new TaskCancelledNotification(pTask));
	}

	void TaskManager::TaskFinished(Task* pTask)
	{
		_nc.PostNotification(new TaskFinishedNotification(pTask));
		FastMutex::ScopedLock lock(_mutex);
		for(TaskList::iterator itr = _taskList.begin(); itr != _taskList.end(); ++itr)
		{
			if (*itr == pTask)
			{
				_taskList.erase(itr);
				break;
			}
		}
	}

	void TaskManager::TaskFailed(Task* pTask, const Exception& exc)
	{
		_nc.PostNotification(new TaskFailedNotification(pTask,exc));
	}
	
}