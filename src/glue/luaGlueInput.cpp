//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "luaGlueInput.h"
#include "LuaUtils.h"

namespace input {

static const struct luaL_Reg engineLib [] = {
  {"cursor"     , l_cursor     },
  {"button"     , l_button     },
  {"mousePos"   , l_mousePos   },
  {"mouseButton", l_mouseButton},
  {NULL, NULL}
};

void openlib(lua_State *L) {
  luaL_register(L, "app", engineLib);
}

// keyboard
vector<char> buttonSettings;
bool cursorUp=false,cursorDown=false,cursorLeft=false,cursorRight=false;
vector<bool> buttons;
// mouse
int mouseX = 0, mouseY = 0;
bool mouseButtons[] = {false, false};

int l_cursor(lua_State *L) {
  int cursor = 5;
  if(     cursorUp   )cursor += 3;
  else if(cursorDown )cursor -= 3;
  if(     cursorLeft )cursor -= 1;
  else if(cursorRight)cursor += 1;
  lua_pushinteger(L, cursor);
  return 1;
}

int l_button(lua_State *L) {
  int buttonNo = luaL_checkint(L, 1);
  if(buttonNo < 1 || buttonNo > buttons.size()) {
    lua_pushboolean(L, 0);
    return 1;
  }
  lua_pushboolean(L, buttons[buttonNo-1]);
  return 1;
}

int l_mousePos(lua_State *L) {
  lua_pushinteger(L, mouseX);
  lua_pushinteger(L, mouseY);
  return 2;
}

int l_mouseButton(lua_State *L) {
  int buttonNo = luaL_checkint(L, 1);
  if(buttonNo <1 || buttonNo > 2) {
    lua_pushboolean(L, 0);
    return 1;
  }
  lua_pushboolean(L, mouseButtons[buttonNo-1]);
  return 1;
}
  
}
