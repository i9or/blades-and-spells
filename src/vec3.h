#ifndef vec3_h
#define vec3_h

typedef struct Vec3 {
  float x, y, z;
} Vec3;

void normalize3(Vec3 *);

float dot3(const Vec3 *, const Vec3 *);

Vec3 cross3(const Vec3 *, const Vec3 *);

#endif /* vec3_h */
