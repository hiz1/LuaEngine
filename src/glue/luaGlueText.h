//
//  luaGlueInput.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueText__
#define __LuaGame001__luaGlueText__

#include <stdio.h>
#include "ofMain.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"
#include "../font/ofxTrueTypeFontUC.h"

namespace text {

  // text
  extern map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
  extern ofPtr<ofxTrueTypeFontUC> currentFont;
  extern Pivot currentTextPivot;


  void openlib(lua_State *L);

  int l_setFont(lua_State *L);
  int l_setTextPivot(lua_State *L);
  int l_drawString(lua_State *L);
  
}

#endif /* defined(__LuaGame001__luaGlueCore__) */
