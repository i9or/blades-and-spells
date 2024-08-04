#include <stdlib.h>
#include <string.h>

#include "mesh.h"

void initMesh(Mesh *mesh) {
  mesh->materialLib = NULL;
  mesh->name = NULL;
  initArray(mesh->vertices);
  initArray(mesh->normals);
  initArray(mesh->uvs);
  initArray(mesh->faces);
}

void setMeshMaterialLib(Mesh *mesh, const char *path) {
  if (mesh->materialLib != NULL) {
    resetMeshName(mesh);
  }

  mesh->materialLib = malloc(strlen(path));
  strncpy(mesh->materialLib, path, strlen(path) + 1);
}

void setMeshName(Mesh *mesh, const char *name) {
  if (mesh->name != NULL) {
    resetMeshName(mesh);
  }

  mesh->name = malloc(strlen(name) + 1);
  strncpy(mesh->name, name, strlen(name) + 1);
}

void addMeshVertex(Mesh *mesh, Vec3 vertex) {
  pushToArray(mesh->vertices, vertex);
}

void addMeshNormal(Mesh *mesh, Vec3 normal) {
  pushToArray(mesh->normals, normal);
}

void addMeshUv(Mesh *mesh, Tex2 uv) {
  pushToArray(mesh->uvs, uv);
}

void addMeshFace(Mesh *mesh, Face face) {
  pushToArray(mesh->faces, face);
}

void resetMeshName(Mesh *mesh) {
  free(mesh->name);
  mesh->name = NULL;
}

void resetMeshMaterialLib(Mesh *mesh) {
  free(mesh->materialLib);
  mesh->name = NULL;
}

void destroyMesh(Mesh *mesh) {
  resetMeshMaterialLib(mesh);
  resetMeshName(mesh);

  destroyArray(mesh->vertices);
  destroyArray(mesh->normals);
  destroyArray(mesh->uvs);
  destroyArray(mesh->faces);
}
