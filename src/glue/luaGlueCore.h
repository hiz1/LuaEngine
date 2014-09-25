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

// state
extern int stateCount;


void openlib(lua_State *L);

int l_changeState(lua_State *L);
int l_count(lua_State *L);


  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
