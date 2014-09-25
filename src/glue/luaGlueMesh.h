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

extern vector<ofPtr<ofMesh> > meshes;

extern void openlib(lua_State *L);

int l_createMesh(lua_State *L);
int l_deleteMesh(lua_State *L);
int l_drawMesh(lua_State *L);

}

#endif /* defined(__LuaGame001__Mesh__) */
