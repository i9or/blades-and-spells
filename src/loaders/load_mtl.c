#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data/vec3.h"
#include "../utils/constants.h"
#include "../utils/logger.h"
#include "../utils/utilities.h"

#include "load_mtl.h"

bool loadMtl(const char *path, Material *material) {
  initMaterial(material);

  FILE *pFile = fopen(path, "r");
  if (!pFile) {
    LOG_DEBUG("Error loading material library: %s", path);
    return false;
  }

  char line[MAX_LINE_WIDTH];
  int lineCounter = 0;
  while (fgets(line, MAX_LINE_WIDTH, pFile) != NULL) {
    char *token;

    token = strtok(line, SPACE_DELIMITER);

    if (strcmp(token, MATERIAL_NAME_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      setMaterialName(material, token);
    } else if (strcmp(token, DIFFUSE_MAP_TOKEN) == 0) {
      token = strtok(NULL, SPACE_DELIMITER);
      STRIP_NEWLINE(token);
      setMaterialDiffuseMapPath(material, token);
    } else if (strcmp(token, DIFFUSE_COLOR_TOKEN) == 0) {
      char *r, *g, *b;

      r = strtok(NULL, SPACE_DELIMITER);
      g = strtok(NULL, SPACE_DELIMITER);
      b = strtok(NULL, SPACE_DELIMITER);

      Vec3 color;
      color.x = strtof(r, NULL);
      color.y = strtof(g, NULL);
      color.z = strtof(b, NULL);

      setMaterialDiffuseColor(material, color);
    } else if ((strcmp(token, COMMENT_TOKEN) == 0)) {
      LOG_DEBUG("Skipping comment");
    } else {
      LOG_DEBUG("Token \"%s\" is not supported", token);
    }

    lineCounter++;
  }

  if (!feof(pFile)) {
    LOG_DEBUG("Error loading a file %s", path);
    fclose(pFile);
    destroyMaterial(material);

    return false;
  } else {
    LOG_DEBUG("MTL file %s is loaded successfully", path);
    LOG_DEBUG("Total number of lines are read: %d", lineCounter);
  }

  fclose(pFile);
  return true;
}
