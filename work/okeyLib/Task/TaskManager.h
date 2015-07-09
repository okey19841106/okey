/********************************************************************
	created:	2015/07/09
	created:	15:33
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_TASK_MANAGER_H__
#define __OKEY_TASK_MANAGER_H__

#include "AutoPtr.h"
#include <list>
#include "Thread/Mutex.h"
#include "Task.h"
#include "Notifications/NotificationCenter.h"
#include "TimeStamp.h"

namespace okey
{

	class Notification;
	class ThreadPool;
	class Exception;


	class TaskManager
	{
	public:
		typedef AutoPtr<Task> TaskPtr;
		typedef std::list<TaskPtr> TaskList;

		TaskManager();
		TaskManager(ThreadPool& pool);
		~TaskManager();

		void Start(Task* pTask);
		void CancelAll();
		void JoinAll();
		TaskList taskList() const;
		int32 GetCount() const;
		void AddObserver(const AbstractObserver& observer);
		void RemoveObserver(const AbstractObserver& observer);

		static const int32 MIN_PROGRESS_NOTIFICATION_INTERVAL;
	protected:
		void PostNotification(const Notification::Ptr& pNf);
		void TaskStarted(Task* pTask);
		void TaskProgress(Task* pTask, f32 progress);
		void TaskCancelled(Task* pTask);
		void TaskFinished(Task* pTask);
		void TaskFailed(Task* pTask, const Exception& exc);
	private:
		ThreadPool& _threadPool;
		TaskList _taskList;
		TimeStamp _lastProgressNotification;
		NotificationCenter _nc;
		mutable FastMutex _mutex;

		friend class Task;
	};

	inline int32 TaskManager::GetCount() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return (int32)_taskList.size();
	}
}

#endif