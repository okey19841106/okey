
#include "PreCom.h"
#include "FileStream.h"
#include <iosfwd>


namespace okey
{

#define _STREAM_BUFF_SIZE_ 4096
	FileStream::FileStream():std::streambuf(), std::iostream((std::streambuf*)this),
		m_bufsize(1), m_gbuf(NULL), m_pbuf(NULL)
	{

		allocate(_STREAM_BUFF_SIZE_);
	}

	FileStream::~FileStream()
	{
		try
		{
			sync();
			if(m_bufsize > 1)
			{
				delete[] m_gbuf;
				delete[] m_pbuf;
				m_gbuf = m_pbuf = 0;
				m_bufsize = 0;
			}
			clear();
			Close();
		}
		catch(...)
		{
			
		}
	}
	FileStream::FileStream(const std::string& path, accessMode_t access, 
		openMode_t open,createMode_t create, shareMode_t share):File(path,access,open,create,share),
		std::streambuf(), std::iostream((std::streambuf*)this),
		m_bufsize(1), m_gbuf(NULL), m_pbuf(NULL)
	{
		allocate(_STREAM_BUFF_SIZE_);
	}

	FileStream::FileStream(const FileStream& fs):File(fs),std::streambuf(), std::iostream((std::streambuf*)this),
		m_bufsize(1), m_gbuf(NULL), m_pbuf(NULL)
	{
		allocate(_STREAM_BUFF_SIZE_);
	}

	FileStream::FileStream(const File& f):File(f),std::streambuf(), std::iostream((std::streambuf*)this),
		m_bufsize(1), m_gbuf(NULL), m_pbuf(NULL)
	{
		allocate(_STREAM_BUFF_SIZE_);
	}


	int FileStream::sync()
	{
		overflow(EOF);
		setg(m_gbuf, m_gbuf + m_bufsize, m_gbuf + m_bufsize);
		return 0;
	}


	int FileStream::uflow()
	{
		int ret = underflow();
		if(ret != EOF)
		{
			if(m_bufsize != 1)
				gbump(1);
		}

		return ret;
	}

	int FileStream::underflow()
	{
		unsigned int rlen;

		if(m_bufsize == 1)
		{
			unsigned char ch;
			try
			{
				rlen = ReadBuffer((char*)&ch, 1);
			}
			catch(...)
			{
				clear(std::ios::failbit | rdstate());
				return EOF;
			}

			if(rlen == 1)
				return ch;

			return EOF;
		}

		if(!gptr())
			return EOF;

		if(gptr() < egptr())
			return (unsigned char) *gptr();

		rlen = (m_gbuf + m_bufsize) - eback();

		try
		{
			rlen = ReadBuffer((char*)eback(), rlen);
			if(rlen > 0)
			{
				setg(eback(), eback(), eback() + rlen);
				return (unsigned char) *gptr();
			}
		}
		catch(...)
		{
			clear(std::ios::failbit | rdstate());
		}

		return EOF;
	}

	int FileStream::overflow(int c)
	{
		unsigned int wlen = 0;

		if(m_bufsize == 1)
		{
			if(c == EOF)
				return 0;

			unsigned char ch = (unsigned char)(c);
			try
			{
				wlen = WriteBufer((const char*)&ch, 1);
				if(wlen == 1)
					return c;
			}
			catch(...)
			{
				clear(std::ios::failbit | rdstate());
			}

			return EOF;
		}

		if(!pbase())
			return EOF;

		unsigned int req = pptr() - pbase();
		if(req)
		{
			try
			{
				wlen = WriteBufer((const char*)pbase(), req);
			}
			catch(...)
			{
				clear(std::ios::failbit | rdstate());
				return EOF;
			}

			if(wlen == 0)
				return EOF;

			req -= wlen;
		}

		if(req)
			memmove(m_pbuf, pptr() + wlen, req);

		setp(m_pbuf, m_pbuf + m_bufsize);
		pbump(req);

		if(c != EOF)
		{
			*pptr() = (unsigned char)c;
			pbump(1);
		}

		return c;
	}


	void FileStream::allocate(unsigned int size)
	{
		sync();
		if(size < 2)
		{
			m_bufsize = 1;
			m_gbuf = m_pbuf = 0;
			return;
		}
		m_gbuf = new char[size];
		m_pbuf = new char[size];
		m_bufsize = size;
		clear();
		setg(m_gbuf, m_gbuf + size, m_gbuf + size);
		setp(m_pbuf, m_pbuf + size);
	}

}