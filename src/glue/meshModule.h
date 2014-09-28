//
//  Mesh.h
//  LuaGame001
//
//  Created by hiz on 2014/09/22.
//
//

#ifndef __LuaGame001__Mesh__
#define __LuaGame001__Mesh__

#include <stdio.h>
#include "ofMain.h"
#include "../mesh/MeshNode.h"
#include "../lua/lua.hpp"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"

namespace mesh {

  void openlib(lua_State *L);

  #pragma mark - lua
  ofPtr<ofMesh> createMesh(vector<ofPoint> verts, vector<ofIndexType> indices, vector<ofPoint> normals);
  void deleteMesh(ofMesh *mesh);
  void drawMesh(ofMesh *mesh, ofPoint pos);
  
}

#endif /* defined(__LuaGame001__Mesh__) */
