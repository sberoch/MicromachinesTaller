#include "LuaInterpreter.h"
#include <iostream>

LuaInterpreter::LuaInterpreter() : L(luaL_newstate()) {
	luaL_openlibs(L);
}

void LuaInterpreter::open(const char* filename) {
	int result = luaL_dofile(L, filename);
	if (result != 0) throw std::runtime_error("LuaInterpreter: can't open file");
}

LuaInterpreter::~LuaInterpreter() {
	lua_close(L);
}