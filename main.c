#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <stdlib.h>

#include <GLUT/glut.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

void displayHandler(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POLYGON);

  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(0.25f, 0.25f, 0.f);
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(0.75f, 0.25f, 0.f);
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(0.5f, 0.75f, 0.f);

  glEnd();

  glutSwapBuffers();
}

void reshapeHandler(int w, int h) {
  if (h < 1) {
    h = 1;
  }

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 1.0, 0.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutPostRedisplay();
}

void initGame(void) {
  glClearColor(0.1f, 0.2f, 0.3f, 1.f);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Blades and Spells");

  initGame();

  glutReshapeFunc(reshapeHandler);
  glutDisplayFunc(displayHandler);
  glutMainLoop();

  return EXIT_SUCCESS;
}
