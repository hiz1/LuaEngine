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

  // sound
  extern ofSoundPlayer         bgm;
  extern ofSoundPlayer         bgs;
  extern vector<ofPtr<ofSoundPlayer> > se;


  void openlib(lua_State *L);

  int l_playBGM(lua_State *L);
  int l_stopBGM(lua_State *L);
  int l_playBGS(lua_State *L);
  int l_stopBGS(lua_State *L);
  int l_playSE(lua_State *L);
  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
