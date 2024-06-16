#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  char idLength;
  char colorMapType;
  char imageType;
  short colorMapFirstEntryIndex;
  short colorMapLength;
  char colorMapEntrySize;
  short xOrigin;
  short yOrigin;
  short width;
  short height;
  char pixelDepth;
  char imageDescriptor;
} ImageHeader;

typedef struct {
  ImageHeader header;
  unsigned char *imageData;
} Image;

void printImageHeader(ImageHeader header);
bool isImageFormatSupported(ImageHeader header);
unsigned char *initImageData(size_t numberOfPixels);
void destroyImageData(unsigned char **data);
void initImage(Image *image);
void destroyImage(Image *image);

#endif /* IMAGE_H */
