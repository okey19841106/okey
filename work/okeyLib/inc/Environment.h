/********************************************************************
	created:	2015/01/09
	created:	15:07
	author:		okey
	
	purpose:	
*********************************************************************/
#ifndef __OKEY_ENVIRONMENT_H_
#define __OKEY_ENVIRONMENT_H_


namespace okey
{
	class Environment
	{
	public:
		typedef uint8 NodeId[6]; /// Ethernet address.

		static std::string get(const std::string& name); //返回环境变量
		static std::string get(const std::string& name, const std::string& defaultValue);

		static bool has(const std::string& name);//环境变量是否存在
		static void set(const std::string& name, const std::string& value);//设置环境变量

		static std::string osName();
		static std::string osDisplayName();
		static std::string osVersion();
		static std::string osArchitecture();

		static std::string nodeName();/// Returns the node (or host) name.
		static void nodeId(NodeId& id);
		static std::string nodeId();

		static unsigned processorCount();//处理器数量
		static uint32 libraryVersion();

		static uint64 processorUsage();
		static uint64 getRAMUsage();
		static uint64 getTickCount();

	private:
#ifndef WINDOWS
		typedef std::map<std::string, std::string> StringMap;

		static StringMap m_map;
		static FastMutex m_cMutex;
#endif
	};
}

#endif