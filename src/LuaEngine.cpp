//
//  LuaEngine.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "LuaEngine.h"
#include "LuaUtils.h"
#include "glue/ofModule.h"
#include "glue/coreModule.h"
#include "glue/imageModule.h"
#include "glue/meshModule.h"
#include "glue/inputModule.h"
#include "glue/soundModule.h"
#include "glue/textModule.h"

#pragma - mark main

void LuaEngine::setup() {
  // ブート用情報を取得
  L = luaL_newstate();
  luaL_loadfile(L, ofToDataPath("boot.lua").c_str());
  callLua(L, "boot");
  // set first state
  lua_getglobal(L, "start");
  string start = luaL_checkstring(L, -1);
  // set framerate
  lua_getglobal(L, "frameRate");
  ofSetFrameRate(luaL_checknumber(L, -1));
  // set window width and height
  lua_getglobal(L, "window");
  lua_rawgeti(L, -1, 1);
  float width = luaL_checknumber(L,-1);
  lua_pop(L,1);
  lua_rawgeti(L, -1, 2);
  float height = luaL_checknumber(L,-1);
  lua_pop(L,1);
  ofSetWindowShape(width, height);
  // key config
  vector<char> keySettings;
  lua_getglobal(L, "buttons");
  int buttonNum = lua_objlen(L, -1);
  for(int i=1;i<=buttonNum;i++) {
    lua_rawgeti(L, -1, i);
    char key = luaL_checkstring(L, -1)[0];
    keySettings.push_back(toupper(key));
    lua_pop(L,1);
  }
  input::setKeySettings(keySettings);
  // font
  lua_getglobal(L, "fonts");
  vector<string> ids;
  vector<string> ttfPaths;
  vector<double> sizes;
  int fontNum = lua_objlen(L, -1);
  for(int i=1;i<=fontNum;i++) {
    lua_rawgeti(L, -1, i);
    lua_getfield(L, -1, "id");
    ids.push_back(luaL_checkstring(L,-1));
    lua_pop(L, 1);
    lua_getfield(L, -1, "ttf");
    ttfPaths.push_back(luaL_checkstring(L,-1));
    lua_pop(L, 1);
    lua_getfield(L, -1, "size");
    sizes.push_back(luaL_checkint(L,-1));
    lua_pop(L, 1);
    lua_pop(L, 1);
  }
  text::initlib(ids, ttfPaths, sizes, TOP_LEFT);
  
  // sound
  lua_getglobal(L, "se_chunnel");
  int seChunnel = luaL_checknumber(L, -1);
  sound::initlib(seChunnel);
  
  lua_close(L);

  // 最初のスクリプトを読み込み
  L = luaL_newstate();
  luaL_openlibs(L);
  core::openlib(L);
  of::openlib(L);
  mesh::openlib(L);
  image::openlib(L);
  input::openlib(L);
  sound::openlib(L);
  text::openlib(L);
  luaL_loadfile(L, ofToDataPath("core.lua").c_str());
  callLua(L, "core");
  lua_getglobal(L, "loadState");
  lua_pushstring(L, start.c_str());
  callLua(L, "loadState", 1,0);
  
  callLuaFunc(L, "_setup");
}

void LuaEngine::update() {
  callLuaFunc(L, "_update");
  core::update();
}

void LuaEngine::draw() {
  ofEnableAlphaBlending();
  callLuaFunc(L, "_draw");
  ofSetColor(255, 255, 255, 255);
  ofDisableAlphaBlending();
}

void LuaEngine::keyPressed(int key) {
  input::keyPressed(key);
}
void LuaEngine::keyReleased(int key) {
  input::keyReleased(key);
  
}
void LuaEngine::mouseMoved(int x, int y ) {
  input::mouseMoved(x, y);
}
void LuaEngine::mouseDragged(int x, int y, int button) {
  input::mouseDragged(x, y, button);
}
void LuaEngine::mousePressed(int x, int y, int button) {
  input::mousePressed(x, y, button);
}
void LuaEngine::mouseReleased(int x, int y, int button) {
  input::mouseReleased(x, y, button);
}


