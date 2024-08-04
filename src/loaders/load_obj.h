#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <stdbool.h>
#include <string.h>

#include "../data/mesh.h"

#define MATERIAL_LIBRARY_NAME_TOKEN "mtllib"
#define OBJECT_NAME_TOKEN "o"
#define VERTEX_COORDINATES_TOKEN "v"
#define VERTEX_NORMAL_COORDINATES_TOKEN "vn"
#define VERTEX_TEXTURE_COORDINATES_TOKEN "vt"
#define FACE_INDICES_TOKEN "f"
#define COMMENT_TOKEN "#"

bool loadObj(const char *path, Mesh *mesh);

#endif /* LOAD_OBJ_H */
