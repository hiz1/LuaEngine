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
#include "glue/luaGlueInput.h"
#include "glue/luaGlueSound.h"
#include "glue/luaGlueText.h"

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
    input::buttonSettings.push_back(toupper(key));
    input::buttons.push_back(false);
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
    text::fonts[id] = ofPtr<ofxTrueTypeFontUC>(new ofxTrueTypeFontUC());
    text::fonts[id]->loadFont(ttf, size);
    lua_pop(L, 1);
  }
  text::currentTextPivot = TOP_LEFT;
  
  // sound
  lua_getglobal(L, "se_chunnel");
  int seChunnel = luaL_checknumber(L, -1);
  sound::bgm.setLoop(true);
  sound::bgs.setLoop(true);
  for(int i=0;i<seChunnel;i++){
    sound::se.push_back(ofPtr<ofSoundPlayer>(new ofSoundPlayer()));
    sound::se[sound::se.size()-1]->unloadSound();
  }
  
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
  luaL_loadfile(L, ofToDataPath(start + ".lua").c_str());
  callLua(L, "start");
  callLuaFunc(L, "setup");
  
  core::stateCount = 0;
}

void LuaEngine::update() {
  callLuaFunc(L, "update");
  core::stateCount ++;
}

void LuaEngine::draw() {
  ofEnableAlphaBlending();
  callLuaFunc(L, "draw");
  ofSetColor(255, 255, 255, 255);
  ofDisableAlphaBlending();
}

void LuaEngine::keyPressed(int key) {
  if(key == OF_KEY_UP   )input::cursorUp    = true;
  if(key == OF_KEY_DOWN )input::cursorDown  = true;
  if(key == OF_KEY_LEFT )input::cursorLeft  = true;
  if(key == OF_KEY_RIGHT)input::cursorRight = true;
  for(int i=0;i<input::buttonSettings.size();i++) {
    if(toupper(key) == input::buttonSettings[i]) {
      input::buttons[i] = true;
      if(i == 0) {
//        ofNotifyEvent(dequeMessageEvent);
      }
    }
  }
}
void LuaEngine::keyReleased(int key) {
  if(key == OF_KEY_UP   )input::cursorUp    = false;
  if(key == OF_KEY_DOWN )input::cursorDown  = false;
  if(key == OF_KEY_LEFT )input::cursorLeft  = false;
  if(key == OF_KEY_RIGHT)input::cursorRight = false;
  for(int i=0;i<input::buttonSettings.size();i++) {
    if(toupper(key) == input::buttonSettings[i]) {
      input::buttons[i] = false;
    }
  }
  
}
void LuaEngine::mouseMoved(int x, int y ) {
  input::mouseX = x;
  input::mouseY = y;
}
void LuaEngine::mouseDragged(int x, int y, int button) {
  input::mouseX = x;
  input::mouseY = y;
  input::mouseButtons[button] = true;
  
}
void LuaEngine::mousePressed(int x, int y, int button) {
  input::mouseX = x;
  input::mouseY = y;
  input::mouseButtons[button] = true;
  
}
void LuaEngine::mouseReleased(int x, int y, int button) {
  input::mouseX = x;
  input::mouseY = y;
  input::mouseButtons[button] = false;
  
}


