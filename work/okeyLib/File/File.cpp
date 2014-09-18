#include "PreCom.h"
#include "File.h"
#include "Exception.h"
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

	void File::UnLink(const std::string& filename)
	{
#ifdef WINDOWS
		if(!DeleteFile(filename.c_str()))
		{
			File::HandleFileError(filename);
		}
#else
		if(unlink(filename.c_str()) == -1)
		{
			File::HandleFileError(filename);
		}
#endif
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
			File::HandleFileError(pername);
			return File();
		}
		IOType handle = CreateFile(tmpname, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_TEMPORARY|FILE_FLAG_DELETE_ON_CLOSE, NULL);

		if(handle == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			File::UnLink(tmpname);
			File::HandleFileError(pername);
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
			File::HandleFileError(pername);
			return f;
		}
		f.setHandle(handle);
		return f;
#endif
	}

	File::File(const File& f): m_Handle(INVALID_HANDLE_VALUE),m_FileName(f.m_FileName),
		m_accessMode(f.m_accessMode), m_openMode(f.m_openMode),
		m_createMode(f.m_createMode), m_shareMode(f.m_shareMode)
	{
#ifdef WINDOWS
		BOOL ret = DuplicateHandle(GetCurrentProcess(), f.m_Handle,
			GetCurrentProcess(), &m_Handle,
			DUPLICATE_SAME_ACCESS, TRUE, 0);
		if (!ret)
		{
			File::HandleFileError(m_FileName);
		}
#else
		m_Handle = dup(f.m_Handle);
		if (m_Handle == -1)
		{
			File::HandleFileError(m_FileName);
		}
		assert(m_handle != -1);
#endif
		
	}


	File::File(const std::string& filename, accessMode_t access, openMode_t open,createMode_t create, shareMode_t share):m_Handle(INVALID_HANDLE_VALUE)
	{
		Open(filename,access,share,open,create);
	}

	File::File()
	{
		m_Handle = INVALID_HANDLE_VALUE;
	}

	File::~File()
	{
		Close();
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
			File::HandleFileError(m_FileName);
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
		File::HandleFileError(m_FileName);
		return 0;
#endif
		
	}

	int32 File::GetPosition()
	{
		return SetPosition(0,posCurrent);
	}

	void File::Open(const std::string& filename, accessMode_t am, shareMode_t sm, openMode_t om, createMode_t cm)
	{
		if (isFileOpen())
		{
			Close();
		}
#ifdef WINDOWS
		DWORD acc;
		switch(am)
		{
		case acWrite:
			acc = GENERIC_WRITE;
			break;

		case acReadWrite:
			acc = GENERIC_READ | GENERIC_WRITE;
			break;

		case acRead:
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
			try
			{
				if(om == Append)
					SetPosition(0, posEnd);
				else if(om == Truncate)
					TruncateFile(0);
			}
			catch (...)
			{
				Close();
				throw;
			}
			return;
		}
		File::HandleFileError(filename);
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
			return;
		}
		File::HandleFileError(filename);
		return false;
#endif
	}


	void File::Close()
	{
#ifdef WINDOWS
		if(isFileOpen())

		{
			if(!CloseHandle(m_Handle))
			{
				File::HandleFileError(m_FileName);
			}
			m_Handle = INVALID_HANDLE_VALUE;
		}
#else
		if(isFileOpen())
		{
			if(close(m_Handle) != 0)
			{
				File::HandleFileError(m_FileName);
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
			File::HandleFileError(m_FileName);
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

		File::HandleFileError(m_FileName);
		return 0;
		
#endif
	}

	uint32 File::WriteBufer(const char* pBuffer, uint32 nBuffersize)
	{
#ifdef WINDOWS
		DWORD written = 0;

		if(!WriteFile(m_Handle, (void*)pBuffer, nBuffersize, &written, NULL))
		{
			File::HandleFileError(m_FileName);
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

		File::HandleFileError(m_FileName);
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
			File::HandleFileError(m_FileName,err);
		}
#else
		int ret = ftruncate(m_Handle, length);
		if(ret == 0)
		{
			seek(length, seekSet);
			return;
		}
		File::HandleFileError(m_FileName);

#endif
	}

	bool File::ReOpen()
	{
		uint32 pos = GetPosition();
		Close();
		Open(m_FileName.c_str(), m_accessMode, m_shareMode, m_openMode, m_createMode);
		SetPosition(pos, posSet);
		return true;
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
			File::HandleFileError(m_FileName);
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
		{	
			File::HandleFileError(m_FileName);
		}
		return;

#else
		int ret = fsync(m_Handle);
		if(ret != -1)
			return;

		if(errno == EINVAL)
			return;

		File::HandleFileError(m_FileName);
#endif
	}

	bool File::GetFileInfo(const std::string& filename, FileInfo* pFileInfo)
	{
		return false;
	}

	

	void File::HandleFileError(const std::string filename)
	{
#ifdef WINDOWS
		DWORD err = GetLastError();
		switch (err)
		{
		case ERROR_FILE_NOT_FOUND:
			throw FileNotFoundException(filename, err);
		case ERROR_PATH_NOT_FOUND:
		case ERROR_BAD_NETPATH:
		case ERROR_CANT_RESOLVE_FILENAME:
		case ERROR_INVALID_DRIVE:
			throw PathNotFoundException(filename, err);
		case ERROR_ACCESS_DENIED:
			throw FileAccessDeniedException(filename, err);
		case ERROR_ALREADY_EXISTS:
		case ERROR_FILE_EXISTS:
			throw FileExistsException(filename, err);
		case ERROR_INVALID_NAME:
		case ERROR_DIRECTORY:
		case ERROR_FILENAME_EXCED_RANGE:
		case ERROR_BAD_PATHNAME:
			throw PathSyntaxException(filename, err);
		case ERROR_FILE_READ_ONLY:
			throw FileReadOnlyException(filename, err);
		case ERROR_CANNOT_MAKE:
			throw CreateFileException(filename, err);
		case ERROR_DIR_NOT_EMPTY:
			throw FileException("directory not empty", filename, err);
		case ERROR_WRITE_FAULT:
			throw WriteFileException(filename, err);
		case ERROR_READ_FAULT:
			throw ReadFileException(filename, err);
		case ERROR_SHARING_VIOLATION:
			throw FileException("sharing violation", filename, err);
		case ERROR_LOCK_VIOLATION:
			throw FileException("lock violation", filename, err);
		case ERROR_HANDLE_EOF:
			throw ReadFileException("EOF reached", filename, err);
		case ERROR_HANDLE_DISK_FULL:
		case ERROR_DISK_FULL:
			throw WriteFileException("disk is full", filename, err);
		case ERROR_NEGATIVE_SEEK:
			throw FileException("negative seek", filename, err);
		default:
			throw FileException(filename, err);
		}
#else
		switch (errno)
		{
		case EIO:
			throw IOException(path, errno);
		case EPERM:
			throw FileAccessDeniedException("insufficient permissions", path, errno);
		case EACCES:
			throw FileAccessDeniedException(path, errno);
		case ENOENT:
			throw FileNotFoundException(path, errno);
		case ENOTDIR:
			throw OpenFileException("not a directory", path, errno);
		case EISDIR:
			throw OpenFileException("not a file", path, errno);
		case EROFS:
			throw FileReadOnlyException(path, errno);
		case EEXIST:
			throw FileExistsException(path, errno);
		case ENOSPC:
			throw FileException("no space left on device", path, errno);
		case EDQUOT:
			throw FileException("disk quota exceeded", path, errno);
#if !defined(_AIX)
		case ENOTEMPTY:
			throw FileException("directory not empty", path, errno);
#endif
		case ENAMETOOLONG:
			throw PathSyntaxException(path, errno);
		case ENFILE:
		case EMFILE:
			throw FileException("too many open files", path, errno);
		default:
			throw FileException(std::strerror(errno), path, errno);
		}
#endif
	}

	void File::HandleFileError(const std::string filename, int32 err)
	{
#ifdef WINDOWS
		switch (err)
		{
		case ERROR_FILE_NOT_FOUND:
			throw FileNotFoundException(filename, err);
		case ERROR_PATH_NOT_FOUND:
		case ERROR_BAD_NETPATH:
		case ERROR_CANT_RESOLVE_FILENAME:
		case ERROR_INVALID_DRIVE:
			throw PathNotFoundException(filename, err);
		case ERROR_ACCESS_DENIED:
			throw FileAccessDeniedException(filename, err);
		case ERROR_ALREADY_EXISTS:
		case ERROR_FILE_EXISTS:
			throw FileExistsException(filename, err);
		case ERROR_INVALID_NAME:
		case ERROR_DIRECTORY:
		case ERROR_FILENAME_EXCED_RANGE:
		case ERROR_BAD_PATHNAME:
			throw PathSyntaxException(filename, err);
		case ERROR_FILE_READ_ONLY:
			throw FileReadOnlyException(filename, err);
		case ERROR_CANNOT_MAKE:
			throw CreateFileException(filename, err);
		case ERROR_DIR_NOT_EMPTY:
			throw FileException("directory not empty", filename, err);
		case ERROR_WRITE_FAULT:
			throw WriteFileException(filename, err);
		case ERROR_READ_FAULT:
			throw ReadFileException(filename, err);
		case ERROR_SHARING_VIOLATION:
			throw FileException("sharing violation", filename, err);
		case ERROR_LOCK_VIOLATION:
			throw FileException("lock violation", filename, err);
		case ERROR_HANDLE_EOF:
			throw ReadFileException("EOF reached", filename, err);
		case ERROR_HANDLE_DISK_FULL:
		case ERROR_DISK_FULL:
			throw WriteFileException("disk is full", filename, err);
		case ERROR_NEGATIVE_SEEK:
			throw FileException("negative seek", filename, err);
		default:
			throw FileException(filename, err);
		}
#else
		switch (err)
		{
		case EIO:
			throw IOException(path, errno);
		case EPERM:
			throw FileAccessDeniedException("insufficient permissions", path, errno);
		case EACCES:
			throw FileAccessDeniedException(path, errno);
		case ENOENT:
			throw FileNotFoundException(path, errno);
		case ENOTDIR:
			throw OpenFileException("not a directory", path, errno);
		case EISDIR:
			throw OpenFileException("not a file", path, errno);
		case EROFS:
			throw FileReadOnlyException(path, errno);
		case EEXIST:
			throw FileExistsException(path, errno);
		case ENOSPC:
			throw FileException("no space left on device", path, errno);
		case EDQUOT:
			throw FileException("disk quota exceeded", path, errno);
#if !defined(_AIX)
		case ENOTEMPTY:
			throw FileException("directory not empty", path, errno);
#endif
		case ENAMETOOLONG:
			throw PathSyntaxException(path, errno);
		case ENFILE:
		case EMFILE:
			throw FileException("too many open files", path, errno);
		default:
			throw FileException(std::strerror(errno), path, errno);
		}
#endif
	}
}