#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "logger.h"
#include "mesh.h"
#include "utilities.h"

#include "load_obj.h"

static int parseIndex(const char *str) {
  return ((int)strtol(str, NULL, 10) - 1);
}

bool loadObj(const char *path, Mesh *mesh) {
  initMesh(mesh);

  FILE *file = fopen(path, "r");
  if (!file) {
    LOG_DEBUG("Error loading file: %s", path);
    return false;
  }

  char line[MAX_LINE_WIDTH];
  int lineCounter = 0;
  while (fgets(line, MAX_LINE_WIDTH, file) != NULL) {
    char *token;

    token = strtok(line, SPACE_DELIMITER);

    if (strcmp(token, MATERIAL_LIBRARY_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      setMeshMaterialLib(mesh, token);
    } else if (strcmp(token, OBJECT_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      setMeshName(mesh, token);
    } else if (strcmp(token, VERTEX_COORDINATES_TOKEN) == 0) {
      char *xStr, *yStr, *zStr;

      xStr = strtok(NULL, SPACE_DELIMITER);
      yStr = strtok(NULL, SPACE_DELIMITER);
      zStr = strtok(NULL, SPACE_DELIMITER);

      Vec3 v;
      v.x = strtof(xStr, NULL);
      v.y = strtof(yStr, NULL);
      v.z = strtof(zStr, NULL);

      addMeshVertex(mesh, v);
    } else if (strcmp(token, VERTEX_NORMAL_COORDINATES_TOKEN) == 0) {
      char *xStr, *yStr, *zStr;

      xStr = strtok(NULL, SPACE_DELIMITER);
      yStr = strtok(NULL, SPACE_DELIMITER);
      zStr = strtok(NULL, SPACE_DELIMITER);

      Vec3 n;
      n.x = strtof(xStr, NULL);
      n.y = strtof(yStr, NULL);
      n.z = strtof(zStr, NULL);

      addMeshNormal(mesh, n);
    } else if (strcmp(token, VERTEX_TEXTURE_COORDINATES_TOKEN) == 0) {
      char *uStr, *vStr;

      uStr = strtok(NULL, SPACE_DELIMITER);
      vStr = strtok(NULL, SPACE_DELIMITER);

      Tex2 t;
      t.u = strtof(uStr, NULL);
      t.v = strtof(vStr, NULL);

      addMeshUv(mesh, t);
    } else if (strcmp(token, FACE_INDICES_TOKEN) == 0) {
      /* TODO: this branch should be DRYed */
      char firstFaceStr[64], secondFaceStr[64], thirdFaceStr[64];

      strcpy(firstFaceStr, strtok(NULL, SPACE_DELIMITER));
      strcpy(secondFaceStr, strtok(NULL, SPACE_DELIMITER));
      strcpy(thirdFaceStr, strtok(NULL, SPACE_DELIMITER));

      Face f;
      char *a, *b, *c;

      a = strtok(firstFaceStr, FORWARD_SLASH_DELIMITER); /* v1 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* t1 or n1 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* n1 or NULL */

      if (!c) {
        f.v1 = parseIndex(a);
        f.t1 = INDEX_UNDEFINED;
        f.n1 = parseIndex(b);
      } else {
        f.v1 = parseIndex(a);
        f.t1 = parseIndex(b);
        f.n1 = parseIndex(c);
      }

      a = strtok(secondFaceStr, FORWARD_SLASH_DELIMITER); /* v2 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* t2 or n2 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);          /* n2 or NULL */

      if (!c) {
        f.v2 = parseIndex(a);
        f.t2 = INDEX_UNDEFINED;
        f.n2 = parseIndex(b);
      } else {
        f.v2 = parseIndex(a);
        f.t2 = parseIndex(b);
        f.n2 = parseIndex(c);
      }

      a = strtok(thirdFaceStr, FORWARD_SLASH_DELIMITER); /* v3 */
      b = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* t3 or n3 */
      c = strtok(NULL, FORWARD_SLASH_DELIMITER);         /* n3 or NULL */

      if (!c) {
        f.v3 = parseIndex(a);
        f.t3 = INDEX_UNDEFINED;
        f.n3 = parseIndex(b);
      } else {
        f.v3 = parseIndex(a);
        f.t3 = parseIndex(b);
        f.n3 = parseIndex(c);
      }

      addMeshFace(mesh, f);
    } else if ((strcmp(token, COMMENT_TOKEN) == 0)) {
      LOG_DEBUG("Skipping comment");
    } else {
      LOG_DEBUG("Token \"%s\" is not supported", token);
    }

    lineCounter++;
  }

  if (!feof(file)) {
    LOG_DEBUG("Error loading a file");
    fclose(file);
    destroyMesh(mesh);

    return false;
  } else {
    LOG_DEBUG("OBJ file %s loaded successfully", path);
    LOG_DEBUG("Total number of lines are read: %d", lineCounter);
  }

  fclose(file);
  return true;
}
