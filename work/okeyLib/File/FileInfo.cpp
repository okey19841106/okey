#include "PreCom.h"
#include "FileInfo.h"
#include "File.h"
#include "TimeStamp.h"
#include "Exception.h"
#include "StringHelper.h"

namespace okey
{

	class PathInfo
	{
	public:
		PathInfo(const std::string& path);
		~PathInfo();
		std::string m_sNode;
		std::string m_sDevice;
		std::string m_sName;
		std::vector<std::string>   m_vDirs;
		bool m_bAbsolute;
		bool IsDirectory() const
		{
			return m_sName.empty();
		}
		void MakeDirectory()
		{
			PushDirectory(m_sName);
			m_sName.clear();
		}
		void MakeFile()
		{
			if (!m_vDirs.empty() && m_sName.empty())
			{
				m_sName = m_vDirs.back();
				m_vDirs.pop_back();
			}
		}
		void MakeParent();
		std::string ToString() const;
	private:
		void assign(const std::string& path);
		void clear();
		void PushDirectory(const std::string& dir);
	};

	PathInfo::PathInfo(const std::string& path):m_bAbsolute(false)
	{
		assign(path);
	}

	PathInfo::~PathInfo()
	{

	}

	void PathInfo::clear()
	{
		m_sNode.clear();
		m_sDevice.clear();
		m_sName.clear();
		m_vDirs.clear();
		m_bAbsolute = false;
	}
	void PathInfo::PushDirectory(const std::string& dir)
	{
		if (!dir.empty() && dir != ".")
		{
			if (dir == "..")
			{
				if (!m_vDirs.empty() && m_vDirs.back() != "..")
					m_vDirs.pop_back();
				else if (!m_bAbsolute)
					m_vDirs.push_back(dir);
			}
			else 
			{
				m_vDirs.push_back(dir);
			}
		}
	}

	void PathInfo::assign(const std::string& path)
	{
		clear();
		std::string::const_iterator it  = path.begin();
		std::string::const_iterator end = path.end();
#ifdef WINDOWS
		if (it != end)
		{
			if (*it == '\\' || *it == '/') 
			{
				m_bAbsolute = true; 
				++it; 
			}
			if (m_bAbsolute && it != end && (*it == '\\' || *it == '/')) // UNC
			{
				++it;
				while (it != end && *it != '\\' && *it != '/') 
					m_sNode += *it++;
				if (it != end) 
					++it;
			}
			else if (it != end)
			{
				char d = *it++;
				if (it != end && *it == ':') // drive letter
				{
					if (m_bAbsolute || !((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))) 
						throw PathSyntaxException(path);
					m_bAbsolute = true;
					m_sDevice += d;
					++it;
					if (it == end || (*it != '\\' && *it != '/')) 
						throw PathSyntaxException(path);
					++it;
				}
				else 
					--it;
			}
			while (it != end)
			{
				std::string name;
				while (it != end && *it != '\\' && *it != '/') 
					name += *it++;
				if (it != end)
					PushDirectory(name);
				else
					m_sName = name;
				if (it != end) 
					++it;
			}
		}
		if (!m_sNode.empty() && m_vDirs.empty() && !m_sName.empty())
		{
			MakeDirectory();
		}
#else
		if (it != end)
		{
			if (*it == '/') 
			{
				m_bAbsolute = true; 
				++it;
			}
			else if (*it == '~')
			{
				++it;
				if (it == end || *it == '/')
				{
					PathInfo cwd(home());
					m_vDirs = cwd._dirs;
					m_bAbsolute = true;
				}
				else 
					--it;
			}

			while (it != end)
			{
				std::string name;
				while (it != end && *it != '/') 
					name += *it++;
				if (it != end)
				{
					if (m_vDirs.empty())
					{
						if (!name.empty() && *(name.rbegin()) == ':')
						{
							m_bAbsolute = true;
							m_sDevice.assign(name, 0, name.length() - 1);
						}
						else
						{
							PushDirectory(name);
						}
					}
					else 
						PushDirectory(name);
				}
				else
					m_sName = name;
				if (it != end) 
					++it;
			}
		}
#endif
	}

	std::string PathInfo::ToString() const
	{
		std::string result;
#ifdef WINDOWS
		if (!m_sNode.empty())
		{
			result.append("\\\\");
			result.append(m_sNode);
			result.append("\\");
		}
		else if (!m_sDevice.empty())
		{
			result.append(m_sDevice);
			result.append(":\\");
		}
		else if (m_bAbsolute)
		{
			result.append("\\");
		}
		for (std::vector<std::string>::const_iterator it = m_vDirs.begin(); it != m_vDirs.end(); ++it)
		{
			result.append(*it);
			result.append("\\");
		}
		result.append(m_sName);
#else
		if (!m_sDevice.empty())
		{
			result.append("/");
			result.append(m_sDevice);
			result.append(":/");
		}
		else if (m_bAbsolute)
		{
			result.append("/");
		}
		for (std::vector<std::string>::const_iterator::const_iterator it = _dirs.begin(); it != _dirs.end(); ++it)
		{
			result.append(*it);
			result.append("/");
		}
		result.append(m_sName);
#endif
		return result;
	}

	void PathInfo::MakeParent()
	{
		if (m_sName.empty())
		{
			if (m_vDirs.empty())
			{
				if (!m_bAbsolute)
					m_vDirs.push_back("..");
			}
			else
			{
				if (m_vDirs.back() == "..")
					m_vDirs.push_back("..");
				else
					m_vDirs.pop_back();
			}
		}
		else
		{
			m_sName.clear();
		}
	}
	FileInfo::DirectoryInfo::DirectoryInfo(const std::string& path)
	{
		PathInfo p(path);
#ifdef WINDOWS
		p.MakeDirectory();
		m_sPath = p.ToString();
		std::string findPath = m_sPath;
		findPath.append("*");
		m_fh = ::FindFirstFile(findPath.c_str(), &m_fd);
		if (m_fh == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() != ERROR_NO_MORE_FILES)
				File::HandleFileError(path);
		}
		else
		{
			m_sCurrent = m_fd.cFileName;
			if (m_sCurrent == "." || m_sCurrent == "..")
			{
				next();
			}
			else
			{
				m_sFile = m_sPath + m_sCurrent;
			}
		}
#else
		m_sPath = p.MakeFile();
		m_pDir = opendir(m_sPath.c_str());
		if (!m_pDir) 
			File::HandleFileError(path);
		next();
#endif
	}

	FileInfo::DirectoryInfo::~DirectoryInfo()
	{
#ifdef WINDOWS
		if (m_fh != INVALID_HANDLE_VALUE)
			FindClose(m_fh);
#else
		if (m_pDir)
		{
			closedir(m_pDir);
		}
#endif
	}

	const std::string& FileInfo::DirectoryInfo::next()
	{
#ifdef WINDOWS
		do
		{
			if (FindNextFile(m_fh, &m_fd) != 0)
			{
				m_sCurrent = m_fd.cFileName;
				m_sFile = m_sPath + m_sCurrent;
			}
			else
			{
				m_sCurrent.clear();
				m_sFile.clear();
			}
		}
#else
		do
		{
			struct dirent* pEntry = readdir(m_pDir);
			if (pEntry)
			{
				m_sCurrent = pEntry->d_name;
				m_sFile = m_sPath + m_sCurrent;
			}
			else
			{
				m_sCurrent.clear();
				m_sFile.clear();
			}
		}
#endif
		while (m_sCurrent == "." || m_sCurrent == "..");
		return m_sCurrent;
	}

	namespace OkeyFile
	{

	
		Iterator::Iterator():m_pDi(NULL)
		{

		}

		Iterator::Iterator(const FileInfo& file)
		{
			m_pDi = new FileInfo::DirectoryInfo(file.GetPath());
			m_cFileInfo = m_pDi->get();
		}

		Iterator::Iterator(const std::string& path):m_pDi(new FileInfo::DirectoryInfo(path))
		{
			m_cFileInfo = m_pDi->get();
		}

		Iterator::Iterator(const Iterator& path):m_pDi(path.m_pDi)
		{
			if (m_pDi)
			{
				m_pDi->AddRef();
				m_cFileInfo = path.m_cFileInfo;
			}
		}

		Iterator::~Iterator()
		{
			if (m_pDi)
			{
				m_pDi->DecRef();
			}
		}
		Iterator& Iterator::operator = (const Iterator& it)
		{
			if (m_pDi)
			{
				m_pDi->DecRef();
			}
			m_pDi = it.m_pDi;
			if (m_pDi)
			{
				m_pDi->AddRef();
				m_cFileInfo = it.m_cFileInfo;
			}
			return *this;
		}
		Iterator& Iterator::operator = (const FileInfo& file)
		{
			if (m_pDi)
			{
				m_pDi->DecRef();
			}
			m_pDi = new FileInfo::DirectoryInfo(file.GetPath());
			m_cFileInfo = file;
			return *this;
		}
		Iterator& Iterator::operator = (const std::string& path)
		{
			if (m_pDi)
			{
				m_pDi->DecRef();
			}
			m_pDi = new FileInfo::DirectoryInfo(path);
			m_cFileInfo = path;
			return *this;
		}

		Iterator& Iterator::operator++()
		{
			if (m_pDi)
			{
				m_pDi->next();
				m_cFileInfo = m_pDi->get();
			}
			return *this;
		}

		Iterator Iterator::operator++(int d)
		{
			Iterator itr = *this;
			if (m_pDi)
			{
				m_pDi->next();
				m_cFileInfo = m_pDi->get();
			}
			return itr;
		}

		const std::string& Iterator::name() const
		{
			if (m_pDi)
			{
				return m_pDi->get();
			}
			return m_csEmpty;
		}
	}
	FileInfo::FileInfo()
	{

	}

	FileInfo::FileInfo(const std::string& paths)
	{
		SetPath(paths);
	}

	FileInfo::FileInfo(const char* path)
	{
		SetPath(path);
	}

	FileInfo::FileInfo(const FileInfo& fi)
	{
		SetPath(fi.m_sPath);
	}

	FileInfo::~FileInfo()
	{

	}

	FileInfo& FileInfo::operator=(const FileInfo& fi)
	{
		SetPath(fi.m_sPath);
		return *this;
	}
	FileInfo& FileInfo::operator=(const std::string& path)
	{
		SetPath(path);
		return *this;
	}
	FileInfo& FileInfo::operator=(const char* path)
	{
		SetPath(path);
		return *this;
	}
	void FileInfo::Swap(FileInfo& file)
	{
		std::swap(m_sPath, file.m_sPath);
	}

	bool FileInfo::IsExisted()const
	{
		if (m_sPath.empty())
		{
			return false;
		}
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
		{
			switch (GetLastError())
			{
			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
			case ERROR_NOT_READY:
			case ERROR_INVALID_DRIVE:
				return false;
			default:
				File::HandleFileError(m_sPath);
				return false;
			}
		}
		return true;
#else
		struct stat st;
		return stat(m_sPath.c_str(), &st) == 0;
#endif
	}

	bool FileInfo::CanRead()const
	{
		if (m_sPath.empty())
		{
			return false;
		}
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
		{
			switch (GetLastError())
			{
			case ERROR_ACCESS_DENIED:
				return false;
			default:
				File::HandleFileError(m_sPath);
				return false;
			}
		}
		return true;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
		{
			if (st.st_uid == geteuid())
				return (st.st_mode & S_IRUSR) != 0;
			else if (st.st_gid == getegid())
				return (st.st_mode & S_IRGRP) != 0;
			else
				return (st.st_mode & S_IROTH) != 0 || geteuid() == 0;
		}
		else
		{
			File::HandleFileError(m_sPath);
			return false;
		}
		return false;
#endif
	}

	bool FileInfo::CanWrite()const
	{
		if (m_sPath.empty())
		{
			return false;
		}
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
		{
			File::HandleFileError(m_sPath);
			return false;
		}
		return (attr & FILE_ATTRIBUTE_READONLY) == 0;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
		{
			if (st.st_uid == geteuid())
				return (st.st_mode & S_IWUSR) != 0;
			else if (st.st_gid == getegid())
				return (st.st_mode & S_IWGRP) != 0;
			else
				return (st.st_mode & S_IWOTH) != 0 || geteuid() == 0;
		}
		else
		{
			File::HandleFileError(m_sPath);
			return false;
		}
		return false;
#endif
	}

	bool FileInfo::CanExecute()const
	{
#ifdef WINDOWS
		return icompare(GetExtension(m_sPath), "exe") == 0;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
		{
			if (st.st_uid == geteuid() || geteuid() == 0)
				return (st.st_mode & S_IXUSR) != 0;
			else if (st.st_gid == getegid())
				return (st.st_mode & S_IXGRP) != 0;
			else
				return (st.st_mode & S_IXOTH) != 0;
		}
		else
		{
			File::HandleFileError(m_sPath);
			return false;
		}
		return false;
#endif
	}

	bool FileInfo::IsFile()const
	{
		if (m_sPath.empty())
		{
			return false;
		}
#ifdef WINDOWS
		return !IsDirectory() && !IsDevice();
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return S_ISREG(st.st_mode);
		else
		{
			File::HandleFileError(m_sPath);
		}
		return false;
#endif
	}
	bool FileInfo::IsLink()const
	{
#ifdef WINDOWS
		return false;
#else
		struct stat st;
		if (lstat(m_sPath.c_str(), &st) == 0)
			return S_ISLNK(st.st_mode);
		else
			File::HandleFileError(m_sPath);
		return false;
#endif
	}

	bool FileInfo::IsDirectory()const
	{
		if (m_sPath.empty())
		{
			return false;
		}
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
			File::HandleFileError(m_sPath);
		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return S_ISDIR(st.st_mode);
		else
			File::HandleFileError(m_sPath);
		return false;
#endif
	}

	bool FileInfo::IsDevice()const
	{
#ifdef WINDOWS
		return
			m_sPath.compare(0, 4, "\\\\.\\") == 0 ||
			icompare(m_sPath, "CON") == 0 ||
			icompare(m_sPath, "PRN") == 0 ||
			icompare(m_sPath, "AUX") == 0 ||
			icompare(m_sPath, "NUL") == 0 ||
			icompare(m_sPath, "LPT1") == 0 ||
			icompare(m_sPath, "LPT2") == 0 ||
			icompare(m_sPath, "LPT3") == 0 ||
			icompare(m_sPath, "LPT4") == 0 ||
			icompare(m_sPath, "LPT5") == 0 ||
			icompare(m_sPath, "LPT6") == 0 ||
			icompare(m_sPath, "LPT7") == 0 ||
			icompare(m_sPath, "LPT8") == 0 ||
			icompare(m_sPath, "LPT9") == 0 ||
			icompare(m_sPath, "COM1") == 0 ||
			icompare(m_sPath, "COM2") == 0 ||
			icompare(m_sPath, "COM3") == 0 ||
			icompare(m_sPath, "COM4") == 0 ||
			icompare(m_sPath, "COM5") == 0 ||
			icompare(m_sPath, "COM6") == 0 ||
			icompare(m_sPath, "COM7") == 0 ||
			icompare(m_sPath, "COM8") == 0 ||
			icompare(m_sPath, "COM9") == 0;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode);
		else
			File::HandleFileError(m_sPath);
		return false;
#endif
	}

	bool FileInfo::IsHidden()const
	{
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
			File::HandleFileError(m_sPath);
		return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
#else
		Path p(_path);
		p.makeFile();
		return p.getFileName()[0] == '.';
#endif
	}

	DateTime FileInfo::GetCreateTime()const
	{
#ifdef WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (GetFileAttributesEx(m_sPath.c_str(), GetFileExInfoStandard, &fad) == 0) 
			File::HandleFileError(m_sPath);
		return DateTime(TimeStamp::fromFileTimeNP(fad.ftCreationTime.dwLowDateTime, fad.ftCreationTime.dwHighDateTime));
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return DateTime(Timestamp::fromEpochTime(st.st_ctime));
		else
			File::HandleFileError(_path);
		return 0;
#endif
	}

	DateTime FileInfo::GetModityTime()const
	{
#ifdef WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (GetFileAttributesEx(m_sPath.c_str(), GetFileExInfoStandard, &fad) == 0) 
			File::HandleFileError(m_sPath);
		return DateTime(TimeStamp::fromFileTimeNP(fad.ftLastWriteTime.dwLowDateTime, fad.ftLastWriteTime.dwHighDateTime));
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return DateTime(Timestamp::fromEpochTime(st.st_mtime));
		else
			File::HandleFileError(_path);
		return 0;
#endif
	}

	FileInfo& FileInfo::SetModityTime(DateTime& dt)
	{
#ifdef WINDOWS
		uint32 low;
		uint32 high;
		TimeStamp ts = dt.ToTime();
		ts.toFileTimeNP(low, high);
		FILETIME ft;
		ft.dwLowDateTime  = low;
		ft.dwHighDateTime = high;
		//File file(m_sPath,File::acReadWrite);
		HANDLE _h = ::CreateFileA(m_sPath.c_str(), GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		if (_h == INVALID_HANDLE_VALUE)
		{
			File::HandleFileError(m_sPath);
		}
		if (SetFileTime(_h, 0, &ft, &ft) == 0)
		{
			::CloseHandle(_h);
			File::HandleFileError(m_sPath);
		}
		::CloseHandle(_h);
#else
		struct utimbuf tb;
		tb.actime  = ts.epochTime();
		tb.modtime = ts.epochTime();
		if (utime(m_sPath.c_str(), &tb) != 0)
			File::HandleFileError(_path);
#endif
		return *this;
	}
	uint32 FileInfo::GetSize() const
	{
#ifdef WINDOWS
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (GetFileAttributesEx(m_sPath.c_str(), GetFileExInfoStandard, &fad) == 0) 
			File::HandleFileError(m_sPath);
		LARGE_INTEGER li;
		li.LowPart  = fad.nFileSizeLow;
		li.HighPart = fad.nFileSizeHigh;
		return (uint32)li.QuadPart;
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) == 0)
			return (uint32)st.st_size;
		else
			File::HandleFileError(m_sPath);
		return 0;
#endif
	}

	FileInfo& FileInfo::SetSize(const uint32& size)
	{
#ifdef WINDOWS
		HANDLE _h = ::CreateFile(m_sPath.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		LARGE_INTEGER li;
		li.QuadPart = size;
		if (SetFilePointer(_h, li.LowPart, &li.HighPart, FILE_BEGIN) == -1)
		{
			::CloseHandle(_h);
			File::HandleFileError(m_sPath);
		}
		if (SetEndOfFile(_h) == 0) 
		{
			::CloseHandle(_h);
			File::HandleFileError(m_sPath);
		}
		::CloseHandle(_h);
#else
		if (truncate(m_sPath.c_str(), size) != 0)
			File::HandleFileError(m_sPath);
	}
#endif
	return *this;
	}

	FileInfo& FileInfo::SetWriteable(bool flag)
	{
#ifdef WINDOWS
		DWORD attr = GetFileAttributes(m_sPath.c_str());
		if (attr == INVALID_FILE_ATTRIBUTES)
			File::HandleFileError(m_sPath);
		if (flag)
			attr &= ~FILE_ATTRIBUTE_READONLY;
		else
			attr |= FILE_ATTRIBUTE_READONLY;
		if (SetFileAttributes(m_sPath.c_str(), attr) == 0)
			File::HandleFileError(m_sPath);
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) != 0) 
			File::HandleFileError(m_sPath);
		mode_t mode;
		if (flag)
		{
			mode = st.st_mode | S_IWUSR;
		}
		else
		{
			mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
			mode = st.st_mode & ~wmask;
		}
		if (chmod(m_sPath.c_str(), mode) != 0) 
			File::HandleFileError(m_sPath);
#endif
		return *this;
	}

	FileInfo& FileInfo::SetReadOnly(bool flag)
	{
		return SetWriteable(!flag);
	}

	FileInfo& FileInfo::SetExecutable(bool flag )
	{
#ifdef WINDOWS
		//windows can not apply...
#else
		struct stat st;
		if (stat(m_sPath.c_str(), &st) != 0) 
			File::HandleFileErrorImpl(m_sPath);
		mode_t mode;
		if (flag)
		{
			mode = st.st_mode | S_IXUSR;
		}
		else
		{
			mode_t wmask = S_IXUSR | S_IXGRP | S_IXOTH;
			mode = st.st_mode & ~wmask;
		}
		if (chmod(m_sPath.c_str(), mode) != 0) 
			File::HandleFileError(m_sPath);
#endif
		return *this;
	}

	void FileInfo::CopyTo(const std::string& path)const
	{
		FileInfo destFile(path);
		PathInfo dest(path);
		PathInfo src(m_sPath);
		if ((destFile.IsExisted() && destFile.IsDirectory()) || dest.IsDirectory())
		{
			dest.MakeDirectory();
			dest.m_sName = src.m_sName;
		}
		if (IsDirectory())
			CopyDirectory(dest.ToString());
		else
		{
			std::string desz = dest.ToString();
#ifdef WINDOWS
			if (::CopyFile(m_sPath.c_str(), desz.c_str(), FALSE) != 0) 
			{
				FileInfo copy(desz);
				copy.SetWriteable(true);
			}
			else 
			{
				File::HandleFileError(m_sPath);
			}
#else
			int sd = open(m_sPath.c_str(), O_RDONLY);
			if (sd == -1) 
			{
				File::HandleFileError(m_sPath);
			}

			struct stat st;
			if (fstat(sd, &st) != 0) 
			{
				close(sd);
				File::HandleFileError(m_sPath);
			}
			const long blockSize = st.st_blksize;

			int dd = open(desz.c_str(), O_CREAT | O_TRUNC | O_WRONLY, st.st_mode & S_IRWXU);
			if (dd == -1)
			{
				close(sd);
				File::HandleFileErrorImpl(path);
			}
			TBuffer<char> buffer(blockSize);
			try
			{
				int n;
				while ((n = read(sd, buffer.begin(), blockSize)) > 0)
				{
					if (write(dd, buffer.begin(), n) != n) 
						File::HandleFileError(m_sPath);
				}
				if (n < 0)
					File::HandleFileError(m_sPath);
			}
			catch (...)
			{
				close(sd);
				close(dd);
				throw;
			}
			close(sd);
			if (fsync(dd) != 0) 
			{
				close(dd);
				File::HandleFileError(desz);
			}
			if (close(dd) != 0)
				File::HandleFileError(desz);
#endif
		}
	}

	void FileInfo::MoveTo(const std::string& path)
	{
		CopyTo(path);
		Remove(true);
		m_sPath = path;
		std::string::size_type n = m_sPath.size();
		if (n > 1 && m_sPath[n - 1] == '/')
			m_sPath.resize(n - 1);
	}

	void FileInfo::RenameTo(const std::string& path)
	{
#ifdef WINDOWS
		if (::MoveFile(m_sPath.c_str(), path.c_str()) == 0) 
			File::HandleFileError(m_sPath);
#else
		if (rename(m_sPath.c_str(), path.c_str()) != 0)
			File::HandleFileError(m_sPath);
#endif
	}

	void FileInfo::Remove(bool recursive)
	{
		if (recursive && !IsLink() && IsDirectory())
		{
			std::vector<FileInfo> files;
			GetList(files);
			for (std::vector<FileInfo>::iterator it = files.begin(); it != files.end(); ++it)
			{
				it->Remove(true);
			}
		}
#ifdef WINDOWS
		if (IsDirectory())
		{
			if (::RemoveDirectory(m_sPath.c_str()) == 0) 
				File::HandleFileError(m_sPath);
		}
		else
		{
			if (::DeleteFile(m_sPath.c_str()) == 0)
				File::HandleFileError(m_sPath);
		}
#else
		if (!IsLink() && IsDirectory())
			rc = rmdir(m_sPath.c_str());
		else
			rc = unlink(m_sPath.c_str());
		if (rc) 
		{
			File::HandleFileError(_path);
		}
#endif
	}

	bool FileInfo::CreateFile()
	{
#ifdef WINDOWS
		HANDLE hFile = ::CreateFile(m_sPath.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			return true;
		}
		else if (GetLastError() == ERROR_FILE_EXISTS)
			return false;
		else
			File::HandleFileError(m_sPath);
		return false;
#else
		int n = open(m_sPath.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (n != -1)
		{
			close(n);
			return true;
		}
		if (n == -1 && errno == EEXIST)
			return false;
		else
			File::HandleFileError(m_sPath);
		return false;
#endif
	}

	bool FileInfo::CreateDirectory()
	{
		if (IsExisted() && IsDirectory())
			return false;
#ifdef WINDOWS
		if (::CreateDirectory(m_sPath.c_str(), 0) == 0)
			File::HandleFileError(m_sPath);
#else

		if (mkdir(m_sPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0) 
			File::HandleFileError(m_sPath);
#endif
		return true;
	}

	void FileInfo::CreateDirectories()
	{
		if (!IsExisted())
		{
			PathInfo p(m_sPath);
			p.MakeDirectory();
			if (p.m_vDirs.size() > 1)
			{
				p.MakeParent();
				FileInfo f(p.ToString());
				f.CreateDirectories();
			}
			CreateDirectory();
		}
	}

	void FileInfo::GetList(std::vector<std::string>& files)const
	{
		files.clear();
		OkeyFile::Iterator it(*this);
		OkeyFile::Iterator end;
		while (it != end)
		{
			files.push_back(GetFileName(it->m_sPath));
			++it;
		}
	}

	void FileInfo::GetList(std::vector<FileInfo>& files)const
	{
		files.clear();
		OkeyFile::Iterator it(*this);
		OkeyFile::Iterator end;
		while (it != end)
		{
			files.push_back(*it);
			++it;
		}
	}

	void FileInfo::CopyDirectory(const std::string& path) const
	{
		FileInfo target(path);
		target.CreateDirectories();

		PathInfo src(m_sPath);
		src.MakeFile();
		OkeyFile::Iterator it(src.ToString());
		OkeyFile::Iterator end;
		for (; it != end; ++it)
		{
			it->CopyTo(path);
		}
	}

	void FileInfo::SetPath(const std::string& path)
	{
		m_sPath = path;
#ifdef WINDOWS
		std::string::size_type n = m_sPath.size();
		if (n > 1 && (m_sPath[n - 1] == '\\' || m_sPath[n - 1] == '/') && !((n == 3 && m_sPath[1]==':')))
		{
			m_sPath.resize(n - 1);
		}
#else
		std::string::size_type n = m_sPath.size();
		if (n > 1 && _path[n - 1] == '/')
			m_sPath.resize(n - 1);
#endif
	}

	std::string FileInfo::GetCurrent()
	{
#ifdef WINDOWS
		char buffer[MAX_PATH];
		DWORD n = ::GetCurrentDirectory(sizeof(buffer), buffer);
		if (n > 0 && n < sizeof(buffer))
		{
			std::string result(buffer, n);
			if (result[n - 1] != '\\')
				result.append("\\");
			return result;
		}
		else 
			throw SystemException("Cannot get current directory");
#else
		std::string path;
		char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)))
			path = cwd;
		else
			throw SystemException("cannot get current directory");
		std::string::size_type n = path.size();
		if (n > 0 && path[n - 1] != '/') path.append("/");
		return path;
#endif
	}

	std::string FileInfo::GetHome()
	{
#ifdef WINDOWS
		//做环境变量的时候再搞。
 		std::string result;
// 		try
// 		{
// 			// windows service has no home dir, return system directory instead
// 			result = EnvironmentImpl::getImpl("HOMEDRIVE");
// 			result.append(EnvironmentImpl::getImpl("HOMEPATH"));
// 		}
// 		catch (NotFoundException&) 
// 		{
// 			result = GetSystem();
// 		}

		std::string::size_type n = result.size();
		if (n > 0 && result[n - 1] != '\\')
			result.append("\\");
		return result;
#else
		std::string path;
		struct passwd* pwd = getpwuid(getuid());
		if (pwd)
			path = pwd->pw_dir;
		else
		{
			pwd = getpwuid(geteuid());
			if (pwd)
				path = pwd->pw_dir;
			else
				path = EnvironmentImpl::getImpl("HOME");
		}
		std::string::size_type n = path.size();
		if (n > 0 && path[n - 1] != '/') path.append("/");
		return path;
#endif
	}

	std::string FileInfo::GetTemp()
	{
#ifdef WINDOWS
		char buffer[MAX_PATH];
		DWORD n = GetTempPath(sizeof(buffer), buffer);
		if (n > 0 && n < sizeof(buffer))
		{
			n = GetLongPathName(buffer, buffer, static_cast<DWORD>(sizeof buffer));
			if (n <= 0) 
				throw SystemException("Cannot get temporary directory long path name");
			std::string result(buffer, n);
			if (result[n - 1] != '\\')
				result.append("\\");
			return result;
		}
		else throw SystemException("Cannot get temporary directory");
#else
		std::string path;
		char* tmp = getenv("TMPDIR");
		if (tmp)
		{
			path = tmp;
			std::string::size_type n = path.size();
			if (n > 0 && path[n - 1] != '/') path.append("/");
		}
		else
		{
			path = "/tmp/";
		}
		return path;
#endif
	}

	std::string FileInfo::GetNull()
	{
#ifdef WINDOWS
		return "NUL:";
#else
		return "/dev/null";
#endif
	}

	std::string FileInfo::GetSystem()
	{
#ifdef WINDOWS
		char buffer[MAX_PATH];
		DWORD n = GetSystemDirectory(buffer, sizeof(buffer));
		if (n > 0 && n < sizeof(buffer))
		{
			std::string result(buffer, n);
			if (result[n - 1] != '\\')
				result.append("\\");
			return result;
		}
		else throw SystemException("Cannot get system directory");
#else
		return std::string("");
#endif
	}

	std::string FileInfo::GetExpand(const std::string& path)
	{
#ifdef WINDOWS
		char buffer[MAX_PATH];
		DWORD n = ExpandEnvironmentStrings(path.c_str(), buffer, sizeof(buffer));
		if (n > 0 && n < sizeof(buffer))
			return std::string(buffer, n - 1);
		else
			return path;
#else
		std::string result;
		std::string::const_iterator it  = path.begin();
		std::string::const_iterator end = path.end();
		if (it != end && *it == '~')
		{
			++it;
			if (it != end && *it == '/')
			{
				result += GetHome(); 
				++it;
			}
			else 
				result += '~';
		}
		while (it != end)
		{
			if (*it == '$')
			{
				std::string var;
				++it;
				if (it != end && *it == '{')
				{
					++it;
					while (it != end && *it != '}') 
						var += *it++;
					if (it != end) 
						++it;
				}
				else
				{
					while (it != end && (Ascii::isAlphaNumeric(*it) || *it == '_')) 
						var += *it++;
				}
				char* val = getenv(var.c_str());
				if (val) 
					result += val;
			}
			else 
				result += *it++;
		}
		return result;
#endif
	}

	void FileInfo::ListRoots(std::vector<std::string>& roots)
	{
#ifdef WINDOWS
		roots.clear();
		char buffer[128];
		DWORD n = GetLogicalDriveStrings(sizeof(buffer) - 1, buffer);
		char* it = buffer;
		char* end = buffer + (n > sizeof(buffer) ? sizeof(buffer) : n);
		while (it < end)
		{
			std::string dev;
			while (it < end && *it) dev += *it++;
			roots.push_back(dev);
			++it;
		}
#else
		roots.clear();
		roots.push_back("/");
#endif
	}

	std::string FileInfo::GetAbsDir(const std::string& paths)
	{
#ifdef WINDOWS
		char abspath[MAX_PATH+1];
		LPTSTR filePart = 0;
		DWORD ret = GetFullPathName(paths.c_str(), MAX_PATH, abspath, &filePart);
		if(!ret)
			throw SystemException("Could not resolve absolute path");

		return std::string(abspath);
#else
		char abspath[PATH_MAX+1];
		if(!realpath(GetDirName(paths).c_str(), abspath))
			throw SystemException("Could not resolve absolute path");
		return string(abspath);
#endif
	}

	std::string FileInfo::GetExtension(const std::string& paths)
	{
		std::string filename = GetFileName(paths);
		if (filename.empty())
		{
			return std::string();
		}
		std::string::size_type pos = filename.rfind('.');
		if (pos != std::string::npos)
			return filename.substr(pos + 1);
		else
			return std::string();
	}

	std::string FileInfo::GetFileName(const std::string& paths)
	{
		PathInfo pi(paths);
		return pi.m_sName;
	}


		
}