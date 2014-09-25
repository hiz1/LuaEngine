//
//  luaGlueOF.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "luaGlueOF.h"

static const struct luaL_Reg engineLib_of [] = {
  {"setFrameRate", l_setFrameRate},
  {"getElapsedTimef", l_getElapsedTimef},
  {"getWidth", l_getWidth},
  {"getHeight", l_getHeight},
  {"background", l_background},
  {"noFill", l_noFill},
  {"fill", l_fill},
  {"setLineWidth", l_setLineWidth},
  {"setColor", l_setColor},
  {"fromHSB", l_fromHSB},
  {"rect", l_rect},
  {"rectRounded", l_rectRounded},
  {"circle", l_circle},
  {NULL, NULL}
};

void openlib_of(lua_State *L) {
  luaL_register(L, "app", engineLib_of);
}

int l_setFrameRate(lua_State *L) {
  ofSetFrameRate(luaL_checknumber(L, 1));
  return 0;
}

int l_getElapsedTimef(lua_State *L) {
  lua_pushnumber(L, ofGetElapsedTimef());
  return 1;
}

int l_getWidth(lua_State *L) {
  lua_pushnumber(L, ofGetWidth());
  return 1;
}

int l_getHeight(lua_State *L) {
  lua_pushnumber(L, ofGetHeight());
  return 1;
}

int l_background(lua_State *L) {
  if(lua_gettop(L) == 1) {
    ofBackground(luaL_checknumber(L, 1));
  } else {
    ofBackground(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  }
}

int l_noFill(lua_State *L) {
  ofNoFill();
}

int l_fill(lua_State *L) {
  ofFill();
}

int l_setLineWidth(lua_State *L) {
  ofSetLineWidth(luaL_checknumber(L, 1));
}

int l_setColor(lua_State *L) {
  if(lua_gettop(L) == 1) {
    ofSetColor(luaL_checknumber(L, 1));
  } else if(lua_gettop(L) == 3) {
    ofSetColor(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), 255);
  } else {
    ofSetColor(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  
  return 0;
}

int l_fromHSB(lua_State *L) {
  const ofColor &color = ofColor::fromHsb(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
  double alpha = luaL_checknumber(L, 4);
  lua_pushnumber(L, color.r);
  lua_pushnumber(L, color.g);
  lua_pushnumber(L, color.b);
  lua_pushnumber(L, alpha);
  return 4;
}

int l_rect(lua_State *L) {
  ofRect(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  return 0;
}

int l_rectRounded(lua_State *L) {
  ofRectRounded(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4), luaL_checknumber(L, 5));
  return 0;
}

int l_circle(lua_State *L) {
  ofCircle(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
}
