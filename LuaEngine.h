//
//  LuaEngine.h
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#ifndef __LuaGame001__LuaEngine__
#define __LuaGame001__LuaEngine__

#include "ofMain.h"
#include "lua/lua.hpp"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

class LuaEngine {
public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
private:
  lua_State *L;
};

#endif /* defined(__LuaGame001__LuaEngine__) */
