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
  
  void openlib(lua_State *L);
  void setKeySettings(vector<char> settings);
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  
#pragma mark - lua
  int     cursor();
  bool    button(int buttonNo);
  ofVec2f mousePos();
  bool    mouseButton(int buttonNo);
  
  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
