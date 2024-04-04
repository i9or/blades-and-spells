#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <stdbool.h>
#include <string.h>

#include "mesh.h"

#define MAX_FILE_PATH_LENGTH 512
#define MAX_LINE_WIDTH 1024
#define SPACE_DELIMITER " "
#define FORWARD_SLASH_DELIMITER "/"
#define INDEX_UNDEFINED (-1)

#define MATERIAL_LIBRARY_NAME_TOKEN "mtllib"
#define OBJECT_NAME_TOKEN "o"
#define VERTEX_COORDINATES_TOKEN "v"
#define VERTEX_NORMAL_COORDINATES_TOKEN "vn"
#define VERTEX_TEXTURE_COORDINATES_TOKEN "vt"
#define FACE_INDICES_TOKEN "f"
#define COMMENT_TOKEN "#"

#define stripNewline(str) (str)[strcspn((str), "\r\n")] = '\0'

bool loadObj(const char *path, Mesh *mesh);

#endif /* LOAD_OBJ_H */
