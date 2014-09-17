//
//  LuaEngine.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/15.
//
//

#include "LuaEngine.h"
#include "LuaUtils.h"
#include "luaGlueOF.h"

#pragma - mark gloval values
vector<char> buttonSettings;
bool cursorUp=false,cursorDown=false,cursorLeft=false,cursorRight=false;
vector<bool> buttons;
int mouseX = 0, mouseY = 0;
bool mouseButtons[] = {false, false};
int stateCount;
map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
ofPtr<ofxTrueTypeFontUC> currentFont;
Pivot currentTextPivot;

#pragma - mark glue


int l_changeState(lua_State *L) {
  string nextLua = luaL_checkstring(L, -1);
  luaL_loadfile(L, ofToDataPath(nextLua + ".lua").c_str());
  callLua(L, nextLua);
  callLuaFunc(L, "setup");
  stateCount = 0;
}

int l_cursor(lua_State *L) {
  int cursor = 5;
  if(     cursorUp   )cursor += 3;
  else if(cursorDown )cursor -= 3;
  if(     cursorLeft )cursor -= 1;
  else if(cursorRight)cursor += 1;
  lua_pushinteger(L, cursor);
  return 1;
}

int l_button(lua_State *L) {
  int buttonNo = luaL_checkint(L, 1);
  if(buttonNo < 1 || buttonNo > buttons.size()) {
    lua_pushboolean(L, 0);
    return 1;
  }
  lua_pushboolean(L, buttons[buttonNo-1]);
  return 1;
}

int l_mousePos(lua_State *L) {
  lua_pushinteger(L, mouseX);
  lua_pushinteger(L, mouseY);
  return 2;
}

int l_mouseButton(lua_State *L) {
  int buttonNo = luaL_checkint(L, 1);
  if(buttonNo <1 || buttonNo > 2) {
    lua_pushboolean(L, 0);
    return 1;
  }
  lua_pushboolean(L, mouseButtons[buttonNo-1]);
  return 1;
}

int l_count(lua_State *L) {
  lua_pushinteger(L, stateCount);
  return 1;
}

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


static const struct luaL_Reg engineLib [] = {
  {"changeState", l_changeState},
  {"cursor"     , l_cursor     },
  {"button"     , l_button     },
  {"mousePos"   , l_mousePos   },
  {"mouseButton", l_mouseButton},
  {"count"      , l_count      },
  {"setFont"    , l_setFont    },
  {"setTextPivot", l_setTextPivot},
  {"drawString" , l_drawString },
  {NULL, NULL}
};

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
  
  lua_close(L);

  // 最初のスクリプトを読み込み
  L = luaL_newstate();
  luaL_openlibs(L);
  luaL_register(L, "app", engineLib);
  luaL_register(L, "app", ofLib);
  luaL_loadfile(L, ofToDataPath("sharedData.lua").c_str());
  callLua(L, "sharedData");
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


