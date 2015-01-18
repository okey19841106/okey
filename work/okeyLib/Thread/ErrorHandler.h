/********************************************************************
	created:	2015/01/18
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef _THREAD_ERROR_HANDLER_H__
#define _THREAD_ERROR_HANDLER_H__

#include "Exception.h"
#include "Mutex.h"

namespace okey
{
	class ErrorHandler
	{
	public:
		ErrorHandler();
		~ErrorHandler();
		virtual void exception(const Exception& exc);
		virtual void exception(const std::exception& exc);
		virtual void exception();
		static void handle(const Exception& exc);
		static void handle(const std::exception& exc);
		static void handle();
		static ErrorHandler* set(ErrorHandler* pHandler);
		static ErrorHandler* get();
	protected:	
		static ErrorHandler* defaultHandler();
	private:
		static ErrorHandler* _pHandler;
		static FastMutex     _mutex;
	};

	inline ErrorHandler* ErrorHandler::get()
	{
		return _pHandler;
	}
}

#endif