#include "PreCom.h"
#include "Semaph.h"
#include "log/Logger.h"
#include "HelperFunction.h"


#ifdef WINDOWS
#include <limits>
#endif


namespace okey
{

	Semaph* g_pMsgQueueSemaph = new Semaph;
#ifdef LINUX
	Semaph* g_pAsyncOperationQueueSemaph = new Semaph;
#endif

#ifdef WINDOWS
	Semaph::Semaph()
	{
		//the initial value of the semaphore is 0
		m_Sem = CreateSemaphore(
			NULL,
			0,
			(std::numeric_limits<long>::max)(),
			NULL
			);
		if ( NULL == m_Sem )
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed CreateSemaphore(), " << FormatErrorMessage( GetLastError() ) );
		}
	}

	Semaph::~Semaph()
	{
		CloseHandle( m_Sem );
	}

	void Semaph::Post()
	{
		if( 0 == ReleaseSemaphore(
			m_Sem,
			1,
			NULL
			)
			)
		{
			LOG_ERROR( logger, __FUNCTION__ << " failed ReleaseSemaphore(), " << FormatErrorMessage( GetLastError() ) );
		}
	}

	void Semaph::Wait()
	{
		WaitForSingleObject( m_Sem, INFINITE );
	}

	int32 Semaph::TryWait()
	{
		return WaitForSingleObject( m_Sem, 0 );
	}
#else
	Semaph::Semaph()
		: m_pSem( new sem_t )
	{
		//the initial value of the semaphore is 0
		sem_init( m_pSem, 0, 0 );
	}

	Semaph::~Semaph()
	{
		sem_destroy( m_pSem );
	}

	void Semaph::Post()
	{
		sem_post( m_pSem );
	}

	void Semaph::Wait()
	{
		sem_wait( m_pSem );
	}

	int32 Semaph::TryWait()
	{
		return sem_trywait( m_pSem );
	}
#endif
	

}
