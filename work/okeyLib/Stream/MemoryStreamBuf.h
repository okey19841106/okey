/********************************************************************
	created:	2014/12/23
	created:	10:16
	author:		okey
	
	purpose:	
*********************************************************************/

#ifndef __MEMORY_STREAM_BUF_H_
#define __MEMORY_STREAM_BUF_H_

#include <streambuf>
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>

namespace okey
{
	template<typename ch, typename tr>
	class TMemoryStreamBuf: public std::basic_streambuf<ch, tr>
	{
	protected:
		typedef std::basic_streambuf<ch, tr> Base;
		typedef std::basic_ios<ch, tr> IOS;
		typedef ch char_type;
		typedef tr char_traits;
		typedef typename Base::int_type int_type;
		typedef typename Base::pos_type pos_type;
		typedef typename Base::off_type off_type;
	public:
		TMemoryStreamBuf(char_type* pBuffer, std::streamsize bufsize):_pBuffer(pBuffer),_bufSize(bufsize)
		{
			this->setg(_pBuffer,_pBuffer,_pBuffer + _bufSize);
			this->setp(_pBuffer,_pBuffer+_bufSize);
		}

		~TMemoryStreamBuf()
		{

		}

		virtual int_type overflow(int_type c)
		{
			return char_traits::eof();
		}

		virtual int_type underflow()
		{
			return char_traits::eof();
		}

		virtual int sync()
		{
			return 0;
		}

		std::streamsize charsWritten() const
		{
			return static_cast<std::streamsize>(this->pptr() - this->pbase());
		}

		void reset()
		{
			this->setg(_pBuffer,_pBuffer,_pBuffer + _bufSize);
			this->setp(_pBuffer,_pBuffer+_bufSize);
		}
	private:
		char_type* _pBuffer;
		std::streamsize _bufSize;

		TMemoryStreamBuf();
		TMemoryStreamBuf(const TMemoryStreamBuf&);
		TMemoryStreamBuf& operator=(const TMemoryStreamBuf&);
	};

	typedef TMemoryStreamBuf<char, std::char_traits<char> > MemoryStreamBuf;

	class MemoryIOS: public virtual std::ios
	{
	public:
		MemoryIOS(char* pBufer, std::streamsize bufferSize);
		~MemoryIOS();
		MemoryStreamBuf* rdbuf();
	protected:
		MemoryStreamBuf	_buf;
	};

	class MemoryInputStream: public MemoryIOS, public std::istream
	{
	public:
		MemoryInputStream(const char* pBuffer, std::streamsize bufferszie);
		~MemoryInputStream();
	};

	class MemoryOutputStream: public MemoryIOS, public std::ostream
	{
	public:
		MemoryOutputStream(char* pBuffer, std::streamsize bufferszie);
		~MemoryOutputStream();
		std::streamsize charsWritten() const;
	};

	inline MemoryStreamBuf* MemoryIOS::rdbuf()
	{
		return &_buf;
	}

	inline std::streamsize MemoryOutputStream::charsWritten()const
	{
		return _buf.charsWritten();
	}
}

#endif