#ifndef vec3_h
#define vec3_h

typedef struct Vec3 {
  float x, y, z;
} Vec3;

void normalizeVec3(Vec3 *);

float dot(const Vec3 *, const Vec3 *);

Vec3 cross(const Vec3 *, const Vec3 *);

#endif /* vec3_h */
