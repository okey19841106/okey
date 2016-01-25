/*****************************************************************************
	created: 2015-12-22
	author:  suxin
	purpose:                                                             
*****************************************************************************/

#ifndef __GALAXY_LUA_ENGINE_H__
#define __GALAXY_LUA_ENGINE_H__

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <set>
#include <string>
#include <vector>
#include "HashMap.h"

namespace okey
{

#define RET_NIL(L) {lua_pushnil(L); return 1;}
#define RET_BOOL(L,exp) { (exp)?lua_pushboolean(L,1):lua_pushboolean(L,0); return 1;}
#define RET_STRING(L, str) {lua_pushstring(L, str); return 1;}
#define RET_NUMBER(L, number) {lua_pushnumber(L, (number)); return 1;}
#define RET_INT(L, integer) {lua_pushinteger(L, integer); return 1;}

	struct LuaLoadScripts
	{
		std::set<std::string> _luaFiles;
	};

	template<typename T>
	struct RegType
	{
		const char* _name;
		int(*_func)(lua_State*, T*);
	};

	void report(lua_State*);

	struct LuaObjectBinding
	{
		int _fuctionReferences[128];
	};

	class LuaEngine
	{
	public:
		typedef hash_map<unsigned int, LuaObjectBinding> LuaObjectBindingMap;

		LuaEngine();
		virtual ~LuaEngine();
		virtual void Startup();
		virtual void LoadScripts();
		void ReStart();
		template<typename T>
		void PushValue(T value);

		template<typename T>
		void PushValue(T* value)
		{
			TLua<T>::Push(_lua_state, value);
		}
		
		template<typename T>
		T CheckValue(int narg);

		template<typename T>
		T* CheckObj(int narg)
		{
			T* ret = NULL;
			if (lua_isuserdata(_lua_state, narg))
			{
				ret = TLua<T>::Check(_lua_state, narg);
			}
			return ret;
		}

		virtual void RegisterCoreFunctions();
		virtual void RegisterGlobalFunctions();
		virtual void RegisterClassFunction();

		lua_State* GetLuaState() const{ return _lua_state; }

		void BeginCall(int refFunction);
		bool ExecuteCall(int params = 0, int res = 0);
		void EndCall(int res = 0);

		virtual void RegisterEvent(int regtype, unsigned int id, unsigned int evt, int functionRef){}
	protected:
		void Unload();
		void ScriptLoadDir(char* Dirname, LuaLoadScripts* pak);

		template<typename T>
		class TLua
		{
		public:
			typedef int(*mfp)(lua_State* L, T* ptr);
			typedef struct{ const char* _name; mfp _mfunc; } RegType;

			static void Register(lua_State* L)
			{
				lua_newtable(L);
				int methods = lua_gettop(L); //table
				luaL_newmetatable(L, T::_classname); //入栈
				int metatable = lua_gettop(L);
				luaL_newmetatable(L, "DO NOT TRASH"); //入栈
				lua_pop(L, 1); //出栈

				lua_pushvalue(L, methods); //复制一个栈
				lua_setglobal(L, T::_classname); //出栈

				lua_pushvalue(L, methods); //复制一个栈
				lua_setfield(L, metatable, "__metatable");//栈恢复

				lua_pushcfunction(L, index);
				lua_setfield(L, metatable, "__index"); //栈恢复 索引

				lua_pushcfunction(L, tostring_T);
				lua_setfield(L, metatable, "__tostring");//栈恢复 字符

				lua_pushcfunction(L, gc_T);
				lua_setfield(L, metatable, "__gc");//栈恢复 垃圾回收。

				lua_newtable(L);  //fuction
				lua_setmetatable(L, methods); //出一个跟第一次一样的元表

				for (RegType* l = ((RegType*)T::_methods); l->_name;++l)
				{
					lua_pushstring(L, l->_name);
					lua_pushlightuserdata(L, (void*)l);
					lua_pushcclosure(L, thunk, 1);
					lua_settable(L, methods);
				}

				lua_pop(L, 2);
			}
			//这个可以走lua的垃圾处理，当然是要gc = true
			static int Push(lua_State* L, T* obj, bool gc = false)
			{
				if (!obj)
				{
					lua_pushnil(L);
					return lua_gettop(L);
				}
				luaL_getmetatable(L, T::_classname);
				if (lua_isnil(L, -1))
				{
					luaL_error(L, "%s missing metatable", T::_classname);
				}
				int mt = lua_gettop(L);
				T** ptrHold = (T**)lua_newuserdata(L, sizeof(T**));
				int ud = lua_gettop(L);
				if (ptrHold != NULL)
				{
					*ptrHold = obj;
					lua_pushvalue(L, mt);
					lua_setmetatable(L, -2);
					char name[32];
					tostring(name, obj);
					lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
					if (lua_isnil(L, -1))
					{
						luaL_newmetatable(L, "DO NOT TRASH");
						lua_pop(L, 1);
					}
					lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
					if (gc == false)
					{
						lua_pushboolean(L, 1);
						lua_setfield(L, -2, name);
					}
					lua_pop(L, 1);
				}
				lua_settop(L, ud);
				lua_replace(L, mt);
				lua_settop(L, mt);
				return mt;
			}

			static T* Check(lua_State* L, int narg)
			{
				T** ptrHold = static_cast<T**>(lua_touserdata(L, narg));
				if (ptrHold == NULL)
				{
					return NULL;
				}
				return *ptrHold;
			}
		private:
			TLua();
			static int thunk(lua_State* L)
			{
				T* obj = Check(L, 1);
				lua_remove(L, 1);// remove self so member function args start at index 1
				RegType* l = static_cast<RegType*>(lua_touserdata(L, lua_upvalueindex(1)));
				return l->_mfunc(L, obj);
			}

			static int gc_T(lua_State* L)
			{
				T* obj = Check(L, 1);
				if (obj == NULL)
				{
					return 0;
				}
				lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
				if (lua_istable(L, -1))
				{
					::delete obj;
					obj = NULL;
				}
				lua_pop(L, 3);
				return 0;
			}

			static int tostring_T(lua_State* L)
			{
				char buff[128];
				T** ptrHold = (T**)lua_touserdata(L, 1);
				T* obj = *ptrHold;
				sprintf(buff, "%p", obj);
				lua_pushfstring(L, "%s (%s)", T::_classname, buff);
				return 1;
			}

			static void tostring(char* buff, void* obj)
			{
				sprintf(buff, "%p", obj);
			}

			static int index(lua_State* L)
			{
				lua_getglobal(L, T::_classname);
				const char* key = lua_tostring(L, 2);
				if (lua_istable(L, -1))
				{
					lua_pushvalue(L, 2);
					lua_rawget(L, -2);
					if (lua_isnil(L, -1))
					{
						lua_getmetatable(L, -2);
						if (lua_istable(L, -1))
						{
							lua_getfield(L, -1, "__index");
							if (lua_isfunction(L, -1))
							{
								lua_pushvalue(L, 1);
								lua_pushvalue(L, 2);
								lua_pcall(L, 2, 1, 0);
							}
							else if (lua_istable(L, -1))
							{
								lua_getfield(L, -1, key);
							}
							else
							{
								lua_pushnil(L);
							}
						}
					}
					else if (lua_istable(L, -1))
					{
						lua_pushvalue(L, 2);
						lua_rawget(L, -2);
					}
				}
				else
				{
					lua_pushnil(L);
				}
				lua_insert(L, 1);
				lua_settop(L, 1);
				return 1;
			}

		};
	protected:
		lua_State* _lua_state;
		//先不考虑多线程的问题。 
		std::string _dir;
	};

	template<>
	inline void LuaEngine::PushValue<bool>(bool value)
	{
		if (value)
		{
			lua_pushboolean(_lua_state, 1);
		}
		else
		{
			lua_pushboolean(_lua_state, 0);
		}
	}

	template<>
	inline void LuaEngine::PushValue<lua_State*>(lua_State* value)
	{
		if (value == NULL)
		{
			lua_pushnil(_lua_state);
		}
		else
		{
			lua_pushnil(value);
		}
	}

	template<>
	inline void LuaEngine::PushValue<int>(int value)
	{
		lua_pushinteger(_lua_state, value);
	}

	template<>
	inline void LuaEngine::PushValue<unsigned int>(unsigned int value)
	{
		lua_pushnumber(_lua_state, value);
	}

	template<>
	inline void LuaEngine::PushValue<float>(float value)
	{
		lua_pushnumber(_lua_state, value);
	}

	template<>
	inline void LuaEngine::PushValue<const char*>(const char* value)
	{
		lua_pushstring(_lua_state, value);
	}

	template<>
	inline bool LuaEngine::CheckValue<bool>(int narg)
	{
		if (lua_isboolean(_lua_state, narg))
		{
			return lua_toboolean(_lua_state, narg) > 0;
		}
		else if (lua_isnumber(_lua_state, narg))
		{
			return lua_isnumber(_lua_state, narg) > 0;
		}
		else
		{
			return true;
		}
	}

	template<>
	inline int LuaEngine::CheckValue<int>(int narg)
	{
		int ret = -1;
		if (lua_isnumber(_lua_state, narg))
		{
			ret = lua_tonumber(_lua_state, narg);
		}
		return ret;
	}

	template<>
	inline unsigned int LuaEngine::CheckValue<unsigned int>(int narg)
	{
		unsigned int ret = 0;
		if (lua_isnumber(_lua_state, narg))
		{
			ret = lua_tonumber(_lua_state, narg);
		}
		return ret;
	}

	template<>
	inline float LuaEngine::CheckValue<float>(int narg)
	{
		float ret = 0.0f;
		if (lua_isnumber(_lua_state, narg))
		{
			ret = lua_tonumber(_lua_state, narg);
		}
		return ret;
	}

	template<>
	inline const char* LuaEngine::CheckValue<const char*>(int narg)
	{
		const char* ret = NULL;
		if (lua_isstring(_lua_state, narg))
		{
			ret = lua_tostring(_lua_state, narg);
		}
		return ret;
	}
}

#endif