#ifndef load_obj_h
#define load_obj_h

#include <stdbool.h>
#include <string.h>

#include "../mesh.h"

#define MATERIAL_LIBRARY_NAME_TOKEN "mtllib"
#define OBJECT_NAME_TOKEN "o"
#define VERTEX_COORDINATES_TOKEN "v"
#define VERTEX_NORMAL_COORDINATES_TOKEN "vn"
#define VERTEX_TEXTURE_COORDINATES_TOKEN "vt"
#define FACE_INDICES_TOKEN "f"

#define stripNewline(str) (str)[strcspn((str), "\r\n")] = '\0'

bool loadObj(const char *, Mesh *);

#endif
