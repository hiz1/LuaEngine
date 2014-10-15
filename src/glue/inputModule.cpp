//
//  luaGlueInput.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "inputModule.h"
#include "LuaUtils.h"

namespace input {
  vector<char> keySettings;
  bool cursorUp=false,cursorDown=false,cursorLeft=false,cursorRight=false;
  vector<bool> buttons;
  // mouse
  int mouseX = 0, mouseY = 0;
  bool mouseButtons[] = {false, false};

  #pragma mark - glue code
  
  int l_cursor(lua_State *L) {
    lua_pushinteger(L, cursor());
    return 1;
  }

  int l_button(lua_State *L) {
    lua_pushboolean(L, button(luaL_checkint(L, 1)));
    return 1;
  }

  int l_mousePos(lua_State *L) {
    ofVec2f pos = mousePos();
    lua_pushinteger(L, pos.x);
    lua_pushinteger(L, pos.y);
    return 2;
  }

  int l_mouseButton(lua_State *L) {
    lua_pushboolean(L, mouseButton(luaL_checkint(L, 1)));
    return 1;
  }
  
  static const struct luaL_Reg keyboardLib [] = {
    {"cursor"     , l_cursor     },
    {"button"     , l_button     },
    {NULL, NULL}
  };
  
  static const struct luaL_Reg mouseLib [] = {
    {"pos"   , l_mousePos   },
    {"button", l_mouseButton},
    {NULL, NULL}
  };
  
  void openlib(lua_State *L) {
    luaL_register(L, "key", keyboardLib);
    luaL_register(L, "mouse", mouseLib);
  }
  
  #pragma mark - module contents
  
  int cursor() {
    int cursor = 5;
    if(     cursorUp   )cursor += 3;
    else if(cursorDown )cursor -= 3;
    if(     cursorLeft )cursor -= 1;
    else if(cursorRight)cursor += 1;
    return cursor;
  }
  
  bool button(int buttonNo) {
    if(buttonNo < 1 || buttonNo > buttons.size()) {
      return false;
    }
    return buttons[buttonNo-1];
  }
  
  ofVec2f mousePos() {
    return ofVec2f(mouseX, mouseY);
  }
  
  bool mouseButton(int buttonNo) {
    if(buttonNo < 1 || buttonNo > 2) {
      return false;
    }
    return mouseButtons[buttonNo-1];
  }
  
  void setKeySettings(vector<char> settings) {
    keySettings = settings;
    for(int i=0;i<settings.size();i++) {
      buttons.push_back(false);
    }
  }
  
  void keyPressed(int key) {
    if(key == OF_KEY_UP   )input::cursorUp    = true;
    if(key == OF_KEY_DOWN )input::cursorDown  = true;
    if(key == OF_KEY_LEFT )input::cursorLeft  = true;
    if(key == OF_KEY_RIGHT)input::cursorRight = true;
    for(int i=0;i<input::keySettings.size();i++) {
      if(toupper(key) == input::keySettings[i]) {
        input::buttons[i] = true;
        if(i == 0) {
          //        ofNotifyEvent(dequeMessageEvent);
        }
      }
    }
  }
  void keyReleased(int key) {
    if(key == OF_KEY_UP   )input::cursorUp    = false;
    if(key == OF_KEY_DOWN )input::cursorDown  = false;
    if(key == OF_KEY_LEFT )input::cursorLeft  = false;
    if(key == OF_KEY_RIGHT)input::cursorRight = false;
    for(int i=0;i<input::keySettings.size();i++) {
      if(toupper(key) == input::keySettings[i]) {
        input::buttons[i] = false;
      }
    }
    
  }
  void mouseMoved(int x, int y ) {
    input::mouseX = x;
    input::mouseY = y;
  }
  void mouseDragged(int x, int y, int button) {
    input::mouseX = x;
    input::mouseY = y;
    input::mouseButtons[button] = true;
    
  }
  void mousePressed(int x, int y, int button) {
    input::mouseX = x;
    input::mouseY = y;
    input::mouseButtons[button] = true;
    
  }
  void mouseReleased(int x, int y, int button) {
    input::mouseX = x;
    input::mouseY = y;
    input::mouseButtons[button] = false;
    
  }
}
