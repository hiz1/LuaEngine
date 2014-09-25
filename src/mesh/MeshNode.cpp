//
//  Mesh.cpp
//  LuaGame001
//
//  Created by hiz on 2014/09/22.
//
//

#include "MeshNode.h"


MeshNode::MeshNode():ofNode() {
}

void MeshNode::customDraw() {
  if(this->wireframe) {
    this->mesh->drawWireframe();
  } else {
    this->mesh->draw();
  }
}

ofMesh& MeshNode::getMesh() {
  return *this->mesh;
}

void MeshNode::addVertices(const vector< ofVec3f > &verts) {
  mesh->addVertices(verts);
}
void MeshNode::addIndices(const vector< ofIndexType > &indices) {
  mesh->addIndices(indices);
}
void MeshNode::addNormals(const vector< ofVec3f > &normals) {
  mesh->addNormals(normals);
}
void MeshNode::addColors(const vector<ofFloatColor> &cols) {
  mesh->addColors(cols);
}


bool MeshNode::isWireframe() {
  return wireframe;
}

void MeshNode::setWireframe(bool wireframe) {
  this->wireframe = wireframe;
}