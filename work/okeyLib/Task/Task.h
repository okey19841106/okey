/********************************************************************
	created:	2015/07/09
	created:	14:47
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_TASK_H__
#define __OKEY_TASK_H__

#include "Thread/Runnable.h"
#include "CRefcounter.h"
#include "Thread/Mutex.h"
#include "Thread/Event.h"

namespace okey
{

	class TaskManager;
	class Notification;
	class NotificationCenter;

	class Task: public Runnable, public CRefCounter
	{
	public:
		enum TaskState
		{
			TASK_IDLE,
			TASK_STARTING,
			TASK_RUNNING,
			TASK_CANCELLING,
			TASK_FINISHED
		};
		Task(const std::string& name);
		inline const std::string& name() const{return _name;}
		f32 GetProgress() const;
		virtual void Cancel();
		inline bool IsCancel() const{return _state == TASK_CANCELLING;}
		inline TaskState GetState() const{return _state;}
		void Reset();
		virtual void RunTask() = 0;
		void Run();
	protected:
		virtual ~Task();
		bool Sleep(int64 milliseconds); //suspends the current thread
		void SetProgress(f32 progress);
		virtual void PostNotification(Notification* pNf);
		void SetOwner(TaskManager* pOwner);
		TaskManager* GetOwner() const;
		void SetState(TaskState state);
	private:
		Task();
		Task(const Task&);
		Task& operator=(const Task&);
	private:
		std::string _name;
		TaskManager* _pOwner;
		f32 _progress;
		TaskState _state;
		Event _cancelEvent;
		mutable FastMutex _mutex;
		friend class TaskManager;
	};

	inline f32 Task::GetProgress() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _progress;
	}

	inline TaskManager* Task::GetOwner() const
	{
		FastMutex::ScopedLock lock(_mutex);
		return _pOwner;
	}
}

#endif