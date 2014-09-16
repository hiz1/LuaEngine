//
//  luaGlueOF.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "luaGlueOF.h"

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
  ofBackground(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3));
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
  ofSetColor(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
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
