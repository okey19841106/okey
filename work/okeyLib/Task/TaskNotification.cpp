#include "PreCom.h"
#include "TaskNotification.h"


namespace okey
{
	TaskNotification::TaskNotification(Task* pTask):
	_pTask(pTask)
	{
		if (_pTask) 
			_pTask->AddRef();
	}


	TaskNotification::~TaskNotification()
	{
		if (_pTask) 
			_pTask->DecRef();
	}


	TaskStartedNotification::TaskStartedNotification(Task* pTask):
	TaskNotification(pTask)
	{
	}


	TaskStartedNotification::~TaskStartedNotification()
	{
	}


	TaskCancelledNotification::TaskCancelledNotification(Task* pTask):
	TaskNotification(pTask)
	{
	}


	TaskCancelledNotification::~TaskCancelledNotification()
	{
	}


	TaskFinishedNotification::TaskFinishedNotification(Task* pTask):
	TaskNotification(pTask)
	{
	}


	TaskFinishedNotification::~TaskFinishedNotification()
	{
	}


	TaskFailedNotification::TaskFailedNotification(Task* pTask, const Exception& exc):
	TaskNotification(pTask),_pException(exc.clone())
	{
	}


	TaskFailedNotification::~TaskFailedNotification()
	{
		delete _pException;
	}


	TaskProgressNotification::TaskProgressNotification(Task* pTask, f32 progress):
	TaskNotification(pTask),_progress(progress)
	{
	}


	TaskProgressNotification::~TaskProgressNotification()
	{
	}
}