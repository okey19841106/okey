/********************************************************************
	created:	2015/01/07
	created:	11:07
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __PATH_INFO_H__
#define __PATH_INFO_H__

#include <string>
#include <vector>

namespace okey
{
	class PathInfo
	{
	public:
		PathInfo();
		PathInfo(const std::string& path);
		PathInfo(const PathInfo& path);
		~PathInfo();
		PathInfo& operator = (const PathInfo& path);
		PathInfo& operator = (const std::string& path);
		PathInfo& operator = (const char* path);
		void swap(PathInfo& path);
		std::string ToString() const;
		PathInfo& assign(const std::string& path);
		PathInfo& assign(const PathInfo& path);
		void clear();
		PathInfo& parse(const std::string& path);
		bool tryParse(const std::string& path);
		PathInfo& PushDirectory(const std::string& dir);
		PathInfo& MakeDirectory();
		PathInfo& parseDirectory(const std::string& path)
	protected:
		std::string m_sNode;
		std::string m_sDevice;
		std::string m_sName;
		std::string m_sVersion;
		std::vector<std::string>   m_vDirs;
		bool        m_bAbsolute;
	};
}

#endif