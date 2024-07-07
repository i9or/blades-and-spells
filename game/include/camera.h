#ifndef camera_h
#define camera_h

#include "vec3.h"

void cameraInit(void);
void cameraRotateYaw(float dx);
void cameraRotatePitch(float dy);
void cameraMove(float amount);
void cameraFly(float amount);
void cameraUpdateDirection(void);
Vec3 cameraGetPosition(void);
Vec3 cameraGetDirection(void);
Vec3 cameraGetUp(void);
void cameraSetHeight(float height);

#endif /* camera_h */
