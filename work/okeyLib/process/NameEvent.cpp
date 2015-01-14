#include "PreCom.h"
#include "NameEvent.h"
#include "Exception.h"

namespace okey
{

#ifdef LINUX
	union semun
	{
		int                 val;
		struct semid_ds*    buf;
		unsigned short int* array;
		struct seminfo*     __buf;
	};
#endif

	NamedEvent::NamedEvent(const std::string& name):_name(name)
	{
#ifdef WINDOWS
		_event = CreateEvent(NULL, FALSE, FALSE, _name.c_str());
		if (!_event)
			throw SystemException("cannot create named event", _name);
#else
		std::string fileName = getFileName();
		int fd = open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd != -1)
			close(fd);
		else 
			throw SystemException("cannot create named event (lockfile)", _name);
		key_t key = ftok(fileName.c_str(), 0);
		if (key == -1)
			throw SystemException("cannot create named event (ftok() failed)", _name);
		_semid = semget(key, 1, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | IPC_CREAT | IPC_EXCL);
		if (_semid >= 0)
		{
			union semun arg;
			arg.val = 0;
			semctl(_semid, 0, SETVAL, arg);
		}
		else if (errno == EEXIST)
		{
			_semid = semget(key, 1, 0);
		}
		else throw SystemException("cannot create named event (semget() failed)", _name);
#endif
	}

	NamedEvent::~NamedEvent()
	{
#ifdef WINDOWS
		CloseHandle(_event);
#else
#endif
	}

	void NamedEvent::Set()
	{
#ifdef WINDOWS
		if (!SetEvent(_event))
			throw SystemException("cannot signal named event", _name);
#else
		struct sembuf op;
		op.sem_num = 0;
		op.sem_op  = 1;
		op.sem_flg = 0;
		if (semop(_semid, &op, 1) != 0)// 加1，其他进程>0的 停止阻塞。
			throw SystemException("cannot set named event", _name);
#endif
	}

	void NamedEvent::Wait()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_event, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;
		default:
			throw SystemException("wait for named event failed", _name);
		}
#else
		struct sembuf op;
		op.sem_num = 0;
		op.sem_op  = -1;
		op.sem_flg = 0;
		int err;
		do
		{
			err = semop(_semid, &op, 1); //< 0 阻塞。
		}
		while (err && errno == EINTR); 
		if (err) 
			throw SystemException("cannot wait for named event", _name);
#endif
	}

#ifdef LINUX
	std::string NamedEvent::getFileName()
	{
		std::string fn = "/tmp/";
		fn.append(_name);
		fn.append(".event");
		return fn;
	}
#endif
}