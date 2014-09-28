//
//  luaGlueOF.h
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#ifndef __LuaGame001__luaGlueOF__
#define __LuaGame001__luaGlueOF__

#include "ofMain.h"

#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

namespace of {
  void openlib(lua_State *L);
}

#endif /* defined(__LuaGame001__luaGlueOF__) */
