//
//  luaGlueCore.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "coreModule.h"
#include "LuaUtils.h"

namespace core {

// state
int stateCount;



int l_changeState(lua_State *L) {
  changeState(L, luaL_checkstring(L, -1));
}

int l_count(lua_State *L) {
  lua_pushinteger(L, count());
  return 1;
}

  static const struct luaL_Reg engineLib_core [] = {
    {"changeState", l_changeState},
    {"count"      , l_count      },
    {NULL, NULL}
  };
  
  void openlib(lua_State *L) {
    luaL_register(L, "app", engineLib_core);
  }
  
  void initlib() {
    stateCount = 0;
  }
  
  void changeState(lua_State *L, string nextState) {
    luaL_loadfile(L, ofToDataPath(nextState + ".lua").c_str());
    callLua(L, nextState);
    callLuaFunc(L, "setup");
    stateCount = 0;
  }
  
  int count() {
    return stateCount;
  }
  
  void update() {
    stateCount ++;
  }

  
}
