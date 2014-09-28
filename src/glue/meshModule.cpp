//
//  Mesh.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/22.
//
//

#include "meshModule.h"
#include <cassert>
#include "LuaUtils.h"

namespace mesh {

  vector<ofPtr<ofMesh> > meshes;

  int l_createMesh(lua_State *L) {
    vector<ofPoint>     verts;
    vector<ofIndexType> indices;
    vector<ofPoint>     normals;
    // vertices
    int vertNum = lua_objlen(L, 1);
    for(int i=0;i<vertNum;i+=3) {
      lua_rawgeti(L, 1, i+1);
      double x = luaL_checknumber(L, -1);
      lua_pop(L,1);
      lua_rawgeti(L, 1, i+2);
      double y = luaL_checknumber(L, -1);
      lua_pop(L,1);
      lua_rawgeti(L, 1, i+3);
      double z = luaL_checknumber(L, -1);
      lua_pop(L,1);
      verts.push_back(ofPoint(x,y,z));
    }
    // indices
    int indNum = lua_objlen(L, 2);
    for(int i=1;i<=indNum;i++) {
      lua_rawgeti(L, 2, i);
      indices.push_back(luaL_checklong(L, -1));
      lua_pop(L, 1);
    }
    // normals
    int normNum = lua_objlen(L, 3);
    for(int i=0;i<normNum;i+=3) {
      lua_rawgeti(L, 3, i+1);
      double x = luaL_checknumber(L, -1);
      lua_pop(L, 1);
      lua_rawgeti(L, 3, i+2);
      double y = luaL_checknumber(L, -1);
      lua_pop(L, 1);
      lua_rawgeti(L, 3, i+3);
      double z = luaL_checknumber(L, -1);
      lua_pop(L, 1);
      normals.push_back(ofPoint(x,y,z));
    }
    lua_pop(L, 1);
    
    ofMesh **a = (ofMesh **)lua_newuserdata(L, sizeof(ofMesh *));
    *a = createMesh(verts, indices, normals).get();
    luaL_getmetatable(L, "app.mesh");
    lua_setmetatable(L, -2);
    return 1;
  }

  int l_deleteMesh(lua_State *L) {
    deleteMesh(*(ofMesh **)lua_touserdata(L, 1));
    return 0;
  }

  int l_drawMesh(lua_State *L) {
    ofMesh *mesh = *(ofMesh **)lua_touserdata(L, 1);
    drawMesh(mesh, ofPoint(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)));
    ofPopMatrix();
  }
  
  static const struct luaL_Reg engineLib_mesh_m [] = {
    {"delete"         , l_deleteMesh},
    {"draw"           , l_drawMesh},
    {NULL, NULL}
  };
  
  static const struct luaL_Reg engineLib_mesh_f [] = {
    {"new"            , l_createMesh},
    {NULL, NULL}
  };
  
  void openlib(lua_State *L) {
    lua_settop(L, 0);
    luaL_newmetatable(L, "app.mesh");
    // set GC
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, l_deleteMesh);
    lua_settable(L, -3);
    // set method
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, engineLib_mesh_m);
    // set constructer
    luaL_register(L, "mesh", engineLib_mesh_f);
  }

  
  ofPtr<ofMesh> createMesh(vector<ofPoint> verts, vector<ofIndexType> indices, vector<ofPoint> normals) {
    meshes.push_back(ofPtr<ofMesh>(new ofMesh()));
    ofPtr<ofMesh> mesh = meshes[meshes.size()-1];
    mesh->addVertices(verts);
    mesh->addIndices(indices);
    mesh->addNormals(normals);
    mesh->setMode(OF_PRIMITIVE_TRIANGLES);
    return mesh;
  }
  
  void deleteMesh(ofMesh *mesh) {
    for(vector<ofPtr<ofMesh> >::iterator ite = meshes.begin(); ite != meshes.end(); ite ++) {
      if((*ite).get() == mesh) {
        meshes.erase(ite);
        return;
      }
    }
    return;
  }
  
  void drawMesh(ofMesh *mesh, ofPoint pos) {
    ofPushMatrix();
    ofTranslate(pos);
    mesh->draw();
    ofPopMatrix();
  }
  
}
