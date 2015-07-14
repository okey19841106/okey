#include "PreCom.h"
#include "StreamCopier.h"
#include "Buffer.h"

namespace okey
{
	std::streamsize StreamCopier::CopyStream(std::istream& istr, std::ostream& ostr, std::size_t bufferSize)
	{
		//assert buffersize > 0
		Buffer<char> buffer(bufferSize);
		std::streamsize len = 0;
		istr.read(buffer.GetBegin(), bufferSize);
		std::streamsize n = istr.gcount();
		while(n > 0)
		{
			len += n;
			ostr.write(buffer.GetBegin(), n);
			if (istr && ostr)
			{
				istr.read(buffer.GetBegin(), bufferSize);
				n = istr.gcount();
			}
			else
				n = 0;
		}
		return 0;
	}

	std::streamsize StreamCopier::CopyStreamUnbuffered(std::istream& istr, std::ostream& ostr)
	{
		char c;
		std::streamsize len = 0;
		istr.get(c);
		while (istr && ostr)
		{
			++len;
			ostr.put(c);
			istr.get(c);
		}
		return len;
	}


	std::streamsize StreamCopier::CopyToString(std::istream& istr, std::string& str, std::size_t bufferSize)
	{
		Buffer<char> buffer(bufferSize);
		std::streamsize len = 0;
		istr.read(buffer.GetBegin(), bufferSize);
		std::streamsize n = istr.gcount();
		while (n > 0)
		{
			len += n;
			str.append(buffer.GetBegin(), static_cast<std::string::size_type>(n));
			if (istr)
			{
				istr.read(buffer.GetBegin(), bufferSize);
				n = istr.gcount();
			}
			else n = 0;
		}
		return len;
	}

	
}