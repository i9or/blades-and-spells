#ifndef VEC3_H
#define VEC3_H

typedef struct {
  float x, y, z;
} Vec3;

float length3(const Vec3 *v);

void normalize3(Vec3 *v);

float dot3(const Vec3 *a, const Vec3 *b);

Vec3 cross3(const Vec3 *a, const Vec3 *b);

Vec3 add3(const Vec3 *a, const Vec3 *b);

Vec3 sub3(const Vec3 *a, const Vec3 *b);

#endif /* VEC3_H */
