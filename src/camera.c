#include <math.h>

#include "camera.h"
#include "vec3.h"

static const float MOVE_SPEED = 0.1f;
static const float ROTATION_SPEED = M_PI / 180.f * 2.f;
static const float ROTATION_LIMIT = 89.f * M_PI / 180.f;
static Vec3 WORLD_UP = { .x = 0.f, .y = 1.f, .z = 0.f };

static Vec3 mPosition;
static Vec3 mDirection;
static Vec3 mUp;
static float mYaw;
static float mPitch;

void cameraInit(void) {
  mYaw = M_PI / 2.f;
  mPitch = 0.f;
  mPosition = (Vec3) { .x = 0.f, .y = 1.8f, .z = -5.f };
  cameraUpdateDirection();
}

void cameraRotateYaw(const float dx) {
  mYaw += ROTATION_SPEED * (float)dx;

  cameraUpdateDirection();
}

void cameraRotatePitch(const float dy) {
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
  mPosition.x += amount * cosf(mYaw) * MOVE_SPEED;
  mPosition.z += amount * sinf(mYaw) * MOVE_SPEED;
}

void cameraUpdateDirection(void) {
  mDirection.x = cosf(mYaw) * cos(mPitch);
  mDirection.y = sinf(mPitch);
  mDirection.z = sinf(mYaw) * cos(mPitch);

  normalizeVec3(&mDirection);

  Vec3 right = cross(&mDirection, &WORLD_UP);
  normalizeVec3(&right);

  mUp = cross(&right, &mDirection);
  normalizeVec3(&mUp);
}

Vec3 cameraGetPosition(void) {
  return mPosition;
}

Vec3 cameraGetDirection(void) {
  return mDirection;
}

Vec3 cameraGetUp(void) {
  return mUp;
}
