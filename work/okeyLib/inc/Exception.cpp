#include "PreCom.h"
#include "Exception.h"


#ifndef WINDOWS
#include <execinfo.h>
#endif

namespace okey
{
	Exception::Exception(int32 code):pnested_(NULL),code_(code)
	{

	}

	Exception::Exception(const std::string& msg, int32 code):pnested_(NULL),message_(msg),code_(code)
	{

	}

	Exception::Exception(const std::string& msg, const std::string& args, int32 code):pnested_(NULL),message_(msg),code_(code)
	{
		if (!args.empty())
		{
			message_.append(": ");
			message_.append(args);
		}
	}

	Exception::Exception(const std::string& msg, const Exception& nest, int32 code):pnested_(nest.clone()),message_(msg),code_(code)
	{

	}

	Exception::Exception(const Exception& exc):std::exception(exc),message_(exc.message_),code_(exc.code_)
	{
		pnested_ = exc.pnested_ ? exc.pnested_->clone() : NULL;
	}

	Exception::~Exception() throw()
	{
		delete pnested_;
	}

	Exception& Exception::operator=(const Exception& exc)
	{
		if (&exc != this)
		{
			if (pnested_)
			{
				delete pnested_;
			}
			message_ = exc.message_;
			pnested_ = exc.pnested_ ? exc.pnested_->clone() : NULL;
			code_ = exc.code_;
		}
		return *this;
	}

	const char* Exception::name() const throw()
	{
		return "Exception";
	}

	const char* Exception::classname() const throw()
	{
		return typeid(*this).name();
	}

	const char* Exception::what() const throw()
	{
		return name();
	}

	std::string Exception::displayText()const
	{
		std::string txt = name();
		if (!message_.empty())
		{
			txt.append(": ");
			txt.append(message_);
		}
		return txt;
	}

	Exception* Exception::clone() const
	{
		return new Exception(*this);
	}

	void Exception::rethrow() const
	{
		throw *this;
	}

	void Exception::extendedMessage(const std::string& arg)
	{
		if (!arg.empty())
		{
			message_.append(": ");
			message_.append(arg);
		}
	}
}

