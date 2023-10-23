#include <math.h>

#include "vec3.h"

void normalize3(Vec3 *v) {
  float length = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);

  v->x /= length;
  v->y /= length;
  v->z /= length;
}

float dot3(const Vec3 *v1, const Vec3 *v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

Vec3 cross3(const Vec3 *v1, const Vec3 *v2) {
  return ((Vec3) {
      .x = v1->y * v2->z - v1->z * v2->y,
      .y = v1->z * v2->x - v1->x * v2->z,
      .z = v1->x * v2->y - v1->y * v2->x });
}
