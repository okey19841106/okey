/********************************************************************
	created:	2014/09/17
	created:	14:56
	author:		okey
	
	purpose:	file info..
*********************************************************************/

#ifndef __OKEY_FILE_INFO_H__
#define __OKEY_FILE_INFO_H__

#include "DateTime.h"
#include <vector>
#include "CRefcounter.h"

namespace okey
{
	class Iterator;

	class FileInfo
	{
	public:
		class DirectoryInfo : public CRefCounter
		{
		public:
			DirectoryInfo(const std::string& path);
			~DirectoryInfo();
			const std::string& get() const{return m_sFile;}
			const std::string& getFile() const {return m_sCurrent;}
			const std::string& next();
		protected:
#ifdef WINDOWS
			HANDLE          m_fh;
			WIN32_FIND_DATA m_fd;
#else
			DIR*        m_pDir;
#endif
			std::string     m_sCurrent;
			std::string     m_sPath;
			std::string     m_sFile;
		};
		
	public:
		FileInfo();
		FileInfo(const std::string& paths);
		FileInfo(const char* path);
		FileInfo(const FileInfo& fi);
		virtual ~FileInfo();
		FileInfo& operator=(const FileInfo& fi);
		FileInfo& operator=(const std::string& path);
		FileInfo& operator=(const char* path);


		void Swap(FileInfo& file);
		std::string GetPath() const{return m_sPath;}
		void SetPath(const std::string& path);
		bool IsExisted()const;
		bool CanRead()const;
		bool CanWrite()const;
		bool CanExecute()const;
		bool IsFile()const;
		bool IsLink()const;
		bool IsDirectory()const;
		bool IsDevice()const;
		bool IsHidden()const;
		DateTime GetCreateTime()const;
		DateTime GetModityTime()const;
		FileInfo& SetModityTime(DateTime& dt);
		uint32 GetSize()const;
		FileInfo& SetSize(const uint32& size);
		FileInfo& SetWriteable(bool flag = true);
		FileInfo& SetReadOnly(bool flag = true);
		FileInfo& SetExecutable(bool flag = true);
		void CopyTo(const std::string& path)const;
		void MoveTo(const std::string& path);
		void RenameTo(const std::string& path);
		void Remove(bool recursive = false); //µÝ¹éÉ¾³ý¡£
		bool CreateFile();
		bool CreateDirectory();
		void CreateDirectories();
		void GetList(std::vector<std::string>& files)const;
		void GetList(std::vector<FileInfo>& files)const;
		bool operator == (const FileInfo& file) const;
		bool operator != (const FileInfo& file) const;
		bool operator < (const FileInfo& file) const;
		bool operator <= (const FileInfo& file) const;
		bool operator > (const FileInfo& file) const;
		bool operator >= (const FileInfo& file) const;

		static std::string GetAbsDir(const std::string& paths);
		static std::string GetExtension(const std::string& paths);
		static std::string GetFileName(const std::string& paths);
		//static std::string GetDirName(const std::string& paths);

		static std::string GetCurrent();
		static std::string GetHome();
		static std::string GetTemp();
		static std::string GetNull();
		static std::string GetSystem();
		static std::string GetExpand(const std::string& path);
		static void ListRoots(std::vector<std::string>& roots);

	protected:
		void CopyDirectory(const std::string& path) const;
	private:
		std::string m_sPath;
	};

	namespace OkeyFile
	{
		class Iterator
		{
			friend class FileInfo;
		public:
			Iterator();
			Iterator(const FileInfo& file);
			Iterator(const std::string& path);
			Iterator(const Iterator& path);
			~Iterator();
			Iterator& operator = (const Iterator& it);
			Iterator& operator = (const FileInfo& file);
			Iterator& operator = (const std::string& path);
			Iterator& operator++();
			Iterator operator++(int);
			const FileInfo& operator*() const{return m_cFileInfo;}
			FileInfo& operator*(){return m_cFileInfo;}
			const FileInfo* operator->() const{return &m_cFileInfo;}
			FileInfo* operator->(){return &m_cFileInfo;}
			bool operator==(const Iterator& iterator) const;
			bool operator!=(const Iterator& iterator) const;
			const std::string& name() const;
		protected:
		
			FileInfo m_cFileInfo;
			FileInfo::DirectoryInfo* m_pDi;
			const std::string m_csEmpty; 
		};

		inline bool Iterator::operator==(const Iterator& iterator) const
		{
			return name() == iterator.name();
		}

		inline bool Iterator::operator!=(const Iterator& iterator) const
		{
			return name() != iterator.name();
		}
	}
	
}

#endif