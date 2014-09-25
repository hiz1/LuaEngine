//
//  Mesh.h
//  LuaGame001
//
//  Created by hiz on 2014/09/22.
//
//

#ifndef __LuaGame001__Mesh__
#define __LuaGame001__Mesh__

#include "ofMain.h"

class MeshNode : public ofNode {
public:
  MeshNode();
  
  ofMesh&    getMesh();
  void       addVertices(const vector< ofVec3f > &verts);
  void       addIndices(const vector< ofIndexType > &indices);
  void       addNormals(const vector< ofVec3f > &normals);
  void       addColors(const vector<ofFloatColor> &cols);
  
  bool       isWireframe();
  void       setWireframe(bool wireframe);
  
  virtual void customDraw();
  
private:
  ofPtr<ofMesh>  mesh;
  bool           wireframe;
};

#endif /* defined(__LuaGame001__Mesh__) */
