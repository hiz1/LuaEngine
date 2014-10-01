//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "soundModule.h"
#include "LuaUtils.h"

namespace sound {
  // sound
  ofSoundPlayer         bgm;
  ofSoundPlayer         bgs;
  vector<ofPtr<ofSoundPlayer> > se;


  int l_playBGM(lua_State *L) {
    if(lua_gettop(L) >= 2) {
      playBGM(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    } else {
      playBGM(luaL_checkstring(L, 1));
    }
  }
  
  int l_stopBGM(lua_State *L) {
    stopBGM();
  }
  
  int l_playBGS(lua_State *L) {
    if(lua_gettop(L) >= 2) {
      playBGS(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    } else {
      playBGS(luaL_checkstring(L, 1));
    }
  }
  
  int l_stopBGS(lua_State *L) {
    stopBGS();
  }
  
  int l_playSE(lua_State *L) {
    bool success;
    if(lua_gettop(L) >= 2) {
      success = playSE(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    } else {
      success = playSE(luaL_checkstring(L, 1));
    }
    lua_pushboolean(L, success);
    return 1;
  }
  
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
  
  void initlib(int seChunnel) {
    sound::bgm.setLoop(true);
    sound::bgs.setLoop(true);
    for(int i=0;i<seChunnel;i++){
      sound::se.push_back(ofPtr<ofSoundPlayer>(new ofSoundPlayer()));
      sound::se[sound::se.size()-1]->unloadSound();
    }

  }
  
  void playBGM(string bgmFile, double volume) {
    bgm.loadSound("BGM/" + bgmFile, true);
    bgm.setVolume(volume);
    bgm.play();
  }
  
  void stopBGM() {
    bgm.stop();
  }
  
  void playBGS(string bgsFile, double volume) {
    bgs.loadSound("BGS/" + bgsFile, true);
    bgs.setVolume(volume);
    bgs.play();
  }
  
  void stopBGS() {
    bgs.stop();
  }
  
  bool playSE(string seFile, double volume) {
    for(ofPtr<ofSoundPlayer> s : se) {
      if(!s->getIsPlaying()) {
        s->loadSound("SE/" + seFile, true);
        s->setVolume(volume);
        s->play();
        return true;
      }
    }
    return false;
  }
  
}
