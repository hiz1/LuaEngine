//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "textModule.h"
#include "LuaUtils.h"

namespace text {
  map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
  ofPtr<ofxTrueTypeFontUC> currentFont;
  Pivot currentTextPivot;

#pragma mark - glue code
  int l_setFont(lua_State *L) {
    setFont(luaL_checkstring(L, 1));
    return 0;
  }
  
  int l_setTextPivot(lua_State *L) {
    setTextPivot(luaL_checkstring(L, 1));
  }
  
  int l_drawString(lua_State *L) {
    drawString(luaL_checkstring(L, 1),
               luaL_checknumber(L, 2),
               luaL_checknumber(L, 3));
    return 0;
  }
  
  static const struct luaL_Reg engineLib [] = {
    {"setFont"    , l_setFont    },
    {"setTextPivot", l_setTextPivot},
    {"drawString" , l_drawString },
    {NULL, NULL}
  };
  
  void openlib(lua_State *L) {
    luaL_register(L, "app", engineLib);
  }
  
  void initlib(vector<string> ids, vector<string> ttfPaths, vector<double> sizes, Pivot pivot) {
    for(int i=0;i<ids.size();i++) {
      fonts[ids[i]] = ofPtr<ofxTrueTypeFontUC>(new ofxTrueTypeFontUC());
      fonts[ids[i]]->loadFont(ttfPaths[i], sizes[i]);
    }
    text::currentTextPivot = pivot;

  }
  
#pragma mark - module contents
  void setFont(string fontId) {
    currentFont   = fonts[fontId];
  }
  
  void setTextPivot(string pivot) {
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
  
  void drawString(string text, float x, float y) {
    currentFont->drawString(text, x, y, currentTextPivot);
  }
  
}
