#include <GLUT/GLUT.h>

#include "grid.h"

void drawGrid(void) {
  glPushMatrix();

  glColor3f(0.f, 1.f, 0.f);

  glBegin(GL_LINES);

  for (int i = -50; i < 50; i += 1) {
    glVertex3f((float)i, 0.f, -50.f);
    glVertex3f((float)i, 0.f, 50.f);

    glVertex3f(-50.f, 0.f, (float)i);
    glVertex3f(50.f, 0.f, (float)i);
  }

  glEnd();

  glPopMatrix();
}
