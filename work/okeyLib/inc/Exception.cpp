//////////////////////////////////////////////////////////////
//                    .----.
//                 _.'__    `.
//             .--(#)(##)---/#\
//           .' @          /###\
//           :       ,     #####
//            `-..__.-' _.-\###/ 
//                   `;_:   `"'
//                 .'"""""`.
//                /,        ,\
//               //          \\
//               `-._______.-'
//              ___`. | .'___
//             (______|______)
//
//  created:	2011-9-4 
//  owner:      OKEY
///////////////////////////////////////////////////////////////////////////////

#include "PreCom.h"
#include "Exception.h"

//#include <cxxabi.h>
#ifndef WINDOWS
#include <execinfo.h>
#endif

#include <stdlib.h>

namespace okey
{



Exception::Exception(const char* msg)
  : message_(msg)
{
  fillStackTrace();
}

Exception::Exception(const std::string& msg)
  : message_(msg)
{
  fillStackTrace();
}

Exception::~Exception() throw ()
{
}

const char* Exception::what() const throw()
{
  return message_.c_str();
}

const char* Exception::stackTrace() const throw()
{
  return stack_.c_str();
}

void Exception::fillStackTrace()
{
#ifndef WINDOWS
	const int32 len = 200;
	void* buffer[len];
	int32 nptrs = ::backtrace(buffer, len);
	char** strings = ::backtrace_symbols(buffer, nptrs);
	if (strings)
	{
		for (int32 i = 0; i < nptrs; ++i)
		{
			// TODO demangle funcion name with abi::__cxa_demangle
			stack_.append(strings[i]);
			stack_.push_back('\n');
		}
		free(strings);
	}
#endif
}

}

