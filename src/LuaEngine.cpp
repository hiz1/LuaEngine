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
#include "TexturePlane.h"

#pragma - mark gloval values
// keyboard
vector<char> buttonSettings;
bool cursorUp=false,cursorDown=false,cursorLeft=false,cursorRight=false;
vector<bool> buttons;
// mouse
int mouseX = 0, mouseY = 0;
bool mouseButtons[] = {false, false};
// state
int stateCount;
// text
map<string, ofPtr<ofxTrueTypeFontUC> > fonts;
ofPtr<ofxTrueTypeFontUC> currentFont;
Pivot currentTextPivot;
// image
vector<ofPtr<TexturePlane> > images;
// sound
ofSoundPlayer         bgm;
ofSoundPlayer         bgs;
vector<ofPtr<ofSoundPlayer> > se;

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

#pragma mark - image module

int l_createImage(lua_State *L) {
  string imageFile = luaL_checkstring(L, 1);
  images.push_back(ofPtr<TexturePlane>(new TexturePlane()));
  images[images.size()-1]->setImage(ofToDataPath(imageFile));
  TexturePlane **a = (TexturePlane **)lua_newuserdata(L, sizeof(TexturePlane *));
  *a = images[images.size()-1].get();
  luaL_getmetatable(L, "app.image");
  lua_setmetatable(L, -2);
  return 1;
}

int l_deleteImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  for(vector<ofPtr<TexturePlane> >::iterator ite = images.begin(); ite != images.end(); ite ++) {
    if((*ite).get() == image) {
      images.erase(ite);
      return 0;
    }
  }
  return 0;
}

int l_setPos(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  float z = 0;
  if(lua_gettop(L) >= 4) {
    z = luaL_checknumber(L, 4);
  }
  image->setPosition(luaL_checknumber(L, 2), luaL_checknumber(L, 3), z);
  lua_pushlightuserdata(L, image);
  return 1;
}

int l_rollImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->roll(luaL_checknumber(L, 2));
  return 0;
}

int l_setRollImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->roll(luaL_checknumber(L, 2) - image->getRoll());
  return 0;
}

int l_getRollImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  lua_pushnumber(L, image->getRoll());
  return 1;
}

int l_panImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->pan(luaL_checknumber(L, 2));
  return 0;
}

int l_setPanImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->pan(luaL_checknumber(L, 2) - image->getHeading());
  return 0;
}

int l_getPanImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  lua_pushnumber(L, image->getHeading());
  return 1;
}

int l_tiltImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->tilt(luaL_checknumber(L, 2));
  return 0;
}

int l_setTiltImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->tilt(luaL_checknumber(L, 2) - image->getPitch());
  return 0;
}

int l_getTiltImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  lua_pushnumber(L, image->getPitch());
  return 1;
}


int l_setScale(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->setScale(luaL_checknumber(L, 2), luaL_checknumber(L, 3), 1);
  lua_pushlightuserdata(L, image);
  return 1;
}

int l_getPos(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  ofVec3f vec = image->getPosition();
  lua_pushnumber(L, vec.x);
  lua_pushnumber(L, vec.y);
  lua_pushnumber(L, vec.z);
  return 3;
}


int l_getScale(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  ofVec3f vec = image->getScale();
  lua_pushnumber(L, vec.x);
  lua_pushnumber(L, vec.y);
  lua_pushnumber(L, vec.z);
  return 3;
}

int l_drawImage(lua_State *L) {
  TexturePlane *image = *(TexturePlane **)lua_touserdata(L, 1);
  image->draw();
}

int l_playBGM(lua_State *L) {
  bgm.loadSound(luaL_checkstring(L, 1), true);
  if(lua_gettop(L) >= 2) {
    bgm.setVolume(luaL_checknumber(L, 2));
  } else {
    bgm.setVolume(1.0);
  }
  bgm.play();
}

int l_stopBGM(lua_State *L) {
  bgm.stop();
}

int l_playBGS(lua_State *L) {
  bgs.loadSound(luaL_checkstring(L, 1), true);
  if(lua_gettop(L) >= 2) {
    bgs.setVolume(luaL_checknumber(L, 2));
  } else {
    bgs.setVolume(1.0);
  }
  bgs.play();
}

int l_stopBGS(lua_State *L) {
  bgs.stop();
}

int l_playSE(lua_State *L) {
  for(ofPtr<ofSoundPlayer> s : se) {
    if(!s->getIsPlaying()) {
      s->loadSound(luaL_checkstring(L, 1), true);
      if(lua_gettop(L) >= 2) {
        s->setVolume(luaL_checknumber(L, 2));
      } else {
        s->setVolume(1.0);
      }
      s->play();
      lua_pushboolean(L, 1);
      return 1;
    }
  }
  lua_pushboolean(L, 0);
  return 1;
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
  {"playBGM"    , l_playBGM    },
  {"stopBGM"    , l_stopBGM    },
  {"playBGS"    , l_playBGS    },
  {"stopBGS"    , l_stopBGS    },
  {"playSE"     , l_playSE     },
  {NULL, NULL}
};

static const struct luaL_Reg engineLib_image_f [] = {
  {"new"        , l_createImage  },
  {NULL, NULL}
};

static const struct luaL_Reg engineLib_image_m [] = {
  {"delete"     , l_deleteImage},
  {"setPos"     , l_setPos     },
  {"setScale"   , l_setScale   },
  {"getPos"     , l_getPos     },
  {"getScale"   , l_getScale   },
  {"draw"       , l_drawImage  },
  {"roll"       , l_rollImage  },
  {"setRoll"    , l_setRollImage},
  {"getRoll"    , l_getRollImage},
  {"pan"        , l_panImage  },
  {"setPan"     , l_setPanImage},
  {"getPan"     , l_getPanImage},
  {"tilt"       , l_tiltImage  },
  {"setTilt"    , l_setTiltImage},
  {"getTilt"    , l_getTiltImage},
  {NULL, NULL}

};

void setupImageModule(lua_State *L) {
  lua_settop(L, 0);
  luaL_newmetatable(L, "app.image");
  // set GC
  lua_pushstring(L, "__gc");
  lua_pushcfunction(L, l_deleteImage);
  stackDump(L);
  lua_settable(L, -3);
  stackDump(L);
  // set method
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_register(L, NULL, engineLib_image_m);
  // set constructer
  luaL_register(L, "image", engineLib_image_f);
}

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
  luaL_register(L, "app", engineLib);
  luaL_register(L, "app", ofLib);
  // image
  setupImageModule(L);
  
  luaL_loadfile(L, ofToDataPath("core.lua").c_str());
  callLua(L, "core");
  luaL_loadfile(L, ofToDataPath(start + ".lua").c_str());
  callLua(L, "start");
  callLuaFunc(L, "_setup");
  
  stateCount = 0;
}

void LuaEngine::update() {
  callLuaFunc(L, "_update");
  stateCount ++;
}

void LuaEngine::draw() {
  ofEnableAlphaBlending();
  callLuaFunc(L, "_draw");
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


