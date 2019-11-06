#include "LuaInterpreter.h"
#include "../Common/Constants.h"
#include <iostream>
#include <stdio.h>

LuaInterpreter::LuaInterpreter() : L(luaL_newstate()) {
	luaL_openlibs(L);
}

void LuaInterpreter::open(const char* filename) {
	int result = luaL_dofile(L, filename);
	if (result != 0) throw std::runtime_error("LuaInterpreter: can't open file");

	lua_getglobal(L, "setupInitialValues");
	lua_pushnumber(L, HOR_PS_STRAIGHT_TRACK/2);
	lua_pushnumber(L, VER_PS_STRAIGHT_TRACK/2);
	lua_call(L, 2, 0);
}

bool LuaInterpreter::insideTrack(int carX, int carY, int trackX, int trackY) {
	lua_getglobal(L, "checkInsideTrack");
	lua_pushnumber(L, carX);
	lua_pushnumber(L, carY);
	lua_pushnumber(L, trackX);
	lua_pushnumber(L, trackY);
	lua_call(L, 4, 1);
	int res = lua_tonumber(L, 1);
	lua_pop(L, 1);
	return (res == 0);
	
}

LuaInterpreter::~LuaInterpreter() {
	lua_close(L);
}