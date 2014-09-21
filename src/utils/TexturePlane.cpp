//
//  Plane.cpp
//  study_texture
//
//  Created by 成田 輝久 on 2013/11/24.
//
//

#include "TexturePlane.h"

map<string, ofImage> imageCache;

void TexturePlane::initialize() {
  texCoords = ofVec4f(0,0,1,1);
  set( 200, 100, 6, 3);
}

void TexturePlane::setImage(const string &imagePath) {
  if(imageCache.count(imagePath) == 0) {
    imageCache[imagePath] = ofImage();
    imageCache[imagePath].loadImage(imagePath);
  }
  this->texture = &imageCache[imagePath].getTextureReference();
  this->setResolution(2, 2);
  resizeToTexture(*texture);
}

void TexturePlane::draw() {
    if(texture != NULL) texture->bind();
    ofPlanePrimitive::draw();
    if(texture != NULL) texture->unbind();
}