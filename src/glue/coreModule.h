//
//  luaGlueCore.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueCore__
#define __LuaGame001__luaGlueCore__

#include <stdio.h>
#include "ofMain.h"

#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

namespace core {
  void openlib(lua_State *L);
  void initlib();
  void update();

  #pragma mark - lua
  void changeState(lua_State *L, string nextState);
  int  count();

  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
