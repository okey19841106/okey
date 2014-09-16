/********************************************************************
	created:	2014/09/10
	created:	15:34
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_FILE_STREAM_H___
#define __OKEY_FILE_STREAM_H___

#include "File"
#include <iosfwd>
#include <iostream>

namespace okey
{

	class FileStream : public File, public std::streambuf, public std::iostream
	{
	public:
		FileStream();
		~FileStream();


	};


}


#endif