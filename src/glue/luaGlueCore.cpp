//
//  luaGlueCore.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "luaGlueCore.h"
#include "LuaUtils.h"

namespace core {

static const struct luaL_Reg engineLib_core [] = {
  {"changeState", l_changeState},
  {"count"      , l_count      },
  {NULL, NULL}
};

void openlib(lua_State *L) {
  luaL_register(L, "app", engineLib_core);
}

// state
int stateCount;



int l_changeState(lua_State *L) {
  string nextLua = luaL_checkstring(L, -1);
  luaL_loadfile(L, ofToDataPath(nextLua + ".lua").c_str());
  callLua(L, nextLua);
  callLuaFunc(L, "setup");
  stateCount = 0;
}

int l_count(lua_State *L) {
  lua_pushinteger(L, stateCount);
  return 1;
}


  
}
