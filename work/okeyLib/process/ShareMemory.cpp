#include "PreCom.h"
#include "ShareMemory.h"
#include "Exception.h"
#include "File/FileInfo.h"

namespace okey
{
	ProcessShareMemory::ProcessShareMemory(const std::string& name, std::size_t size, ShareMemory_AccessMode mode, const void* addrHint, bool server):
	_name(name),
	_size(size),
	_address(0),
#ifdef WINDOWS
	_mode(PAGE_READONLY),
	_memHandle(INVALID_HANDLE_VALUE),
	_fileHandle(INVALID_HANDLE_VALUE)
#else
	_fd(-1),
	_access(mode),
	_name("/"),
	_fileMapped(false),
	_server(server)
#endif
	{
#ifdef WINDOWS
		if (mode == AM_WRITE)
			_mode = PAGE_READWRITE;
		_memHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, _mode, 0, static_cast<DWORD>(_size), _name.c_str());
		if (!_memHandle)
			throw SystemException("Cannot create shared memory object", _name);

		map();
#else
		_name.append(name);
		int flags = _server ? O_CREAT : 0;
		if (_access == SharedMemory::AM_WRITE)
			flags |= O_RDWR;
		else
			flags |= O_RDONLY;

		// open the shared memory segment
		_fd = ::shm_open(_name.c_str(), flags, S_IRUSR | S_IWUSR);
		if (_fd == -1)
			throw SystemException("Cannot create shared memory object", _name);
		// now set the correct size for the segment
		if (_server && -1 == ::ftruncate(_fd, size))
		{
			::close(_fd);
			_fd = -1;
			::shm_unlink(_name.c_str());
			throw SystemException("Cannot resize shared memory object", _name);
		}
		map(addrHint);
#endif
	}

	ProcessShareMemory::~ProcessShareMemory()
	{
		unmap();
		close();
	}

	
#ifdef WINDOWS
	void ProcessShareMemory::map()
	{
		DWORD access = FILE_MAP_READ;
		if (_mode == PAGE_READWRITE)
			access = FILE_MAP_WRITE;//¿ÉÐ´¿É¶Á¡£
		LPVOID addr = MapViewOfFile(_memHandle, access, 0, 0, _size);
		if (!addr)
			throw SystemException("Cannot map shared memory object", _name);
		_address = static_cast<char*>(addr);
	}
#else
	void ProcessShareMemory::map(const void* addrHint)
	{
		int access = PROT_READ;
		if (_access == SharedMemory::AM_WRITE)
			access |= PROT_WRITE;

		void* addr = ::mmap(const_cast<void*>(addrHint), _size, access, MAP_SHARED, _fd, 0);
		if (addr == MAP_FAILED)
			throw SystemException("Cannot map file into shared memory", _name);
		_address = static_cast<char*>(addr);
	}
#endif
	

	void ProcessShareMemory::unmap()
	{
#ifdef WINDOWS
		if (_address)
		{
			UnmapViewOfFile(_address);
			_address = 0;
			return;
		}
#else
		if (_address)
		{
			::munmap(_address, _size);
		}
#endif
	}

	void ProcessShareMemory::close()
	{
#ifdef WINDOWS
		if (_memHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_memHandle);
			_memHandle = INVALID_HANDLE_VALUE;
		}
		if (_fileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(_fileHandle);
			_fileHandle = INVALID_HANDLE_VALUE;
		}
#else
		if (_fd != -1)
		{
			::close(_fd);
			_fd = -1;
		}
		if (!_fileMapped && _server)
		{
			::shm_unlink(_name.c_str());
		}
#endif
	}

	ProcessShareMemory::ProcessShareMemory(const FileInfo& file, ShareMemory_AccessMode mode, const void* addrHint):
	_size(0),
		_address(0),
		_name(file.GetPath()),
#ifdef WINDOWS
		_memHandle(INVALID_HANDLE_VALUE),
		_fileHandle(INVALID_HANDLE_VALUE),
		_mode(PAGE_READONLY)
	
#else
		_fd(-1),
		_access(mode),
		_fileMapped(true),
		_server(false)
#endif
	{
		if (!file.IsExisted() || !file.IsFile())
			throw FileNotFoundException(file.GetPath());
		_size = file.GetSize();
#ifdef WINDOWS
		DWORD shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
		DWORD fileMode  = GENERIC_READ;
		if (mode == AM_WRITE)
		{
			_mode = PAGE_READWRITE;
			fileMode |= GENERIC_WRITE;
		}
		_fileHandle = CreateFile(_name.c_str(), fileMode, shareMode, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (_fileHandle == INVALID_HANDLE_VALUE)
			throw OpenFileException("Cannot open memory mapped file", _name);
		_memHandle = CreateFileMapping(_fileHandle, NULL, _mode, 0, 0, NULL);
		if (!_memHandle)
		{
			CloseHandle(_fileHandle);
			_fileHandle = INVALID_HANDLE_VALUE;
			throw SystemException("Cannot map file into shared memory", _name);
		}
		map();
#else
		int flag = O_RDONLY;
		if (mode == SharedMemory::AM_WRITE)
			flag = O_RDWR;
		_fd = ::open(_name.c_str(), flag);
		if (-1 == _fd)
			throw OpenFileException("Cannot open memory mapped file", _name);
		map(addrHint);
#endif
	}

	SharedMemory::SharedMemory():_pImpl(NULL)
	{

	}
	SharedMemory::SharedMemory(const std::string& name, std::size_t size, ShareMemory_AccessMode mode, const void* addrHint, bool server):
	_pImpl(new ProcessShareMemory(name,size,mode,addrHint,server))
	{

	}

	SharedMemory::SharedMemory(const FileInfo& file, ShareMemory_AccessMode mode, const void* addrHint):
	_pImpl(new ProcessShareMemory(file,mode,addrHint))
	{

	}

	SharedMemory::SharedMemory(const SharedMemory& other):
	_pImpl(other._pImpl)
	{
		if (_pImpl)
			_pImpl->AddRef();
	}

	SharedMemory::~SharedMemory()
	{
		if (_pImpl)
			_pImpl->DecRef();
	}

	SharedMemory& SharedMemory::operator = (const SharedMemory& other)
	{
		SharedMemory tmp(other);
		swap(tmp);
		return *this;
	}
}