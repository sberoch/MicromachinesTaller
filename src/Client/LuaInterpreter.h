#ifndef LUA_INTERPRETER_H
#define LUA_INTERPRETER_H

#ifdef __cplusplus
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif

class LuaInterpreter {
private:
	lua_State *L;
public:
	LuaInterpreter();
	void open(const char* filename);
	~LuaInterpreter();

	bool insideTrack(int carX, int carY, int trackX, int trackY);

};

#endif // LUA_INTERPRETER_H
