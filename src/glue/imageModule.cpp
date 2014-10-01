//
//  luaGlueImage.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/25.
//
//

#include "imageModule.h"
#include "LuaUtils.h"

namespace image {

  // image
  vector<ofPtr<TexturePlane> > images;

  int l_createImage(lua_State *L) {
    TexturePlane **a = (TexturePlane **)lua_newuserdata(L, sizeof(TexturePlane *));
    *a = createImage(luaL_checkstring(L, 1)).get();
    luaL_getmetatable(L, "app.image");
    lua_setmetatable(L, -2);
    return 1;
  }

  int l_setImage(lua_State *L) {
    setImage(*(TexturePlane **)lua_touserdata(L, 1), luaL_checkstring(L, 2));
    return 0;
  }
  
  int l_setSubsection(lua_State *L) {
    setSubsection(*(TexturePlane **)lua_touserdata(L, 1),
                  luaL_checknumber(L, 2),
                  luaL_checknumber(L, 3),
                  luaL_checknumber(L, 4),
                  luaL_checknumber(L, 5));
    return 0;
  }
  
  int l_getSubsection(lua_State *L) {
    ofVec4f rect = getSubsection(*(TexturePlane **)lua_touserdata(L, 1));
    lua_pushnumber(L, rect.x);
    lua_pushnumber(L, rect.y);
    lua_pushnumber(L, rect.z);
    lua_pushnumber(L, rect.w);
    return 4;
  }
  
  int l_getImageSize(lua_State *L) {
    ofVec2f size = getImageSize(*(TexturePlane **)lua_touserdata(L, 1));
    lua_pushnumber(L, size.x);
    lua_pushnumber(L, size.y);
    return 2;
  }
  
  int l_deleteImage(lua_State *L) {
    deleteImage(*(TexturePlane **)lua_touserdata(L, 1));

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
  
  static const struct luaL_Reg engineLib_image_f [] = {
    {"new"        , l_createImage  },
    {NULL, NULL}
  };
  
  static const struct luaL_Reg engineLib_image_m [] = {
    {"delete"     , l_deleteImage},
    {"setImage"   , l_setImage   },
    {"setSubsection", l_setSubsection},
    {"getSubsection", l_getSubsection},
    {"getImageSize", l_getImageSize},
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
  
  void openlib(lua_State *L) {
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
  
  ofPtr<TexturePlane> createImage(const string &imageFile) {
    images.push_back(ofPtr<TexturePlane>(new TexturePlane()));
    images[images.size()-1]->setImage(ofToDataPath(imageFile));
    images[images.size()-1]->resizeToCurrentTexture();
    return images[images.size()-1];
  }
  
  void setImage(TexturePlane *image, const string &imageFile) {
    image->setImage(ofToDataPath(imageFile));
    image->resizeToCurrentTexture();
  }
  
  void setSubsection(TexturePlane *image, float u1, float v1, float u2, float v2) {
    image->mapTexCoords(u1, v1, u2, v2);
    image->set((u2-u1) * image->getScale().x, (v2-v1) * image->getScale().y);
  }
  
  ofVec4f &getSubsection(TexturePlane *image) {
    return image->getTexCoords();
  }
  
  ofVec2f getImageSize(TexturePlane *image) {
    return ofVec2f(image->getTexture().getWidth(), image->getTexture().getHeight());
  }
  
  void deleteImage(TexturePlane *image) {
    for(vector<ofPtr<TexturePlane> >::iterator ite = images.begin(); ite != images.end(); ite ++) {
      if((*ite).get() == image) {
        images.erase(ite);
        return;
      }
    }
  }
  
  map<string, ofImage> imageCache;
  
  void TexturePlane::initialize() {
    set( 200, 100, 6, 3);
  }
  
  void TexturePlane::setImage(const string &imagePath) {
    if(imageCache.count(imagePath) == 0) {
      imageCache[imagePath] = ofImage();
      imageCache[imagePath].loadImage(imagePath);
    }
    this->texture = &imageCache[imagePath].getTextureReference();
    this->setResolution(2, 2);
  }
  
  void TexturePlane::resizeToCurrentTexture() {
    resizeToTexture(*texture);
  }
  
  void TexturePlane::draw() {
    if(texture != NULL) texture->bind();
    ofPlanePrimitive::draw();
    if(texture != NULL) texture->unbind();
  }
  
  ofTexture &TexturePlane::getTexture() {
    return *texture;
  }
  
}

