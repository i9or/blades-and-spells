#include <math.h>

#include "vec2.h"

void normalize2(Vec2 *v) {
  float length = sqrtf(v->x * v->x + v->y * v->y);

  v->x /= length;
  v->y /= length;
}

float dot2(const Vec2 *v1, const Vec2 *v2) {
  return v1->x * v1->x + v1->y * v1->y;
}
