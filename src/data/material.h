#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

typedef struct {
  char *name;
  char *diffuseMapPath;
  Vec3 diffuseColor;
} Material;

void initMaterial(Material *material);

void resetMaterialName(Material *material);

void resetMaterialDiffuseMapPath(Material *material);

void setMaterialName(Material *material, const char *name);

void setMaterialDiffuseMapPath(Material *material, const char *diffuseMapPath);

void setMaterialDiffuseColor(Material *material, Vec3 color);

void destroyMaterial(Material *material);

#endif /* MATERIAL_H */
