//
//  camera.c
//  blades-and-spells
//
//  Created by Igor on 03/06/2023.
//

#include <math.h>

#include "camera.h"
#include "vec3.h"

static const float MOVE_SPEED = 0.1f;
static const float ROTATION_SPEED = M_PI / 180.f * 0.2f;
static const float ROTATION_LIMIT = 89.f * M_PI / 180.f;

static Vec3 mPosition;
static Vec3 mDirection;
static float mYaw;
static float mPitch;

void cameraInit(void) {
  mYaw = M_PI / 2.f;
  mPitch = 0.f;
  mPosition = (Vec3) { .x = 0.f, .y = 1.8f, .z = -5.f };
  cameraUpdateDirection();
}

void cameraRotateYaw(const int dx) {
  mYaw += ROTATION_SPEED * (float)dx;

  cameraUpdateDirection();
}

void cameraRotatePitch(const int dy) {
  mPitch += ROTATION_SPEED * (float)dy;

  if (mPitch < -ROTATION_LIMIT) {
    mPitch = -ROTATION_LIMIT;
  }

  if (mPitch > ROTATION_LIMIT) {
    mPitch = ROTATION_LIMIT;
  }

  cameraUpdateDirection();
}

void cameraMove(float amount) {
  mPosition.x += amount * mDirection.x * MOVE_SPEED;
  mPosition.y += amount * mDirection.y * MOVE_SPEED;
  mPosition.z += amount * mDirection.z * MOVE_SPEED;
}

void cameraStrafe(float amount) {
  mPosition.x += amount * MOVE_SPEED * cosf(mYaw - M_PI_2);
  mPosition.z += amount * MOVE_SPEED * sinf(mYaw - M_PI_2);
}

void cameraUpdateDirection(void) {
  mDirection.x = cosf(mYaw) * cos(mPitch);
  mDirection.y = sinf(mPitch);
  mDirection.z = sinf(mYaw) * cos(mPitch);
}

Vec3 cameraGetPosition(void) {
  return mPosition;
}

Vec3 cameraGetDirection(void) {
  return mDirection;
}
