#include <math.h>

#include "vec3.h"

float length3(const Vec3 *v) {
  return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

void normalize3(Vec3 *v) {
  float length = length3(v);

  v->x /= length;
  v->y /= length;
  v->z /= length;
}

float dot3(const Vec3 *a, const Vec3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

Vec3 cross3(const Vec3 *a, const Vec3 *b) {
  return ((Vec3) {
      .x = a->y * b->z - a->z * b->y,
      .y = a->z * b->x - a->x * b->z,
      .z = a->x * b->y - a->y * b->x });
}
