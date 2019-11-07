#ifndef LUA_INTERPRETER_H
#define LUA_INTERPRETER_H

#ifdef __cplusplus
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif
#include "TextureCreator.h"

class LuaInterpreter {
private:
	lua_State *L;
public:
	LuaInterpreter();
	void open(const char* filename);
	~LuaInterpreter();

	bool insideTracks(int carX, int carY);
	int getNextMovement(int carX, int carY);
	void addToTrackTable(ObjectViewPtr track);
	void printTrackTable();

};

#endif // LUA_INTERPRETER_H
