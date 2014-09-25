//
//  luaGlueInput.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueInput__
#define __LuaGame001__luaGlueInput__

#include <stdio.h>
#include "ofMain.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

namespace input {

// keyboard
extern vector<char> buttonSettings;
extern bool cursorUp,cursorDown,cursorLeft,cursorRight;
extern vector<bool> buttons;
// mouse
extern int mouseX, mouseY;
extern bool mouseButtons[];

void openlib(lua_State *L);

int l_cursor(lua_State *L);
int l_button(lua_State *L);
int l_mousePos(lua_State *L);
int l_mouseButton(lua_State *L);
  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
