#include "PreCom.h"
#include "LuaEngine.h"


namespace okey
{
	void report(lua_State* L)
	{
		int count = lua_gettop(L);
		while (count > 0)
		{
			const char* msg = lua_tostring(L, -1);
			printf("%s\n", msg);
			lua_pop(L, 1);
			--count;
		}
	}

	LuaEngine::LuaEngine()
	{

	}
	LuaEngine::~LuaEngine()
	{
		
	}

	void LuaEngine::Startup()
	{
		printf("LuaEngine Start......");
		_lua_state = lua_open();

		LoadScripts();
	}

	void LuaEngine::LoadScripts()
	{
		LuaLoadScripts rtn;
		printf("Scanning Script-Directories......");
		ScriptLoadDir((char*)_dir.c_str(), &rtn);

		uint32 cnt = 0;
		luaL_openlibs(_lua_state);
		RegisterCoreFunctions();
		printf("Loading Scripts......");

		for (std::set<std::string>::iterator itr = rtn._luaFiles.begin(); itr != rtn._luaFiles.end(); ++itr)
		{
			if (luaL_loadfile(_lua_state, itr->c_str()) != 0)
			{
				printf("Loading %s failed......", itr->c_str());
				report(_lua_state);
			}
			else
			{
				if (lua_pcall(_lua_state, 0, 0, 0) != 0)
				{
					printf("Loading %s failed......", itr->c_str());
					report(_lua_state);
				}
				else
				{
					printf("Loaded %s.", itr->c_str());
				}
			}
			++cnt;
		}
		printf("Loaded %u lua scripts....", cnt);
	}

	void LuaEngine::ReStart()
	{
		printf("LuaEngine Restart......");
		Unload();
		LoadScripts();
	}

	void LuaEngine::RegisterCoreFunctions()
	{
		RegisterGlobalFunctions();
		RegisterClassFunction();
	}

	void LuaEngine::RegisterGlobalFunctions()
	{
	}
	void LuaEngine::RegisterClassFunction()
	{
	}
	void LuaEngine::Unload()
	{
		lua_close(_lua_state);
	}

	void LuaEngine::ScriptLoadDir(char* Dirname, LuaLoadScripts* pak)
	{
		printf("Scanning Directory %s", Dirname);
#ifdef _WINDOWS
		HANDLE hFile;
		WIN32_FIND_DATA FindData;
		memset(&FindData, 0, sizeof(FindData));
		char SearchName[MAX_PATH];
		strcpy(SearchName, Dirname);
		strcat(SearchName, "/*.*");
		hFile = FindFirstFile(SearchName, &FindData);
		FindNextFile(hFile, &FindData);
		while (FindNextFile(hFile, &FindData))
		{
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				strcpy(SearchName, Dirname);
				strcat(SearchName, "/");
				strcat(SearchName, FindData.cFileName);
				ScriptLoadDir(SearchName, pak);
			}
			else
			{
				std::string fname = Dirname;
				fname += "/";
				fname += FindData.cFileName;
				size_t len = strlen(fname.c_str());
				int i = 0;
				char ext[MAX_PATH];
				while (len > 0)
				{
					ext[i++] = fname[--len];
					if (fname[len] == '.')
						break;
				}
				ext[i++] = '\0';
				if (!_stricmp(ext, "aul."))
				{
					pak->_luaFiles.insert(fname);
				}
			}
		}
#else
#endif // _WINDOWS

	}

	void LuaEngine::BeginCall(int r)
	{
		lua_settop(_lua_state, 0);
		lua_getref(_lua_state, r);
	}

	bool LuaEngine::ExecuteCall(int params, int res)
	{
		bool ret = true;
		int top = lua_gettop(_lua_state);
		if (strcmp(luaL_typename(_lua_state, top - params), "function"))
		{
			ret = false;
			if (params > 0)
			{
				for (int i = top; i >= (top - params); --i)
				{
					if (!lua_isnone(_lua_state, i))
					{
						lua_remove(_lua_state, i);
					}
				}
			}
		}
		else
		{
			if (lua_pcall(_lua_state, params, res, 0))
			{
				report(_lua_state);
				ret = false;
			}
		}
		return ret;
	}

	void LuaEngine::EndCall(int res)
	{
		for (int i = res; i >= 0; --i)
		{
			if (!lua_isnone(_lua_state, i))
			{
				lua_remove(_lua_state, i);
			}
		}
	}
}