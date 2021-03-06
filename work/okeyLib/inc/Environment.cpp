#include "PreCom.h"
#include "Environment.h"
#include "Exception.h"
#include <sstream>
#ifdef WINDOWS
#include <IPTypes.h>
#include <IPHlpApi.h>
#include <Psapi.h>
#pragma comment(lib, "Psapi")
#endif


namespace okey
{
#ifndef WINDOWS
	static StringMap Environment::m_map;
	static FastMutex Environment::m_cMutex;
#endif
	std::string Environment::get(const std::string& name)
	{
#ifdef WINDOWS
		DWORD len = GetEnvironmentVariable(name.c_str(), 0, 0);
		if (len == 0) 
			throw NotFoundException(name);
		char* buffer = new char[len];
		GetEnvironmentVariable(name.c_str(), buffer, len);
		std::string result(buffer);
		delete [] buffer;
		return result;
#else
		FastMutex::ScopedLock lock(m_cMutex);
		const char* val = getenv(name.c_str());
		if (val)
			return std::string(val);
		else
			throw NotFoundException(name);
#endif
	}

	std::string Environment::get(const std::string& name, const std::string& defaultValue)
	{
		if (has(name))
			return get(name);
		else
			return defaultValue;
	}

	bool Environment::has(const std::string& name)
	{
#ifdef WINDOWS
		DWORD len = GetEnvironmentVariable(name.c_str(), 0, 0);
		return len > 0;
#else
		FastMutex::ScopedLock lock(m_cMutex);
		return getenv(name.c_str()) != 0;
#endif
		
	}

	void Environment::set(const std::string& name, const std::string& value)
	{
#ifdef WINDOWS
		if (SetEnvironmentVariable(name.c_str(), value.c_str()) == 0)
		{
			std::string msg = "cannot set environment variable: ";
			msg.append(name);
			throw SystemException(msg);
		}
#else
		FastMutex::ScopedLock lock(m_cMutex);
		std::string var = name;
		var.append("=");
		var.append(value);
		_map[name] = var;
		if (putenv((char*) _map[name].c_str()))
		{
			std::string msg = "cannot set environment variable: ";
			msg.append(name);
			throw SystemException(msg);
		}
#endif
	}

	std::string Environment::osName()
	{
#ifdef WINDOWS
		OSVERSIONINFO vi;
		vi.dwOSVersionInfoSize = sizeof(vi);
		if (GetVersionEx(&vi) == 0) throw SystemException("Cannot get OS version information");
		switch (vi.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:
			return "Windows 3.x";
		case VER_PLATFORM_WIN32_WINDOWS:
			return vi.dwMinorVersion == 0 ? "Windows 95" : "Windows 98";
		case VER_PLATFORM_WIN32_NT:
			return "Windows NT";
		default:
			return "Unknown";
		}
#else
		struct utsname uts;
		uname(&uts);
		return uts.sysname;
#endif
	}

	std::string Environment::osDisplayName()
	{
#ifdef WINDOWS
		OSVERSIONINFO vi;
		vi.dwOSVersionInfoSize = sizeof(vi);
		if (GetVersionEx(&vi) == 0) throw SystemException("Cannot get OS version information");
		switch(vi.dwMajorVersion)
		{
		case 6:
			switch (vi.dwMinorVersion)
			{
			case 0:
				return "Windows Vista/Server 2008";
			case 1:
				return "Windows 7/Server 2008 SP2";
			case 2:
				return "Windows 8/Server 2012";
			default:
				return "Unknown";
			}
		case 5:
			switch (vi.dwMinorVersion)
			{
			case 0:
				return "Windows 2000";
			case 1:
				return "Windows XP";
			case 2:
				return "Windows Server 2003/Windows Server 2003 R2";
			default:
				return "Unknown";
			}
		case 4:
			switch (vi.dwMinorVersion)
			{
			case 0:
				return "Windows 95/Windows NT 4.0";
			case 10:
				return "Windows 98";
			case 90:
				return "Windows ME";
			default:
				return "Unknown";
			}
		default:
			return "Unknown";
		}
#else
		return osName();
#endif
	}

	std::string Environment::osVersion()
	{
#ifdef WINDOWS
		OSVERSIONINFO vi;
		vi.dwOSVersionInfoSize = sizeof(vi);
		if (GetVersionEx(&vi) == 0) throw SystemException("Cannot get OS version information");
		std::ostringstream str;
		str << vi.dwMajorVersion << "." << vi.dwMinorVersion << " (Build " << (vi.dwBuildNumber & 0xFFFF);
		if (vi.szCSDVersion[0]) str << ": " << vi.szCSDVersion;
		str << ")";
		return str.str();
#else
		struct utsname uts;
		uname(&uts);
		return uts.release;
#endif
	}

	std::string Environment::osArchitecture()
	{
#ifdef WINDOWS
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		switch (si.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_INTEL:
			return "IA32";
		case PROCESSOR_ARCHITECTURE_MIPS:
			return "MIPS";
		case PROCESSOR_ARCHITECTURE_ALPHA:
			return "ALPHA";
		case PROCESSOR_ARCHITECTURE_PPC:
			return "PPC";
		case PROCESSOR_ARCHITECTURE_IA64:
			return "IA64";
#ifdef PROCESSOR_ARCHITECTURE_IA32_ON_WIN64
		case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
			return "IA64/32";
#endif
#ifdef PROCESSOR_ARCHITECTURE_AMD64
		case PROCESSOR_ARCHITECTURE_AMD64:
			return "AMD64";
#endif
		default:
			return "Unknown";
		}
#else
		struct utsname uts;
		uname(&uts);
		return uts.machine;
#endif
	}

	std::string Environment::nodeName()
	{
#ifdef WINDOWS
		char name[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD size = sizeof(name);
		if (GetComputerName(name, &size) == 0) throw SystemException("Cannot get computer name");
		return std::string(name);
#else
		struct utsname uts;
		uname(&uts);
		return uts.nodename;
#endif
	}

	void Environment::nodeId(NodeId& id)
	{
#ifdef WINDOWS
		std::memset(&id, 0, sizeof(id));

		PIP_ADAPTER_INFO pAdapterInfo;
		PIP_ADAPTER_INFO pAdapter = 0;
		ULONG len    = sizeof(IP_ADAPTER_INFO);
		pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
		// Make an initial call to GetAdaptersInfo to get
		// the necessary size into len
		DWORD rc = GetAdaptersInfo(pAdapterInfo, &len);
		if (rc == ERROR_BUFFER_OVERFLOW) 
		{
			delete [] reinterpret_cast<char*>(pAdapterInfo);
			pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[len]);
		}
		else if (rc != ERROR_SUCCESS)
		{
			return;
		}
		if (GetAdaptersInfo(pAdapterInfo, &len) == NO_ERROR) 
		{
			pAdapter = pAdapterInfo;
			bool found = false;
			while (pAdapter && !found) 
			{
				if (pAdapter->Type == MIB_IF_TYPE_ETHERNET && pAdapter->AddressLength == sizeof(id))
				{
					found = true;
					std::memcpy(&id, pAdapter->Address, pAdapter->AddressLength);
				}
				pAdapter = pAdapter->Next;
			}
		}
		delete [] reinterpret_cast<char*>(pAdapterInfo);
#else
		std::memset(&id, 0, sizeof(id));
		int fd = open("/sys/class/net/eth0/address", O_RDONLY);
		if (fd >= 0)
		{
			char buffer[18];
			int n = read(fd, buffer, 17);
			close(fd);
			if (n == 17)
			{
				buffer[n] = 0;
				if (std::sscanf(buffer, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &id[0], &id[1], &id[2], &id[3], &id[4], &id[5]) == 6)
					return;
			}
		}	

		// if that did not work, search active interfaces
		int sock = socket(PF_INET, SOCK_DGRAM, 0);
		if (sock == -1) return;
		// the following code is loosely based
		// on W. Richard Stevens, UNIX Network Programming, pp 434ff.
		int lastlen = 0;
		int len = 100*sizeof(struct ifreq);
		struct ifconf ifc;
		char* buf = 0;
		for (;;)
		{
			buf = new char[len];
			ifc.ifc_len = len;
			ifc.ifc_buf = buf;
			if (::ioctl(sock, SIOCGIFCONF, &ifc) < 0)
			{
				if (errno != EINVAL || lastlen != 0)
				{
					close(sock);
					delete [] buf;
					return;
				}
			}
			else
			{
				if (ifc.ifc_len == lastlen)
					break;
				lastlen = ifc.ifc_len;
			}
			len += 10*sizeof(struct ifreq);
			delete [] buf;
		}
		for (const char* ptr = buf; ptr < buf + ifc.ifc_len;)
		{
			const struct ifreq* ifr = reinterpret_cast<const struct ifreq*>(ptr);		
			int rc = ioctl(sock, SIOCGIFHWADDR, ifr);
			if (rc != -1)
			{
				const struct sockaddr* sa = reinterpret_cast<const struct sockaddr*>(&ifr->ifr_hwaddr);
				if (sa->sa_family == ARPHRD_ETHER)
				{
					std::memcpy(&id, sa->sa_data, sizeof(id));
					break;
				}
			}
			ptr += sizeof(struct ifreq);
		}
		close(sock);
		delete [] buf;
#endif
	}

	std::string Environment::nodeId()
	{
		NodeId id;
		nodeId(id);
		char result[18];
		tsnprintf(result, 18,"%02x:%02x:%02x:%02x:%02x:%02x",
			id[0],
			id[1],
			id[2],
			id[3],
			id[4],
			id[5]);
		return std::string(result);
	}

	unsigned Environment::processorCount()
	{
#ifdef WINDOWS
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		return si.dwNumberOfProcessors;
#else
		return sysconf(_SC_NPROCESSORS_ONLN);
#endif
	}

	uint32 Environment::libraryVersion()
	{
		return 0;
	}

	uint64 Environment::processorUsage()
	{
#ifdef _WINDOWS
		FILETIME dummy;
		FILETIME kerneltime;
		FILETIME usertime;
		BOOL sucess = ::GetProcessTimes(GetCurrentProcess(), &dummy, &dummy, &kerneltime, &usertime);
		if (sucess == FALSE)
		{
			return 0;
		}
		ULARGE_INTEGER ktime;
		ULARGE_INTEGER utime;
		ktime.HighPart = kerneltime.dwHighDateTime;
		ktime.LowPart = kerneltime.dwLowDateTime;
		utime.HighPart = usertime.dwHighDateTime;
		utime.LowPart = usertime.dwLowDateTime;
		f64 totaltime = static_cast<f64>(ktime.QuadPart + utime.QuadPart);
		totaltime /= 10;
		return static_cast<uint64>(totaltime);
#else
		rusage usage;
		if (getrusage(RUSAGE_SELF, &usage) != 0)
		{
			return 0;
		}
		uint64 k = usage.ru_utime.tv_sec * 1000000 + usage.ru_utime.tv_usec;
		uint64 u = usage.ru_stime.tv_sec * 1000000 + usage.ru_stime.tv_usec;
		return (k+u);
#endif
	}
	uint64 Environment::getRAMUsage()
	{
#ifdef _WINDOWS
		PROCESS_MEMORY_COUNTERS pmcex;
		::GetProcessMemoryInfo(GetCurrentProcess(), &pmcex, sizeof(pmcex));
		return pmcex.PagefileUsage;
#else
		std::ifstream memf;
		std::string line;
		std::string value;
		std::stringstream fname;
		char line2[100];
		f32 memusage;
		unsigned long pos = 0;
		unsigned long pid = getpid();
		fname<<"/proc"<<pid<<"/status";
		memf.open(fname.str().c_str());
		do 
		{
			pos = std::string::npos;
			memf.getline(line2, 100);
			line.assign(line2);
			pos = line.find("VmRSS");
		} while (pos == std::string::npos);
		pos = line.find(" ");
		++pos;
		value = line.substr(pos, std::string::npos);
		memusage = static_cast<f32>(atof(value.c_str()));
		memf.close();
		memusage *= 1024.0f;
		return memusage;
#endif
	}

	uint64 Environment::getTickCount()
	{
#ifdef _WINDOWS
		return ::GetTickCount();
#else
		timeval Time;
		if (gettimeofday(&Time, NULL) != 0)
		{
			return 0;
		}
		return (Time.tv_sec * 1000) + (Time.tv_usec/1000);
#endif
	}
}