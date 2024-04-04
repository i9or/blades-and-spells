#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>
#include <GLUT/glut.h>

#include "load_obj.h"
#include "logger.h"
#include "mesh.h"

#include "camera.h"
#include "grid.h"
#include "keyboard.h"
#include "triangle.h"

#define WINDOWED_MODE true /* change to "false" to run game in fullscreen */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static bool gFpsMode = false;
static char gDrawingTime[64] = "";

void initGame(void);
void cleanUp(void);
void displayHandler(void);
void reshapeHandler(int, int);
void keyDownHandler(unsigned char, int, int);
void keyUpHandler(unsigned char, int, int);
void mouseMotionHandler(int, int);
void processKeyboard(void);
void processCamera(void);

static Mesh gBunny;
bool loadBunny(void);
void drawBunny(void);
void setOrthographicProjection(void);
void restorePerspectiveProjection(void);
void renderBitmapString(float x, float y, void *font, char *string);

int main(int argc, char **argv) {
  if (atexit(cleanUp) != 0) {
    LOG_DEBUG("Clean up function registration failed...");
    return EXIT_FAILURE;
  }

  LOG_DEBUG("Creating a window");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  if (WINDOWED_MODE == true) {
      glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
      glutInitWindowPosition(100, 100);
      glutCreateWindow("Blades and Spells");
  } else {
    glutGameModeString("800x600:32");
    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
      glutEnterGameMode();
    else {
      LOG_DEBUG("The selected mode is not available");
      exit(1);
    }
  }

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
  LOG_DEBUG("Initializing a game");

  glClearColor(0.1f, 0.2f, 0.3f, 1.f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  cameraInit();

  loadBunny();
}

void cleanUp(void) {
  LOG_DEBUG("Cleaning up a game");

  destroyMesh(&gBunny);
}

void displayHandler(void) {
  int t1 = glutGet(GLUT_ELAPSED_TIME);
  processKeyboard();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  processCamera();

  /* Draw scene here */
  drawGrid();
  drawBunny();
  /* =============== */

  setOrthographicProjection();
  glPushMatrix();
  glLoadIdentity();
  glColor3f(0.f, 1.f, 1.f);
  renderBitmapString(5, 20, GLUT_BITMAP_HELVETICA_18, gDrawingTime);
  glPopMatrix();

  restorePerspectiveProjection();

  glutSwapBuffers();

  int t2 = glutGet(GLUT_ELAPSED_TIME);

  sprintf(gDrawingTime, "Draw time: %d", t2 - t1);
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
  LOG_DEBUG("Key pressed: %c - %d", key, key);

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

bool loadBunny(void) {
  if(!loadObj("../assets/bunny.obj", &gBunny)) {
    return false;
  }

  /* TODO: add materials and texture loading here */

  return true;
}
void drawBunny(void) {
  glPushMatrix();

  glColor3f(1.f, 0.f, 0.f);

  glBegin(GL_TRIANGLES);

  for (int i = 0; i < gBunny.faces.count; i++) {
    glVertex3f(gBunny.vertices.data[gBunny.faces.data[i].v1].x,
               gBunny.vertices.data[gBunny.faces.data[i].v1].y,
               gBunny.vertices.data[gBunny.faces.data[i].v1].z);

    glVertex3f(gBunny.vertices.data[gBunny.faces.data[i].v2].x,
               gBunny.vertices.data[gBunny.faces.data[i].v2].y,
               gBunny.vertices.data[gBunny.faces.data[i].v2].z);

    glVertex3f(gBunny.vertices.data[gBunny.faces.data[i].v3].x,
               gBunny.vertices.data[gBunny.faces.data[i].v3].y,
               gBunny.vertices.data[gBunny.faces.data[i].v3].z);
  }

  glEnd();

  glPopMatrix();
}

void setOrthographicProjection(void) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);
  gluOrtho2D(0, width, height, 0);

  glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection(void) {
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font, char *string) {
  glRasterPos2f(x, y);

  for (char *c = string; *c != '\0'; ++c) {
    glutBitmapCharacter(font, *c);
  }
}
