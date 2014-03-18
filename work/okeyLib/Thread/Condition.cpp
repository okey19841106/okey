//////////////////////////////////////////////////////////////
//                      .----.
//                   _.'__    `.
//             .--(#)(##)---/#\
//           .' @            /###\
//           :         ,       #####
//            `-..__.-' _.-  \###/ 
//                   `;_:         `"'
//                 .'"""""`.
//                /,         ,\
//               //           \\
//               `-._______.-'
//                ___`. | .'___
//             (______|______)
//
//  created:	2011-9-2 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////
#include "PreCom.h"
#include "Condition.h"
#include "Mutex.h"

namespace okey{

Condition::Condition()
{
#ifdef WINDOWS
	SECURITY_ATTRIBUTES attr;
	attr.nLength = sizeof(SECURITY_ATTRIBUTES);
	attr.lpSecurityDescriptor = NULL;
	attr.bInheritHandle = FALSE;
	m_EventOne		= ::CreateEvent(&attr, FALSE, FALSE, NULL); 
	m_EventAll		= ::CreateEvent(&attr, TRUE, FALSE, NULL); 
#else
	pthread_cond_init(&pcond_, NULL);
#endif
	
}

Condition::~Condition()
{
#ifdef WINDOWS
	::CloseHandle(m_EventOne); 
	::CloseHandle(m_EventAll); 
#else
	pthread_cond_destroy(&pcond_);
#endif
	
}

void Condition::wait(Mutex& mutex_)
{
#ifdef WINDOWS
	mutex_.UnLock();
	HANDLE eve[] = {m_EventOne, m_EventAll};
	::WaitForMultipleObjects(2, eve, FALSE, INFINITE);
	mutex_.Lock();
#else
	pthread_cond_wait(&pcond_, mutex_.getPthreadMutex());
#endif
	
}

void Condition::signal()
{
#ifdef WINDOWS
	::SetEvent(m_EventOne);
#else
	pthread_cond_signal(&pcond_);
#endif
	
}

void Condition::broadcast()
{
#ifdef WINDOWS
	::SetEvent(m_EventAll);
	::ResetEvent(m_EventAll);
#else
	pthread_cond_broadcast(&pcond_);
#endif
	
}

}