#ifndef LOAD_MTL_H
#define LOAD_MTL_H

#include <stdbool.h>

#include "../data/material.h"

#define MATERIAL_NAME_TOKEN "newmtl"
#define DIFFUSE_COLOR_TOKEN "Kd"
#define DIFFUSE_MAP_TOKEN "map_Kd"
#define COMMENT_TOKEN "#"

bool loadMtl(const char *path, Material *material);

#endif /* LOAD_MTL_H */
