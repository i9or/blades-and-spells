#ifndef MESH_H
#define MESH_H

#include "dynamic_array.h"
#include "face.h"
#include "tex2.h"
#include "vec3.h"

typedef Array(Vec3) Vec3Array;
typedef Array(Tex2) Tex2Array;
typedef Array(Face) FaceArray;

typedef struct {
  char *materialLib;
  char *name;

  Vec3Array vertices;
  Vec3Array normals;
  Tex2Array uvs;

  FaceArray faces;
} Mesh;

void initMesh(Mesh *mesh);

void setMeshMaterialLib(Mesh *mesh, const char *path);

void setMeshName(Mesh *mesh, const char *name);

void addMeshVertex(Mesh *mesh, Vec3 vertex);

void addMeshNormal(Mesh *mesh, Vec3 normal);

void addMeshUv(Mesh *mesh, Tex2 uv);

void addMeshFace(Mesh *mesh, Face face);

void resetMeshName(Mesh *mesh);

void resetMeshMaterialLib(Mesh *mesh);

void destroyMesh(Mesh *mesh);

#endif /* MESH_H */
