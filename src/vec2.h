#ifndef vec2_h
#define vec2_h

typedef struct Vec2 {
  float x, y;
} Vec2;

void normalize2(Vec2 *);

float dot2(const Vec2 *, const Vec2 *);

#endif /* vec2_h */
