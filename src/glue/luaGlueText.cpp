//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "luaGlueText.h"
#include "LuaUtils.h"

namespace text {

  static const struct luaL_Reg engineLib [] = {
    {"setFont"    , l_setFont    },
    {"setTextPivot", l_setTextPivot},
    {"drawString" , l_drawString },
    {NULL, NULL}
  };

  void openlib(lua_State *L) {
    luaL_register(L, "app", engineLib);
  }
    
  // text
  map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
  ofPtr<ofxTrueTypeFontUC> currentFont;
  Pivot currentTextPivot;


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
  
}
