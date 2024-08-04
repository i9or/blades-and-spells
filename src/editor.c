#include <stdio.h>
#include <stdlib.h>

#include <GLUT/GLUT.h>

#include "utils/logger.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

double gWindowWidth = (double)WINDOW_WIDTH;
double gWindowHeight = (double)WINDOW_HEIGHT;

void initEditor(void);
void cleanUp(void);
void displayHandler(void);
void reshapeHandler(int, int);
void keyDownHandler(unsigned char, int, int);
void keyUpHandler(unsigned char, int, int);
void mouseMotionHandler(int, int);
void mouseClickHandler(int, int, int, int);

int main(int argc, char **argv) {
  if (atexit(cleanUp) != 0) {
    LOG_DEBUG("Clean up function registration failed");
    return EXIT_FAILURE;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Editor");
  glutIgnoreKeyRepeat(1);

  initEditor();

  glutReshapeFunc(reshapeHandler);
  glutDisplayFunc(displayHandler);
  glutKeyboardFunc(keyDownHandler);
  glutKeyboardUpFunc(keyUpHandler);
  glutIdleFunc(displayHandler);
  glutMotionFunc(mouseMotionHandler);
  glutPassiveMotionFunc(mouseMotionHandler);
  glutMouseFunc(mouseClickHandler);

  glutMainLoop();

  return EXIT_FAILURE;
}

void cleanUp(void) {
  LOG_DEBUG("Cleaning up");
}

void initEditor(void) {
  LOG_DEBUG("Initialising editor");
  glClearColor(0.3f, 0.3f, 0.3f, 1.f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void displayHandler(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, gWindowWidth / gWindowHeight, 0.1, 1000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0.0, 0.0, -2.5,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);

  glBegin(GL_TRIANGLES);

  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-0.5f, -0.5f, 0.f);

  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(0.5f, -0.5f, 0.f);

  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(0.f, 0.5f, 0.f);

  glEnd();

  glutSwapBuffers();
}

void reshapeHandler(int w, int h) {
  LOG_DEBUG("Reshape: %d %d", w, h);
  if (w < 1) {
    w = 1;
  }

  if (h < 1) {
    h = 1;
  }

  gWindowWidth = (double)w;
  gWindowHeight = (double)h;

  glViewport(0, 0, w, h);
}

void keyDownHandler(unsigned char key, int x, int y) {
  LOG_DEBUG("Key down: %c %d %d %d", key, key, x, y);

  if (key == 27) {
    exit(EXIT_SUCCESS);
  }
}

void keyUpHandler(unsigned char key, int x, int y) {
  LOG_DEBUG("Key up: %c %d %d %d", key, key, x, y);
}

void mouseMotionHandler(int x, int y) {
  LOG_DEBUG("Mouse motion: %d %d", x, y);
}

void mouseClickHandler(int button, int state, int x, int y) {
  LOG_DEBUG("Mouse click: %d %d %d %d", button, state, x, y);
}
