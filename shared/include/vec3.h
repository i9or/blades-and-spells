#ifndef VEC3_H
#define VEC3_H

typedef struct {
  float x, y, z;
} Vec3;

void normalize3(Vec3 *v);

float dot3(const Vec3 *a, const Vec3 *b);

Vec3 cross3(const Vec3 *a, const Vec3 *b);

#endif /* VEC3_H */
