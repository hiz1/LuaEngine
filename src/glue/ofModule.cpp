//
//  luaGlueOF.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "ofModule.h"

namespace of {

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
  
  int l_ellipse(lua_State *L) {
    ofEllipse(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  
  int l_triangle(lua_State *L) {
    ofTriangle(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3),
               luaL_checknumber(L, 4), luaL_checknumber(L, 5), luaL_checknumber(L, 6));
  }
  
  int l_line(lua_State *L) {
    ofLine(luaL_checknumber(L, 1), luaL_checknumber(L, 2),
           luaL_checknumber(L, 3), luaL_checknumber(L, 4));
  }
  
  int l_pushMatrix(lua_State *L) {
    ofPushMatrix();
  }
  int l_popMatrix(lua_State *L) {
    ofPopMatrix();
  }
  int l_pushStyle(lua_State *L) {
    ofPushStyle();
  }
  int l_popStyle(lua_State *L) {
    ofPopStyle();
  }
  int l_translate(lua_State *L) {
    float z=0;
    if(lua_gettop(L) >= 3) z = luaL_checknumber(L, 3);
    ofTranslate(ofPoint(luaL_checknumber(L, 1), luaL_checknumber(L, 2), z));
  }
  int l_scale(lua_State *L) {
    float y, z=1;
    if(lua_gettop(L) == 1) y = luaL_checknumber(L, 1);
    else y = luaL_checknumber(L, 2);
    if(lua_gettop(L) >= 3) z = luaL_checknumber(L, 3);
    ofScale(luaL_checknumber(L, 1), y, z);
  }
  int l_rotate(lua_State *L) {
    ofRotate(luaL_checknumber(L, 1));
  }
  int l_rotateX(lua_State *L) {
    ofRotateX(luaL_checknumber(L, 1));
  }
  int l_rotateY(lua_State *L) {
    ofRotate(luaL_checknumber(L, 1));
  }
  int l_rotateZ(lua_State *L) {
    ofRotateZ(luaL_checknumber(L, 1));
  }

  
  
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
    {"ellipse", l_ellipse},
    {"triangle", l_triangle},
    {"line"   , l_line},
    {"pushMatrix", l_pushMatrix},
    {"popMatrix", l_popMatrix},
    {"pushStyle", l_pushStyle},
    {"popStyle", l_popStyle},
    {"translate", l_translate},
    {"scale"    , l_scale},
    {"rotate", l_rotate},
    {"rotateX", l_rotateX},
    {"rotateY", l_rotateY},
    {"rotateZ", l_rotateZ},
    {NULL, NULL}
  };
  
  void openlib(lua_State *L) {
    luaL_register(L, "app", engineLib_of);
  }
}
