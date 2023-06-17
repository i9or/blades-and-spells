#ifndef camera_h
#define camera_h

#include "vec3.h"

void cameraInit(void);

void cameraRotateYaw(const float);

void cameraRotatePitch(const float);

void cameraMove(float);

void cameraUpdateDirection(void);

Vec3 cameraGetPosition(void);

Vec3 cameraGetDirection(void);

Vec3 cameraGetUp(void);

#endif /* camera_h */
