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

void openlib_of(lua_State *L);

int l_setFrameRate(lua_State *L);
int l_getElapsedTimef(lua_State *L);
int l_getWidth(lua_State *L);
int l_getHeight(lua_State *L);
int l_background(lua_State *L);
int l_noFill(lua_State *L);
int l_fill(lua_State *L);
int l_setLineWidth(lua_State *L);
int l_setColor(lua_State *L);
int l_fromHSB(lua_State *L);
int l_rect(lua_State *L);
int l_rectRounded(lua_State *L);
int l_circle(lua_State *L);


#endif /* defined(__LuaGame001__luaGlueOF__) */
