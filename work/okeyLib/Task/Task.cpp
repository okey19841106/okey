#include "PreCom.h"
#include "Task.h"
#include "TaskManager.h"

namespace okey
{
	Task::Task(const std::string& name):_name(name),_pOwner(NULL),_progress(0.0f),_state(TASK_IDLE),_cancelEvent(false)
	{
	}

	Task::~Task()
	{
	}

	void Task::Cancel()
	{
		_state = TASK_CANCELLING;
		_cancelEvent.Set();
		if (_pOwner)
		{
			_pOwner->TaskCancelled(this);
		}
	}

	void Task::Reset()
	{
		_progress = 0.0f;
		_state = TASK_IDLE;
		_cancelEvent.Reset();
	}

	void Task::Run()
	{
		TaskManager* pOwer = GetOwner();
		if (pOwer)
		{
			pOwer->TaskStarted(this);
		}
		try
		{
			_state = TASK_RUNNING;
			RunTask();
		}
		catch (Exception& exc)
		{
			if (pOwer)
			{
				pOwer->TaskFailed(this, exc);
			}
		}
		catch (std::exception& exc)
		{
			if (pOwer)
			{
				pOwer->TaskFailed(this, SystemException(exc.what()));
			}
		}
		catch (...)
		{
			if (pOwer)
			{
				pOwer->TaskFailed(this, SystemException("unknown exception"));
			}
		}
		_state = TASK_FINISHED;
		if (pOwer)
		{
			pOwer->TaskFinished(this);
		}
	}

	bool Task::Sleep(int64 milliseconds)
	{
		return _cancelEvent.TryWait(milliseconds);
	}

	void Task::SetProgress(f32 progress)
	{
		FastMutex::ScopedLock lock(_mutex);
		_progress = progress;
		if (_pOwner)
		{
			_pOwner->TaskProgress(this, _progress);
		}
	}

	void Task::PostNotification(Notification* pNf)
	{
		FastMutex::ScopedLock lock(_mutex);
		if (_pOwner)
		{
			_pOwner->PostNotification(pNf);
		}
	}

	void Task::SetOwner(TaskManager* pOwner)
	{
		FastMutex::ScopedLock lock(_mutex);
		_pOwner = pOwner;
	}

	void Task::SetState(TaskState state)
	{
		_state = state;
	}
}