#include "PreCom.h"
#include "NameMutex.h"
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


	NameMutex::NameMutex(const std::string& name):_name(name)
	{
#ifdef WINDOWS
		_mutex = CreateMutex(NULL, FALSE, _name.c_str());
		if (!_mutex) 
			throw SystemException("cannot create named mutex", _name);
#else
		std::string fileName = getFileName();
		int fd = open(fileName.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd != -1)
			close(fd);
		else 
			throw SystemException("cannot create named mutex (lockfile)", _name);
		key_t key = ftok(fileName.c_str(), 0);
		if (key == -1)
			throw SystemException("cannot create named mutex (ftok() failed)", _name);
		_semid = semget(key, 1, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH | IPC_CREAT | IPC_EXCL);
		if (_semid >= 0)
		{
			union semun arg;
			arg.val = 1;
			semctl(_semid, 0, SETVAL, arg);
		}
		else if (errno == EEXIST)
		{
			_semid = semget(key, 1, 0);
		}
		else 
			throw SystemException("cannot create named mutex (semget() failed)", _name);
#endif
	}

	NameMutex::~NameMutex()
	{
#ifdef WINDOWS
		CloseHandle(_mutex);
#else
#endif
	}

	void NameMutex::lock()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_mutex, INFINITE))
		{
		case WAIT_OBJECT_0:
			return;
		case WAIT_ABANDONED:
			throw SystemException("cannot lock named mutex (abadoned)", _name);
		default:
			throw SystemException("cannot lock named mutex", _name);
		}
#else
		struct sembuf op;
		op.sem_num = 0;
		op.sem_op  = -1;
		op.sem_flg = SEM_UNDO;//失败的时候会还原之前的状态,防止异常锁住，。
		int err;
		do
		{
			err = semop(_semid, &op, 1);
		}
		while (err && errno == EINTR);
		if (err)
			throw SystemException("cannot lock named mutex", _name);
#endif
	}

	bool NameMutex::tryLock()
	{
#ifdef WINDOWS
		switch (WaitForSingleObject(_mutex, 0))
		{
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			return false;
		case WAIT_ABANDONED:
			throw SystemException("cannot lock named mutex (abadoned)", _name);
		default:
			throw SystemException("cannot lock named mutex", _name);
		}
#else
		struct sembuf op;
		op.sem_num = 0;
		op.sem_op  = -1;
		op.sem_flg = SEM_UNDO | IPC_NOWAIT;//不会阻塞
		return semop(_semid, &op, 1) == 0;
#endif
	}

	void NameMutex::unlock()
	{
#ifdef WINDOWS
		ReleaseMutex(_mutex);
#else
		struct sembuf op;
		op.sem_num = 0;
		op.sem_op  = 1;
		op.sem_flg = SEM_UNDO;
		if (semop(_semid, &op, 1) != 0)
			throw SystemException("cannot unlock named mutex", _name);
#endif
	}

#ifdef LINUX
	std::string NameMutex::getFileName()
	{
		std::string fn = "/tmp/";
		fn.append(_name);
		fn.append(".mutex");
		return fn;
	}

#endif

}