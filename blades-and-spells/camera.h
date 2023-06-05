#ifndef camera_h
#define camera_h

#include "vec3.h"

void cameraInit(void);

void cameraRotateYaw(const int);

void cameraRotatePitch(const int);

void cameraMove(float);

void cameraStrafe(float);

void cameraUpdateDirection(void);

Vec3 cameraGetPosition(void);

Vec3 cameraGetDirection(void);

#endif /* camera_h */
