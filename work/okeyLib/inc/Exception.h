/********************************************************************
	created:	2014/08/22
	created:	16:26
	author:		
	
	purpose:	
*********************************************************************/

#ifndef OKEY_BASE_EXCEPTION_H
#define OKEY_BASE_EXCEPTION_H


#include <exception>
#include "Types.h"

namespace okey
{

	class Exception : public std::exception
	{
	public:
		Exception(const std::string& msg, int32 code = 0);
		Exception(const std::string& msg, const std::string& args, int32 code = 0);
		Exception(const std::string& msg, const Exception& nest, int32 code = 0);
		Exception(const Exception& exc);
		~Exception() throw();
	public:
		Exception& operator=(const Exception& exc);
	public:
		virtual const char* name() const throw();
		virtual const char* classname() const throw();
		virtual const char* what() const throw();
		inline Exception* nested() const
		{
			return pnested_;
		}
		inline const std::string& message() const
		{
			return message_;
		}
		inline int32 code() const
		{
			return code_;
		}
		std::string displayText()const;
		virtual Exception* clone() const;
		virtual void rethrow() const;
	protected:
		Exception(int32 code = 0);
		inline void message(const std::string& msg)
		{
			message_ = msg;
		}
		void extendedMessage(const std::string& arg);
	private:
		std::string message_;
		Exception* pnested_;
		int32 code_;
	};

#define OKEY_DECLARE_EXCEPTION_CODE(CLS, BASE, NAME, CODE)	\
	class CLS: public BASE	\
	{	\
	public:	\
	CLS(int32 code = CODE):BASE(code){}	\
	CLS(const std::string& msg, int32 code = CODE):BASE(msg, code){}	\
	CLS(const std::string& msg, const std::string& arg, int32 code = CODE):BASE(msg,arg,code){}	\
	CLS(const std::string& msg, const Exception& exc, int32 code=CODE):BASE(msg,exc,code){}	\
	CLS(const CLS& exc):BASE(exc){}	\
	CLS::~CLS() throw(){}	\
	CLS& CLS::operator=(const CLS& exc){BASE::operator=(exc);return *this;}	\
	const char* name()const throw(){return NAME;}	\
	const char* className()const throw(){return typeid(*this).name();}	\
	Exception* clone()const{return new CLS(*this);}	\
	void rethrow() const{throw *this;}	\
	};	\

#define OKEY_DECLARE_EXCEPTION(CLASS, BASE, NAME)	\
	OKEY_DECLARE_EXCEPTION_CODE(CLASS,BASE, NAME, 0)

OKEY_DECLARE_EXCEPTION(IOException, Exception,"I/O error");
OKEY_DECLARE_EXCEPTION(FileException, Exception, "File access error");
OKEY_DECLARE_EXCEPTION(FileAccessDeniedException, Exception, "Access to file denied");
OKEY_DECLARE_EXCEPTION(PathNotFoundException, Exception, "Path not found");
OKEY_DECLARE_EXCEPTION(FileExistsException, Exception, "File exists");
OKEY_DECLARE_EXCEPTION(PathSyntaxException, Exception, "Bad path syntax");
OKEY_DECLARE_EXCEPTION(FileReadOnlyException, Exception, "File is read-only");
OKEY_DECLARE_EXCEPTION(CreateFileException, Exception, "Cannot create file");
OKEY_DECLARE_EXCEPTION(WriteFileException, Exception, "Cannot write file");
OKEY_DECLARE_EXCEPTION(FileNotFoundException,Exception,"File not found");
OKEY_DECLARE_EXCEPTION(ReadFileException, Exception, "Cannot read file");
OKEY_DECLARE_EXCEPTION(SystemException, Exception,"System Exception");
OKEY_DECLARE_EXCEPTION(NotFoundException,Exception,"Not Find");
// OKEY_DECLARE_EXCEPTION(FileNotFoundException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(PathNotFoundException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(FileAccessDeniedException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(FileExistsException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(PathSyntaxException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(FileReadOnlyException, Exception, "Cannot read file");
// OKEY_DECLARE_EXCEPTION(ReadFileException, Exception, "Cannot read file");
}

#endif  
