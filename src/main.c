#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ApplicationServices/ApplicationServices.h>

#include <GLUT/glut.h>

#include "camera.h"
#include "keyboard.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float gTriangleAngle = 0.f;
bool gFpsMode = false;

void initGame(void);
void displayHandler(void);
void reshapeHandler(int, int);
void keyDownHandler(unsigned char, int, int);
void keyUpHandler(unsigned char, int, int);
void mouseMotionHandler(int, int);
void processKeyboard(void);
void processCamera(void);

void drawGrid(void);
void drawTriangle(void);

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Blades and Spells");
  glutIgnoreKeyRepeat(1);

  initGame();
  glutReshapeFunc(reshapeHandler);
  glutDisplayFunc(displayHandler);
  glutKeyboardFunc(keyDownHandler);
  glutKeyboardUpFunc(keyUpHandler);
  glutIdleFunc(displayHandler);
  glutMotionFunc(mouseMotionHandler);
  glutPassiveMotionFunc(mouseMotionHandler);

  glutMainLoop();

  return EXIT_FAILURE; /* Something went terribly wrong if we are here */
}

void initGame(void) {
  glClearColor(0.1f, 0.2f, 0.3f, 1.f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  cameraInit();
}

void displayHandler(void) {
  int t1 = glutGet(GLUT_ELAPSED_TIME);
  processKeyboard();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  processCamera();

  drawGrid();
  drawTriangle();

  glutSwapBuffers();

  int t2 = glutGet(GLUT_ELAPSED_TIME);

  char title[64];
  sprintf(title, "Draw time: %d", t2 - t1);
  glutSetWindowTitle(title);
}

void reshapeHandler(int w, int h) {
  if (h < 1) {
    h = 1;
  }

  double ratio = (double)w / (double)h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, ratio, 0.1, 1000.0);
}

void keyDownHandler(unsigned char key, int x, int y) {
  printf("Key pressed: %c - %d\n", key, key);

  if (key == ESCAPE_KEY) {
    exit(EXIT_SUCCESS);
  }

  pressKey(key);

  glutPostRedisplay();
}

void keyUpHandler(unsigned char key, int x, int y) {
  resetKey(key);

  glutPostRedisplay();
}

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

void drawTriangle(void) {
  glPushMatrix();

  glRotatef(gTriangleAngle, 0.f, 1.f, 0.f);

  glBegin(GL_TRIANGLES);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(-1.f, 0.f, 0.f);
  glColor3f(0.f, 1.f, 0.f);
  glVertex3f(1.f, 0.f, 0.f);
  glColor3f(0.f, 0.f, 1.f);
  glVertex3f(0.f, 2.f, 0.f);
  glEnd();

  gTriangleAngle += 1.f;

  if (gTriangleAngle >= 360) {
    gTriangleAngle = 0.f;
  }

  glPopMatrix();
}

void mouseMotionHandler(int x, int y) {
  // Add mouse handling here
  glutPostRedisplay();
}

void processKeyboard(void) {
  if (isKeyPressed(F_KEY)) {
    resetKey(F_KEY);
    gFpsMode = !gFpsMode;

    if (gFpsMode) {
      CGDisplayHideCursor(CGMainDisplayID());
    } else {
      CGDisplayShowCursor(CGMainDisplayID());
    }
  }

  if (isKeyPressed(W_KEY)) {
    cameraMove(1.f);
  }

  if (isKeyPressed(A_KEY)) {
    cameraRotateYaw(-1.f);
  }

  if (isKeyPressed(S_KEY)) {
    cameraMove(-1.f);
  }

  if (isKeyPressed(D_KEY)) {
    cameraRotateYaw(1.f);
  }

  if (isKeyPressed(T_KEY)) {
    cameraRotatePitch(1.f);
  }

  if (isKeyPressed(G_KEY)) {
    cameraRotatePitch(-1.f);
  }
}

void processCamera(void) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  Vec3 pos = cameraGetPosition();
  Vec3 dir = cameraGetDirection();
  Vec3 up = cameraGetUp();
  gluLookAt(pos.x, pos.y, pos.z,
            pos.x + dir.x, pos.y + dir.y, pos.z + dir.z,
            up.x, up.y, up.z);
}
