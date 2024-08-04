#include <stdlib.h>
#include <string.h>

#include "../utils/logger.h"

#include "material.h"

void initMaterial(Material *material) {
  material->name = NULL;
  material->diffuseMapPath = NULL;
  material->diffuseColor.x = 0.f;
  material->diffuseColor.y = 0.f;
  material->diffuseColor.z = 0.f;
}

void resetMaterialName(Material *material) {
  free(material->name);
  material->name = NULL;
}

void resetMaterialDiffuseMapPath(Material *material) {
  free(material->diffuseMapPath);
  material->diffuseMapPath = NULL;
}

void setMaterialName(Material *material, const char *name) {
  if (material->name != NULL) {
    resetMaterialName(material);
  }

  material->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(material->name, name);
}

void setMaterialDiffuseMapPath(Material *material, const char *diffuseMapPath) {
  if (material->diffuseMapPath != NULL) {
    resetMaterialDiffuseMapPath(material);
  }

  material->diffuseMapPath = malloc(sizeof(char) * (strlen(diffuseMapPath) + 1));
  strcpy(material->diffuseMapPath, diffuseMapPath);
}

void destroyMaterial(Material *material) {
  resetMaterialName(material);
  resetMaterialDiffuseMapPath(material);
}

void setMaterialDiffuseColor(Material *material, Vec3 color) {
  material->diffuseColor = color;
}
