//
//  LuaEngine.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "LuaEngine.h"
#include "LuaUtils.h"
#include "TexturePlane.h"
#include "glue/luaGlueOF.h"
#include "glue/luaGlueCore.h"
#include "glue/luaGlueImage.h"
#include "glue/luaGlueMesh.h"


#pragma mark - image module





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
  lua_getglobal(L, "buttons");
  int buttonNum = lua_objlen(L, -1);
  for(int i=1;i<=buttonNum;i++) {
    lua_rawgeti(L, -1, i);
    char key = luaL_checkstring(L, -1)[0];
    buttonSettings.push_back(toupper(key));
    buttons.push_back(false);
    lua_pop(L,1);
  }
  // font
  lua_getglobal(L, "fonts");
  int fontNum = lua_objlen(L, -1);
  for(int i=1;i<=fontNum;i++) {
    lua_rawgeti(L, -1, i);
    lua_getfield(L, -1, "id");
    string id = luaL_checkstring(L,-1);
    lua_pop(L, 1);
    lua_getfield(L, -1, "ttf");
    string ttf = luaL_checkstring(L,-1);
    lua_pop(L, 1);
    lua_getfield(L, -1, "size");
    int size = luaL_checkint(L,-1);
    lua_pop(L, 1);
    fonts[id] = ofPtr<ofxTrueTypeFontUC>(new ofxTrueTypeFontUC());
    fonts[id]->loadFont(ttf, size);
    lua_pop(L, 1);
  }
  currentTextPivot = TOP_LEFT;
  
  // sound
  lua_getglobal(L, "se_chunnel");
  int seChunnel = luaL_checknumber(L, -1);
  bgm.setLoop(true);
  bgs.setLoop(true);
  for(int i=0;i<seChunnel;i++){
    se.push_back(ofPtr<ofSoundPlayer>(new ofSoundPlayer()));
    se[se.size()-1]->unloadSound();
  }
  
  lua_close(L);

  // 最初のスクリプトを読み込み
  L = luaL_newstate();
  luaL_openlibs(L);
  openlib_of(L);
  openlib_core(L);
  openlib_image(L);
  openlib_mesh(L);
  luaL_loadfile(L, ofToDataPath("core.lua").c_str());
  callLua(L, "core");
  luaL_loadfile(L, ofToDataPath(start + ".lua").c_str());
  callLua(L, "start");
  callLuaFunc(L, "setup");
  
  stateCount = 0;
}

void LuaEngine::update() {
  callLuaFunc(L, "update");
  stateCount ++;
}

void LuaEngine::draw() {
  ofEnableAlphaBlending();
  callLuaFunc(L, "draw");
  ofSetColor(255, 255, 255, 255);
  ofDisableAlphaBlending();
}

void LuaEngine::keyPressed(int key) {
  if(key == OF_KEY_UP   )cursorUp    = true;
  if(key == OF_KEY_DOWN )cursorDown  = true;
  if(key == OF_KEY_LEFT )cursorLeft  = true;
  if(key == OF_KEY_RIGHT)cursorRight = true;
  for(int i=0;i<buttonSettings.size();i++) {
    if(toupper(key) == buttonSettings[i]) {
      buttons[i] = true;
      if(i == 0) {
//        ofNotifyEvent(dequeMessageEvent);
      }
    }
  }
}
void LuaEngine::keyReleased(int key) {
  if(key == OF_KEY_UP   )cursorUp    = false;
  if(key == OF_KEY_DOWN )cursorDown  = false;
  if(key == OF_KEY_LEFT )cursorLeft  = false;
  if(key == OF_KEY_RIGHT)cursorRight = false;
  for(int i=0;i<buttonSettings.size();i++) {
    if(toupper(key) == buttonSettings[i]) {
      buttons[i] = false;
    }
  }
  
}
void LuaEngine::mouseMoved(int x, int y ) {
  mouseX = x;
  mouseY = y;
}
void LuaEngine::mouseDragged(int x, int y, int button) {
  mouseX = x;
  mouseY = y;
  mouseButtons[button] = true;
  
}
void LuaEngine::mousePressed(int x, int y, int button) {
  mouseX = x;
  mouseY = y;
  mouseButtons[button] = true;
  
}
void LuaEngine::mouseReleased(int x, int y, int button) {
  mouseX = x;
  mouseY = y;
  mouseButtons[button] = false;
  
}


