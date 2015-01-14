/********************************************************************
	created:	2015/01/14
	created:	15:44
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_NAME_EVENT_H__
#define __OKEY_NAME_EVENT_H__


namespace okey
{
	class  NamedEvent
	{
	public:
		NamedEvent(const std::string& name);
		~NamedEvent();
		void Set();
		void Wait();
	private:
		NamedEvent();
		NamedEvent(const NamedEvent&);
		NamedEvent& operator = (const NamedEvent&);


		std::string _name;
#ifdef WINDOWS
		HANDLE      _event;	
#else
		std::string getFileName();
		int _lockfd; // lock file descriptor
		int _semfd;  // file used to identify semaphore
		int _semid;  // semaphore id
#endif
	};
}

#endif