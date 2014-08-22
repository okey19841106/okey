/********************************************************************
	created:	2014/08/22
	created:	16:26
	author:		
	
	purpose:	
*********************************************************************/

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
