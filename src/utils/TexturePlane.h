//
//  Plane.h
//  study_texture
//
//  Created by 成田 輝久 on 2013/11/24.
//
//

#ifndef __study_texture__Plane__
#define __study_texture__Plane__

#include "ofMain.h"

// テクスチャを表示するPlane
class TexturePlane : public ofPlanePrimitive {
public:
  void initialize();
    void setImage(const string &imagePath);
    void draw();
private:
    ofTexture *texture;
};

#endif /* defined(__study_texture__Plane__) */
