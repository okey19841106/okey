/********************************************************************
	created:	2015/07/09
	created:	16:12
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_TASK_NOTIFICATION_H__
#define __OKEY_TASK_NOTIFICATION_H__


#include "Notifications/Notification.h"
#include "Task.h"

namespace okey
{
	class TaskNotification: public Notification
	{
	public:
		TaskNotification(Task* pTask);
		inline Task* GetTask() const{return _pTask;}
	protected:
		virtual ~TaskNotification();
	private:
		Task* _pTask;
	};

	class TaskStartedNotification: public TaskNotification
	{
	public:
		TaskStartedNotification(Task* pTask);
	protected:
		~TaskStartedNotification();
	};

	class TaskCancelledNotification: public TaskNotification
	{
	public:
		TaskCancelledNotification(Task* pTask);
	protected:
		~TaskCancelledNotification();
	};

	class TaskFinishedNotification: public TaskNotification
	{
	public:
		TaskFinishedNotification(Task* pTask);
	protected:
		~TaskFinishedNotification();
	};

	class TaskFailedNotification: public TaskNotification
	{
	public:
		TaskFailedNotification(Task* pTask, const Exception& exc);
		inline const Exception& GetReason()const{ return *_pException;}
	protected:
		~TaskFailedNotification();
	private:
		Exception* _pException;
	};

	class TaskProgressNotification: public TaskNotification
	{
	public:
		TaskProgressNotification(Task* pTask, f32 progress);
		inline f32 GetProgress() const{return _progress;}
	protected:
		~TaskProgressNotification();
	private:
		f32 _progress;
	};

	template<typename C>
	class TaskCustomNotification: public TaskNotification
	{
	public:
		TaskCustomNotification(Task* pTask, const C& custom):TaskNotification(pTask),_custom(custom){}
		const C& GetCustom() const{return _custom;}
	protected:
		~TaskCustomNotification(){}
	private:
		C _custom;
	};
}

#endif