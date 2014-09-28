//
//  luaGlueInput.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueSound__
#define __LuaGame001__luaGlueSound__

#include <stdio.h>
#include "ofMain.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

namespace sound {

  void openlib(lua_State *L);
  void initlib(int seChunnel);
  
  #pragma mark - lua
  void playBGM(string bgmFile, double volume = 1.0);
  void stopBGM();
  void playBGS(string bgsFile, double volume = 1.0);
  void stopBGS();
  bool playSE(string seFile, double volume = 1.0);
  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
