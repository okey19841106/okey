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

#ifndef OKEY_BASE_EXCEPTION_H
#define OKEY_BASE_EXCEPTION_H

#include "Types.h"
#include <exception>
#include <string>

namespace okey
{

	class Exception : public std::exception
	{
	 public:
	  explicit Exception(const char* what);
	  explicit Exception(const std::string& what);
	  virtual ~Exception() throw();
	  virtual const char* what() const throw();
	  const char* stackTrace() const throw();

	 private:
	  void fillStackTrace();

	  std::string message_;
	  std::string stack_;
	};

}

#endif  // MUDUO_BASE_EXCEPTION_H
