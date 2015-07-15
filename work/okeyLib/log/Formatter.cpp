#include "PreCom.h"
#include "Formatter.h"
#include "Exception.h"

namespace okey
{
	Formatter::Formatter()
	{

	}

	Formatter::~Formatter()
	{

	}

	void Formatter::SetProperty(const std::string& name, const std::string& value)
	{
		throw PropertyNotSupportedException();
	}

	std::string Formatter::GetProperty(const std::string& name) const
	{
		throw PropertyNotSupportedException();
	}
}