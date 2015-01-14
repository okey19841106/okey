/********************************************************************
	created:	2015/01/14
	created:	16:07
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_NAME_MUTEX_H__
#define __OKEY_NAME_MUTEX_H__



namespace okey
{
	class NameMutex
	{
		NameMutex(const std::string& name);
		~NameMutex();

		void lock();
		bool tryLock();
		void unlock();

	private:
		NameMutex();
		NameMutex(const NameMutex&);
		NameMutex& operator = (const NameMutex&);
	private:
		std::string _name;
#ifdef WINDOWS
		HANDLE      _mutex;	
#else
		std::string getFileName();
		int _lockfd; // lock file descriptor
		int _semfd;  // file used to identify semaphore
		int _semid;  // semaphore id
#endif
	};
}


#endif