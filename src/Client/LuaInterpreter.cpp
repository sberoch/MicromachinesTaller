#include "LuaInterpreter.h"
#include "../Common/Constants.h"
#include "../Common/Event/CommandEvent.h"
#include <iostream>

LuaInterpreter::LuaInterpreter() : L(luaL_newstate()) {
	luaL_openlibs(L);
}

void LuaInterpreter::open(const char* filename) {
	int result = luaL_dofile(L, filename);
	if (result != 0) throw std::runtime_error("LuaInterpreter: can't open file");

	lua_getglobal(L, "setupInitialValues");
	lua_pushnumber(L, HOR_PS_STRAIGHT_TRACK/2);
	lua_pushnumber(L, VER_PS_STRAIGHT_TRACK/2);
	lua_pushnumber(L, ACCELERATE);
	lua_pushnumber(L, TURN_RIGHT);
	lua_pushnumber(L, TURN_LEFT);
	lua_pushnumber(L, DESACCELERATE);
	lua_call(L,  6, 0);
}

void LuaInterpreter::addToTrackTable(ObjectViewPtr track) {
	lua_getglobal(L, "addToTrackTable");
	lua_pushnumber(L, track->getX());
	lua_pushnumber(L, track->getY());
	lua_pushnumber(L, track->getAngle());
	lua_call(L, 3, 0);
}

void LuaInterpreter::printTrackTable() {
	lua_getglobal(L, "printTrackTable");
	lua_call(L, 0, 0);
}

int LuaInterpreter::getNextMovement(int carX, int carY, int carAngle) {
	lua_getglobal(L, "getNextMovement");
	lua_pushnumber(L, carX);
	lua_pushnumber(L, carY);
	lua_pushnumber(L, carAngle);
	lua_call(L, 3, 1);
	int res = lua_tonumber(L, 1);
	lua_pop(L, 1);
	return res;
}

LuaInterpreter::~LuaInterpreter() {
	lua_close(L);
}