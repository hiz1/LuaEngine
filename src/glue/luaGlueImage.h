//
//  luaGlueImage.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueImage__
#define __LuaGame001__luaGlueImage__

#include <stdio.h>
#include "ofMain.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
#include "TexturePlane.h"

// image
extern vector<ofPtr<TexturePlane> > images;

void openlib_image(lua_State *L);

int l_createImage(lua_State *L);
int l_deleteImage(lua_State *L);
int l_setPos(lua_State *L);
int l_rollImage(lua_State *L);
int l_setRollImage(lua_State *L);
int l_getRollImage(lua_State *L);
int l_panImage(lua_State *L);
int l_setPanImage(lua_State *L);
int l_getPanImage(lua_State *L);
int l_tiltImage(lua_State *L);
int l_setTiltImage(lua_State *L);
int l_getTiltImage(lua_State *L);
int l_setScale(lua_State *L);
int l_getPos(lua_State *L);
int l_getScale(lua_State *L);
int l_drawImage(lua_State *L);

#endif /* defined(__LuaGame001__luaGlueImage__) */
