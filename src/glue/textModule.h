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
#include "../utils/CommonUtil.h"

namespace text {
  void openlib(lua_State *L);
  void initlib(vector<string> ids, vector<string> ttfPaths, vector<double> sizes, Pivot pivot);
  
#pragma mark - lua
  void setFont(string fontId);
  void setTextPivot(string pivot);
  void drawString(string pivot, float x, float y);
  int  length(const string &text);
  string substr(const string &s, int begin, int length);
  string paragraph(const string &s, int col, int row);
  ofVec2f textSize(const string &s, const string &fontId);

}

#endif /* defined(__LuaGame001__luaGlueCore__) */
