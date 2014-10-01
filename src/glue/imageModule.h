//
//  luaGlueImage.h
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#ifndef __LuaGame001__luaGlueImage__
#define __LuaGame001__luaGlueImage__

#include <stdio.h>
#include "ofMain.h"
#include "../lua/lua.hpp"
#include "../lua/lualib.h"
#include "../lua/lauxlib.h"

namespace image {
  // テクスチャを表示するPlane
  class TexturePlane : public ofPlanePrimitive {
  public:
    void initialize();
    void setImage(const string &imageFile);
    void resizeToCurrentTexture();
    ofTexture &getTexture();
    void draw();
  private:
    ofTexture *texture;
  };
  
  void openlib(lua_State *L);
  
  ofPtr<TexturePlane> createImage(const string &imageFile);
  void setImage(TexturePlane *image, const string &imageFile);
  void deleteImage(TexturePlane *mesh);
  void setSubsection(TexturePlane *image, float u1, float v1, float u2, float v2);
  ofVec4f &getSubsection(TexturePlane *image);
  ofVec2f getImageSize(TexturePlane *image);
}

#endif /* defined(__LuaGame001__luaGlueImage__) */
