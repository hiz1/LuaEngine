//
//  luaGlueCore.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "luaGlueCore.h"
#include "LuaUtils.h"

static const struct luaL_Reg engineLib_core [] = {
  {"changeState", l_changeState},
  {"cursor"     , l_cursor     },
  {"button"     , l_button     },
  {"mousePos"   , l_mousePos   },
  {"mouseButton", l_mouseButton},
  {"count"      , l_count      },
  {"setFont"    , l_setFont    },
  {"setTextPivot", l_setTextPivot},
  {"drawString" , l_drawString },
  {"playBGM"    , l_playBGM    },
  {"stopBGM"    , l_stopBGM    },
  {"playBGS"    , l_playBGS    },
  {"stopBGS"    , l_stopBGS    },
  {"playSE"     , l_playSE     },
  {NULL, NULL}
};

void openlib_core(lua_State *L) {
  luaL_register(L, "app", engineLib_core);
}

// keyboard
vector<char> buttonSettings;
bool cursorUp=false,cursorDown=false,cursorLeft=false,cursorRight=false;
vector<bool> buttons;
// mouse
int mouseX = 0, mouseY = 0;
bool mouseButtons[] = {false, false};
// state
int stateCount;
// text
map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
ofPtr<ofxTrueTypeFontUC> currentFont;
Pivot currentTextPivot;
// sound
ofSoundPlayer         bgm;
ofSoundPlayer         bgs;
vector<ofPtr<ofSoundPlayer> > se;


int l_changeState(lua_State *L) {
  string nextLua = luaL_checkstring(L, -1);
  luaL_loadfile(L, ofToDataPath(nextLua + ".lua").c_str());
  callLua(L, nextLua);
  callLuaFunc(L, "setup");
  stateCount = 0;
}

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

int l_count(lua_State *L) {
  lua_pushinteger(L, stateCount);
  return 1;
}

int l_setFont(lua_State *L) {
  string fontId = luaL_checkstring(L, 1);
  currentFont   = fonts[fontId];
  return 0;
}

int l_setTextPivot(lua_State *L) {
  string pivot = luaL_checkstring(L, 1);
  
  if(pivot == "top_left"     ) currentTextPivot = TOP_LEFT;
  else if(pivot == "top_center"   ) currentTextPivot = TOP_CENTER;
  else if(pivot == "top_right"    ) currentTextPivot = TOP_RIGHT;
  else if(pivot == "middle_left"  ) currentTextPivot = MIDDLE_LEFT;
  else if(pivot == "middle_center") currentTextPivot = MIDDLE_CENTER;
  else if(pivot == "middle _right") currentTextPivot = MIDDLE_RIGHT;
  else if(pivot == "bottom_left"  ) currentTextPivot = BOTTOM_LEFT;
  else if(pivot == "bottom_center") currentTextPivot = BOTTOM_CENTER;
  else if(pivot == "bottom_right" ) currentTextPivot = BOTTOM_RIGHT;
}

int l_drawString(lua_State *L) {
  string text = luaL_checkstring(L, 1);
  double x    = luaL_checknumber(L, 2);
  double y    = luaL_checknumber(L, 3);
  currentFont->drawString(text, x, y, currentTextPivot);
  return 0;
}

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
