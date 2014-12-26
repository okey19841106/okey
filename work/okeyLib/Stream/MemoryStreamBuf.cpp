#include "PreCom.h"
#include "MemoryStreamBuf.h"

namespace okey
{
	MemoryIOS::MemoryIOS(char* pBufer, std::streamsize bufferSize):_buf(pBufer, bufferSize)
	{

	}

	MemoryIOS::~MemoryIOS()
	{

	}

	MemoryInputStream::MemoryInputStream(const char* pBuffer, std::streamsize bufferSize): 
	MemoryIOS(const_cast<char*>(pBuffer), bufferSize), 	std::istream(&_buf)
	{
	}


	MemoryInputStream::~MemoryInputStream()
	{
	}


	MemoryOutputStream::MemoryOutputStream(char* pBuffer, std::streamsize bufferszie): 
	MemoryIOS(pBuffer, bufferszie), std::ostream(&_buf)
	{
	}


	MemoryOutputStream::~MemoryOutputStream()
	{
	}

}