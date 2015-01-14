/********************************************************************
	created:	2015/01/14
	created:	17:19
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __SHARE_MEMORY_H__
#define __SHARE_MEMORY_H__

#include "CRefcounter.h"

namespace okey
{
	enum ShareMemory_AccessMode
	{
		AM_READ = 0,
		AM_WRITE
	};

	class FileInfo;

	class ProcessShareMemory : public CRefCounter
	{
	public:
		ProcessShareMemory(const std::string& name, std::size_t size, ShareMemory_AccessMode mode, const void* addrHint, bool server);
		char* begin() const{return _address;}
		char* end() const{return _address + _size;}
		ProcessShareMemory(const FileInfo& file, ShareMemory_AccessMode mode, const void* addrHint);
	protected:
		~ProcessShareMemory();
#ifdef WINDOWS
		void map();
#else
		void map(const void* addrHint);	/// Maps the shared memory object.
#endif
		void unmap();	/// Unmaps the shared memory object.
		void close();	/// Releases the handle for the shared memory segment.
	private:
	private:
		ProcessShareMemory();
		ProcessShareMemory(const ProcessShareMemory&);
		ProcessShareMemory& operator = (const ProcessShareMemory&);
#ifdef WINDOWS
		HANDLE  _memHandle;
		HANDLE  _fileHandle;
		DWORD   _mode;
#else
		int         _fd;
		ShareMemory_AccessMode::AccessMode _access;
		bool        _fileMapped;
		bool        _server;
#endif
		std::size_t _size;
		std::string _name;
		char*   _address;
	};


	class  SharedMemory
	{
	public:

		SharedMemory();
		SharedMemory(const std::string& name, std::size_t size, ShareMemory_AccessMode mode, const void* addrHint = 0, bool server = true);

		SharedMemory(const FileInfo& file, ShareMemory_AccessMode mode, const void* addrHint = 0);
		SharedMemory(const SharedMemory& other);
		~SharedMemory();
		SharedMemory& operator = (const SharedMemory& other);
		void swap(SharedMemory& other);
		char* begin() const{return (_pImpl)?_pImpl->begin():0;}
		char* end() const{return (_pImpl)?_pImpl->end():0;}

	private:
		ProcessShareMemory* _pImpl;
	};

	inline void SharedMemory::swap(SharedMemory& other)
	{
		using std::swap;
		swap(_pImpl, other._pImpl);
	}
}


#endif