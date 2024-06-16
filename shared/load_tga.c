#include <stdio.h>

#include "load_tga.h"
#include "logger.h"

bool loadTga(const char *path, Image *image) {
  initImage(image);

  FILE *pFile = fopen(path, "r");
  if (!pFile) {
    LOG_DEBUG("Error loading Targa image: %s", path);
    return false;
  }

  image->header.idLength = (char)fgetc(pFile);
  image->header.colorMapType = (char)fgetc(pFile);
  image->header.imageType = (char)fgetc(pFile);
  fread(&(image->header.colorMapFirstEntryIndex), 2, 1, pFile);
  fread(&(image->header.colorMapLength), 2, 1, pFile);
  image->header.colorMapEntrySize = (char)fgetc(pFile);
  fread(&(image->header.xOrigin), 2, 1, pFile);
  fread(&(image->header.yOrigin), 2, 1, pFile);
  fread(&(image->header.width), 2, 1, pFile);
  fread(&(image->header.height), 2, 1, pFile);
  image->header.pixelDepth = (char)fgetc(pFile);
  image->header.imageDescriptor = (char)fgetc(pFile);

  if (isImageFormatSupported(image->header)) {
    size_t numberOfPixels = image->header.width * image->header.height;
    image->imageData = initImageData(numberOfPixels);

    size_t bytesToRead = image->header.pixelDepth / 8;
    unsigned char rawPixel[4];

    for (size_t i = 0; i < numberOfPixels * 4; i += 4) {
      if (fread(rawPixel, 1, bytesToRead, pFile) != bytesToRead) {
        LOG_DEBUG("Unexpected end of file");
        destroyImageData(&image->imageData);
        fclose(pFile);
        return false;
      }

      image->imageData[i] = rawPixel[2];
      image->imageData[i + 1] = rawPixel[1];
      image->imageData[i + 2] = rawPixel[0];

      if (bytesToRead == 4) {
        image->imageData[i + 3] = rawPixel[3];
      } else {
        image->imageData[i + 3] = 255;
      }
    }
  }

  LOG_DEBUG("Targa image %s is loaded successfully", path);
  printImageHeader(image->header);
  fclose(pFile);

  return true;
}
