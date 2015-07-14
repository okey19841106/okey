/********************************************************************
	created:	2015/07/14
	created:	14:13
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __STREAM_COPIER_H__
#define __STREAM_COPIER_H__

#include <istream>
#include <ostream>

namespace okey
{
	class StreamCopier
	{
	public:
		static std::streamsize CopyStream(std::istream& istr, std::ostream& ostr, std::size_t bufferSize = 8192);
		
		static std::streamsize CopyStreamUnbuffered(std::istream& istr, std::ostream& ostr);
		
		static std::streamsize CopyToString(std::istream& istr, std::string& str, std::size_t bufferSize = 8192);
		
	};
}

#endif