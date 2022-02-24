#pragma once

#pragma region Imports

extern "C" {
#include "Lua\lua.h"
#include "Lua\lua.hpp"
#include "Lua\lualib.h"
#include "Lua\lauxlib.h"
#include "Lua\luaconf.h"
#include "Lua\llimits.h"
}

#include "EnvironmentHelpers.h"

#pragma endregion

class LuaManager { // TODO: add new environment as a function
public:
	const static void InitalizeLua() {
		//Utils::Log("Initalizing environment...");
	}

	const static void Execute(std::string script) {
		lua_State* luaEnv = luaL_newstate();
		luaL_openlibs(luaEnv);

#pragma region Register variables

		lua_register(luaEnv, "Print", lua_Print);
		lua_register(luaEnv, "print", lua_Print);

		lua_register(luaEnv, "Warn", lua_Warn);
		lua_register(luaEnv, "warn", lua_Warn);

		lua_register(luaEnv, "Info", lua_Info);
		lua_register(luaEnv, "info", lua_Info);

		lua_register(luaEnv, "Error", lua_Error);
		lua_register(luaEnv, "error", lua_Error);

#pragma endregion

		if (CheckError(luaL_dostring(luaEnv, script.c_str()))) {
			std::string err = lua_tostring(luaEnv, -1);
			HandleLuaError(err.c_str()); // handle error correctly.
		}
	}

	const static bool CheckError(int errorCode) {
		bool output = false;

		if (errorCode == LUA_ER)
			output = true;

		return output;
	}

	const static void HandleLuaError(const char* err) {
		//Utils::LogF(err);
		Game::hooks.Error(err);
	}
};