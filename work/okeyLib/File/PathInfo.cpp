#include "PreCom.h"
#include "PathInfo.h"
#include "Exception.h"

namespace okey
{
	PathInfo::PathInfo():m_bAbsolute(false)
	{

	}

	PathInfo::PathInfo(const std::string& path)
	{
		assign(path);
	}

	PathInfo::PathInfo(const PathInfo& path)
	{
		m_sNode     = path.m_sNode;
		m_sDevice   = path.m_sDevice;
		m_sName     = path.m_sName;
		m_sVersion  = path.m_sVersion;
		m_vDirs     = path.m_vDirs;
		m_bAbsolute = path.m_bAbsolute;
	}

	PathInfo::~PathInfo()
	{

	}

	PathInfo& PathInfo::assign(const std::string& path)
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
			MakeDirectory();
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

	void PathInfo::clear()
	{
		m_sNode.clear();
		m_sDevice.clear();
		m_sName.clear();
		m_sVersion.clear();
		m_vDirs.clear();
		m_bAbsolute = false;
	}

	PathInfo& PathInfo::PushDirectory(const std::string& dir)
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
		return *this;
	}

	PathInfo& PathInfo::MakeDirectory()
	{
		PushDirectory(m_sName);
		m_sName.clear();
		m_sVersion.clear();
		return *this;
	}

	PathInfo& PathInfo::operator = (const PathInfo& path)
	{
		return assign(path);
	}

	PathInfo& PathInfo::operator = (const std::string& path)
	{
		return assign(path);
	}

	PathInfo& PathInfo::operator = (const char* path)
	{
		return assign(path);
	}

	PathInfo& PathInfo::assign(const PathInfo& path)
	{
		if (&path != this)
		{
			m_sNode     = path.m_sNode;
			m_sDevice   = path.m_sDevice;
			m_sName     = path.m_sName;
			m_sVersion  = path.m_sVersion;
			m_vDirs     = path.m_vDirs;
			m_bAbsolute = path.m_bAbsolute;
		}
		return *this;
	}
	void PathInfo::swap(PathInfo& path)
	{

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
		return result;
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

	PathInfo& PathInfo::parse(const std::string& path)
	{
		return assign(path);
	}

	bool PathInfo::tryParse(const std::string& path)
	{
		try
		{
			PathInfo p;
			p.parse(path);
			assign(p);
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	PathInfo& PathInfo::parseDirectory(const std::string& path)
	{
		assign(path);
		return MakeDirectory();
	}
}