#include <stddef.h>
#include <stdlib.h>

#include "image.h"
#include "logger.h"

static void printImageHeaderLine(char *label, int value) {
  LOG_DEBUG("%-30s:%d", label, value);
}

void printImageHeader(ImageHeader header) {
  printImageHeaderLine("ID Length", header.idLength);
  printImageHeaderLine("Color Map Type", header.colorMapType);
  printImageHeaderLine("Image Type", header.imageType);
  printImageHeaderLine("Color Map First Entry Index", header.colorMapFirstEntryIndex);
  printImageHeaderLine("Color Map Length", header.colorMapLength);
  printImageHeaderLine("Color Map Entry Size", header.colorMapEntrySize);
  printImageHeaderLine("X Origin", header.xOrigin);
  printImageHeaderLine("Y Origin", header.yOrigin);
  printImageHeaderLine("Width", header.width);
  printImageHeaderLine("Height", header.height);
  printImageHeaderLine("Pixel depth", header.pixelDepth);
  printImageHeaderLine("Image Descriptor", header.imageDescriptor);

  if (((header.imageDescriptor >> 4) & 1) == 1) {
    LOG_DEBUG("Image is right-to-left");
  } else {
    LOG_DEBUG("Image is left-to-right");
  }

  if (((header.imageDescriptor >> 5) & 1) == 1) {
    LOG_DEBUG("Image is top-to-bottom");
  } else {
    LOG_DEBUG("Image is bottom-to-top");
  }
}

bool isImageFormatSupported(ImageHeader header) {
  if (header.imageType != 2) {
    LOG_DEBUG("Uncompressed true-color images are supported only");
    return false;
  }

  if (header.pixelDepth != 24 && header.pixelDepth != 32) {
    LOG_DEBUG("Pixel depth of 24 bits and 32 bits supported only");
    return false;
  }

  if (header.colorMapType != 0) {
    LOG_DEBUG("Images without color map are supported only");
    return false;
  }

  return true;
}

unsigned char *initImageData(size_t numberOfPixels) {
  unsigned char *result = malloc(numberOfPixels * sizeof(unsigned char) * 4);

  for (size_t i = 0; i < numberOfPixels * 4; i += 4) {
    result[i] = 0;
    result[i + 1] = 0;
    result[i + 2] = 0;
    result[i + 3] = 0;
  }

  return result;
}

void destroyImageData(unsigned char **data) {
  free(*data);
  *data = NULL;
}

void initImage(Image *image) {
  image->header.idLength = 0;
  image->header.colorMapType = 0;
  image->header.imageType = 0;
  image->header.colorMapFirstEntryIndex = 0;
  image->header.colorMapLength = 0;
  image->header.colorMapEntrySize = 0;
  image->header.xOrigin = 0;
  image->header.yOrigin = 0;
  image->header.width = 0;
  image->header.height = 0;
  image->header.pixelDepth = 0;
  image->header.imageDescriptor = 0;
  image->imageData = NULL;
}

void destroyImage(Image *image) {
  destroyImageData(&image->imageData);
  initImage(image);
}
