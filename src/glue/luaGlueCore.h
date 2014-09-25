//
//  luaGlueCore.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueCore__
#define __LuaGame001__luaGlueCore__

#include <stdio.h>
#include "ofMain.h"
#include "../font/ofxTrueTypeFontUC.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

// keyboard
extern vector<char> buttonSettings;
extern bool cursorUp,cursorDown,cursorLeft,cursorRight;
extern vector<bool> buttons;
// mouse
extern int mouseX, mouseY;
extern bool mouseButtons[];
// state
extern int stateCount;
// text
extern map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
extern ofPtr<ofxTrueTypeFontUC> currentFont;
extern Pivot currentTextPivot;
// sound
extern ofSoundPlayer         bgm;
extern ofSoundPlayer         bgs;
extern vector<ofPtr<ofSoundPlayer> > se;

void openlib_core(lua_State *L);

int l_changeState(lua_State *L);
int l_cursor(lua_State *L);
int l_button(lua_State *L);
int l_mousePos(lua_State *L);
int l_mouseButton(lua_State *L);
int l_count(lua_State *L);
int l_setFont(lua_State *L);
int l_setTextPivot(lua_State *L);
int l_drawString(lua_State *L);
int l_playBGM(lua_State *L);
int l_stopBGM(lua_State *L);
int l_playBGS(lua_State *L);
int l_stopBGS(lua_State *L);
int l_playSE(lua_State *L);

#endif /* defined(__LuaGame001__luaGlueCore__) */
