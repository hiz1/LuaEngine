//
//  LuaUtils.h
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#ifndef __LuaGame001__LuaUtils__
#define __LuaGame001__LuaUtils__

#include <iostream>
#include "lua/lua.hpp"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

void stackDump(lua_State *L);
void error(lua_State *L, const char *fmt, ...) ;
void callLua(lua_State *L, std::string category = "", int nargs = 0, int nresults = 0, int errfunc = 0);
void callLuaFunc(lua_State *L, std::string funcNm, int nargs = 0, int nresults = 0, int errfunc = 0);

#endif /* defined(__LuaGame001__LuaUtils__) */
