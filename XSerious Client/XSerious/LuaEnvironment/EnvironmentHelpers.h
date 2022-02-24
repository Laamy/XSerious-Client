#pragma once

#define LUA_OK 0
#define LUA_ER 1

int lua_Print(lua_State* lua) {

	std::string a1 = lua_tostring(lua, 1);

	//Utils::Log("Lua just printed something!");
	//Utils::Log(a1.c_str());
	Game::hooks.Output(a1.c_str());

	return 0;
}

int lua_Warn(lua_State* lua) {

	std::string a1 = lua_tostring(lua, 1);
	Game::hooks.Warning(a1.c_str());

	return 0;
}

int lua_Info(lua_State* lua) {

	std::string a1 = lua_tostring(lua, 1);
	Game::hooks.Info(a1.c_str());

	return 0;
}

int lua_Error(lua_State* lua) {

	std::string a1 = lua_tostring(lua, 1);
	Game::hooks.Error(a1.c_str());

	return 0;
}