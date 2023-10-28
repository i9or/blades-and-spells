#include <stdlib.h>
#include <string.h>

#include "mesh.h"

void initMesh(Mesh *m) {
  m->materialLib = NULL;
  m->name = NULL;
  initArray(m->vertices);
  initArray(m->normals);
  initArray(m->uvs);
  initArray(m->faces);
}

void setMeshMaterialLib(Mesh *m, const char *materialLib) {
  if(m->materialLib != NULL) {
    resetMeshName(m);
  }

  m->materialLib = malloc(strlen(materialLib));
  strncpy(m->materialLib, materialLib, strlen(materialLib));
}

void setMeshName(Mesh *m, const char * name) {
  if (m->name != NULL) {
    resetMeshName(m);
  }

  m->name = malloc(strlen(name));
  strncpy(m->name, name, strlen(name));
}

void addMeshVertex(Mesh *m, Vec3 v) {
  pushToArray(m->vertices, v);
}

void addMeshNormal(Mesh *m, Vec3 v) {
  pushToArray(m->normals, v);
}

void addMeshUv(Mesh *m, Tex2 t) {
  pushToArray(m->uvs, t);
}

void addMeshFace(Mesh *m, Face f) {
  pushToArray(m->faces, f);
}

void resetMeshName(Mesh *m) {
  free(m->name);
  m->name = NULL;
}

void resetMeshMaterialLib(Mesh *m) {
  free(m->materialLib);
  m->name = NULL;
}

void destroyMesh(Mesh *m) {
  resetMeshMaterialLib(m);
  resetMeshName(m);

  destroyArray(m->vertices);
  destroyArray(m->normals);
  destroyArray(m->uvs);
  destroyArray(m->faces);
}
