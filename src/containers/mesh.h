#ifndef mesh_h
#define mesh_h

#include "./vec3.h"
#include "./tex2.h"
#include "./face.h"
#include "../utils/dynamic_array.h"

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

void initMesh(Mesh *);

void setMeshMaterialLib(Mesh *, const char *);

void setMeshName(Mesh *, const char *);

void addMeshVertex(Mesh *, Vec3);

void addMeshNormal(Mesh *, Vec3);

void addMeshUv(Mesh *, Tex2);

void addMeshFace(Mesh *, Face);

void resetMeshName(Mesh *);

void resetMeshMaterialLib(Mesh *);

void destroyMesh(Mesh *);

#endif /* mesh_h */
