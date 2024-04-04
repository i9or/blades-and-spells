#include <GLUT/GLUT.h>

#include "triangle.h"

static float mTriangleAngle = 0.f;

void drawTriangle(void) {
  glPushMatrix();

  glRotatef(mTriangleAngle, 0.f, 1.f, 0.f);

  glBegin(GL_TRIANGLES);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-1.f, 0.f, 0.f);
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(1.f, 0.f, 0.f);
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(0.f, 2.f, 0.f);
  glEnd();

  mTriangleAngle += 1.f;

  if (mTriangleAngle >= 360) {
    mTriangleAngle = 0.f;
  }

  glPopMatrix();
}
