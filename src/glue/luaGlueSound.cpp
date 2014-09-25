//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "luaGlueSound.h"
#include "LuaUtils.h"

namespace sound {

  static const struct luaL_Reg engineLib [] = {
    {"playBGM"    , l_playBGM    },
    {"stopBGM"    , l_stopBGM    },
    {"playBGS"    , l_playBGS    },
    {"stopBGS"    , l_stopBGS    },
    {"playSE"     , l_playSE     },
    {NULL, NULL}
  };

  void openlib(lua_State *L) {
    luaL_register(L, "app", engineLib);
  }
    
  // sound
  ofSoundPlayer         bgm;
  ofSoundPlayer         bgs;
  vector<ofPtr<ofSoundPlayer> > se;


  int l_playBGM(lua_State *L) {
    bgm.loadSound(luaL_checkstring(L, 1), true);
    if(lua_gettop(L) >= 2) {
      bgm.setVolume(luaL_checknumber(L, 2));
    } else {
      bgm.setVolume(1.0);
    }
    bgm.play();
  }
  
  int l_stopBGM(lua_State *L) {
    bgm.stop();
  }
  
  int l_playBGS(lua_State *L) {
    bgs.loadSound(luaL_checkstring(L, 1), true);
    if(lua_gettop(L) >= 2) {
      bgs.setVolume(luaL_checknumber(L, 2));
    } else {
      bgs.setVolume(1.0);
    }
    bgs.play();
  }
  
  int l_stopBGS(lua_State *L) {
    bgs.stop();
  }
  
  int l_playSE(lua_State *L) {
    for(ofPtr<ofSoundPlayer> s : se) {
      if(!s->getIsPlaying()) {
        s->loadSound(luaL_checkstring(L, 1), true);
        if(lua_gettop(L) >= 2) {
          s->setVolume(luaL_checknumber(L, 2));
        } else {
          s->setVolume(1.0);
        }
        s->play();
        lua_pushboolean(L, 1);
        return 1;
      }
    }
    lua_pushboolean(L, 0);
    return 1;
  }
  
}
