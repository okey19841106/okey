#include "PreCom.h"
#include "File.h"
#ifdef WINDOWS
#include <windows.h>
#include <shlwapi.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#endif

namespace okey
{

	bool File::IsFileExist(const std::string& filename)
	{
#ifdef WINDOWS
		return PathFileExists(filename.c_str()) ? true : false;
#else
		return access(path, F_OK) ? false : true;
#endif
	}

	bool File::UnLink(const std::string& filename)
	{
#ifdef WINDOWS
		if(!DeleteFile(filename.c_str()))
		{
			//GetLastError();
			return false;
		}
#else
		if(unlink(filename.c_str()) == -1)
		{
			//errno..
			return false;
		}
#endif
		return true;
	}

	File File::CreateTmpFile(const std::string& pername)
	{
#ifdef WINDOWS
		char tmpdir[MAX_PATH+1];
		char tmpname[MAX_PATH+1];

		GetTempPath(MAX_PATH, tmpdir);
		UINT ret = GetTempFileName(tmpdir, pername.c_str(), 0, tmpname);
		if(ret == 0)
		{
			//assert(); GetLastError;
			return File();
		}
		IOType handle = CreateFile(tmpname, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_DELETE_ON_CLOSE, NULL);

		if(handle == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			File::UnLink(tmpname);
			//assert(); GetLastError;
			return File();
		}

		File f;
		f.setHandle(handle);
		return f;
#else
		std::string temname = pername + ".tmp";
		IOType handle = ::mkstemp(temname.c_str());
		File f;
		if(handle == -1)
		{
			//assert(errno);
			return f;
		}
		f.setHandle(handle);
		return f;
#endif
	}

	File::File(const File& f): m_FileName(f.m_FileName),
		m_accessMode(f.m_accessMode), m_openMode(f.m_openMode),
		m_createMode(f.m_createMode), m_shareMode(f.m_shareMode)
	{
#ifdef WINDOWS
		BOOL ret = DuplicateHandle(GetCurrentProcess(), f.m_Handle,
			GetCurrentProcess(), &m_Handle,
			DUPLICATE_SAME_ACCESS, TRUE, 0);
		//assert(ret);
#else
		m_Handle = dup(f.m_Handle);
		assert(m_handle != -1);
			//throw IOError(errno, "Could not duplicate file descriptor", P_SOURCEINFO);
#endif
		
	}


	File::File(const std::string& filename, accessMode_t access, openMode_t open,createMode_t create, shareMode_t share)
	{
		Open(filename,access,share,open,create);
	}

	File::File()
	{
		m_Handle = INVALID_HANDLE_VALUE;
	}

	int32 File::SetPosition(int32 lPos, posMode_t pmod)
	{
		if (m_Handle == INVALID_HANDLE_VALUE)
		{
			//assert();
			return 0;
		}
#ifdef WINDOWS
		DWORD whence;
		switch(pmod)
		{
		case posSet:
			whence = FILE_BEGIN;
			break;

		case posCurrent:
			whence = FILE_CURRENT;
			break;

		case posEnd:
			whence = FILE_END;
			break;
		}
		DWORD ret = SetFilePointer(m_Handle, lPos, NULL, whence);
		if(ret == INVALID_SET_FILE_POINTER)
		{
			//assert GetLastError;
			return 0;
		}
		return ret;
#else
		int whence;
		switch(mode)
		{
		case posSet:
			whence = SEEK_SET;
			break;

		case posCurrent:
			whence = SEEK_CUR;
			break;

		case posEnd:
			whence = SEEK_END;
			break;
		}

_seek:
		off_t ret = lseek(m_Handle, lPos, whence);
		if(ret != -1)
			return ret;
		if(errno == EINTR)
			goto _seek;
		//assert(); errno
		return 0;
#endif
		
	}

	int32 File::GetPosition()
	{
		return SetPosition(0,posCurrent);
	}

	bool File::Open(const std::string& filename, accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm)
	{
		if (isFileOpen())
		{
			Close();
		}
#ifdef WINDOWS
		DWORD acc;
		switch(am)
		{
		case accessMode_t::acWrite:
			acc = GENERIC_WRITE;
			break;

		case accessMode_t::acReadWrite:
			acc = GENERIC_READ | GENERIC_WRITE;
			break;

		case accessMode_t::acRead:
		default:
			acc = GENERIC_READ;
			break;
		}

		DWORD create;
		switch(cm)
		{
		case OpenCreate:
			create = OPEN_ALWAYS;
			break;

		case CreateFail:
			create = CREATE_NEW;
			break;

		case OpenExisting:
		default:
			create = OPEN_EXISTING;
			break;
		}

		DWORD share;
		switch(sm)
		{
		case AllowNone:
			share = 0;
			break;

		case AllowRead:
			share = FILE_SHARE_READ;
			break;

		case AllowWrite:
			share = FILE_SHARE_WRITE;
			break;

		case AllowReadWrite:
			share = FILE_SHARE_READ|FILE_SHARE_WRITE;
			break;
		}

		IOType handle = CreateFile(filename.c_str(), acc, share, NULL, create, 0, NULL);
		if(handle != INVALID_HANDLE_VALUE)
		{
			m_FileName     = filename;
			m_accessMode = am;
			m_openMode   = om;
			m_createMode = cm;
			m_shareMode  = sm;
			setHandle(handle);
			if(om == Append)
				SetPosition(0, posEnd);
			else if(om == Truncate)
				TruncateFile(0);
			return true;
		}
		return false;
#else
		int flags = 0;
		switch(am)
		{
		case acWrite:
			flags |= O_WRONLY;
			break;

		case acReadWrite:
			flags |= O_RDWR;
			break;

		case acRead:
		default:
			flags |= O_RDONLY;
			break;
		}

		switch(om)
		{
		case Append:
			flags |= O_APPEND;
			break;

		case Truncate:
			flags |= O_TRUNC;
			break;

		case Normal:
		default:
			break;
		}

		switch(cm)
		{
		case OpenCreate:
			flags |= O_CREAT;
			break;

		case CreateFail:
			flags |= O_CREAT | O_EXCL;
			break;

		case OpenExisting:
		default:
			break;
		}

		IOType handle = open(path, flags, 0644);
		if(handle != -1)
		{
			m_path       = path;
			m_accessMode = am;
			m_openMode   = om;
			m_createMode = cm;
			m_shareMode  = sm;
			setHandle(handle);
			return true;
		}
		return false;
#endif
	}

	bool File::ReadLine(char* buffer, int32 len)
	{

	}

	bool File::IsEnd()
	{
		
	}

	void File::Close()
	{
#ifdef WINDOWS
		if(isFileOpen())

		{
			if(!CloseHandle(m_Handle))
			{
				//assert getlassterror;

			}
				//throw IOError(GetLastError(), "Could not close handle", P_SOURCEINFO);

			m_Handle = INVALID_HANDLE_VALUE;
		}
#else
		if(isFileOpen())
		{
			if(close(m_Handle) != 0)
			{
				//assert() errno;
			}	
			m_handle = INVALID_HANDLE_VALUE;
		}
#endif
		
	}
	uint32 File::ReadBuffer(char* pBuffer, uint32 nBufferSize)
	{
#ifdef WINDOWS
		DWORD read;
		if(!ReadFile(m_Handle, (void*)pBuffer, nBufferSize, &read, NULL))
		{
			//assert; GetLastError;
		}
		return (uint32)read;
#else
_read:
		ssize_t ret = ::read(m_Handle, pBuffer, nBufferSize);
		if(ret != -1)
			return ret;

		if(errno == EAGAIN)
			return 0;
		else if(errno == EINTR)
			goto _read;

		//assert(); errno;
		return 0;
		
#endif
	}

	uint32 File::WriteBufer(const char* pBuffer, uint32 nBuffersize)
	{
#ifdef WINDOWS
		DWORD written = 0;

		if(!WriteFile(m_Handle, (void*)pBuffer, nBuffersize, &written, NULL))
		{
			//assert GetLastError();
		}
		return (uint32)written; //实际写入字节。
#else
_write:
		ssize_t ret = ::write(m_Handle, pBuffer, nBuffersize);
		if(ret != -1)
			return ret;
		if(errno == EAGAIN)
			return 0;
		else if(errno == EINTR)
			goto _write;

		//assert errno;
		return 0;
#endif
		
	}

	void File::TruncateFile(uint32 length)
	{
		//assert(IsFileOpen())
#ifdef WINDOWS
		int32 pos = GetPosition();
		SetPosition(length, posSet);

		if(!SetEndOfFile(m_Handle))
		{
			DWORD err = GetLastError();
			SetPosition(pos, posSet);
			//log？ assert？
		}
#else
		int ret = ftruncate(m_Handle, length);
		if(ret == 0)
		{
			seek(length, seekSet);
			return;
		}

		//log? assert?//

#endif
	}

	bool File::ReOpen()
	{
		uint32 pos = GetPosition();
		Close();
		Open(m_FileName.c_str(), m_accessMode, m_shareMode, m_openMode, m_createMode);
		SetPosition(pos, posSet);
	}

	uint32 File::PeekFile(char* pBuff, uint32 len)
	{
		uint32 ret = ReadBuffer(pBuff, len);
		if(ret > 0)
			SetPosition(-((int32)ret), posCurrent);
		return ret;
	}
	uint32 File::GetFileSize()
	{
#ifdef WINDOWS
		DWORD sz = ::GetFileSize(m_Handle, NULL);
		if(sz == INVALID_FILE_SIZE)
		{
			//assert()
		}
		return (uint32)sz;
#else
		struct stat stb;
		int ret = fstat(handle(), &stb);
		if(ret == 0)
			return (uint32)stb.st_size;
		//assert()
		return 0;
#endif
	}

	void File::SyncFile()
	{
#if WINDOWS
		if(!FlushFileBuffers(m_Handle))
		{	//assert()
		}
		return;

#else
		int ret = fsync(m_Handle);
		if(ret != -1)
			return;

		if(errno == EINVAL)
			return;

		//assert()
#endif
	}

	bool File::GetFileInfo(const std::string& filename, FileInfo* pFileInfo)
	{
		return false;
	}
}