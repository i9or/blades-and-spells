#include <ApplicationServices/ApplicationServices.h>
#include <GLUT/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
#include "image.h"
#include "load_mtl.h"
#include "load_obj.h"
#include "load_tga.h"
#include "logger.h"

#include "camera.h"
#include "grid.h"
#include "keyboard.h"

#define WINDOWED_MODE true /* change to "false" to run game in fullscreen */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

static bool gFpsMode = false;
static char gDrawingTime[64] = "";
static float gLightAngle = 100.f; //-270.f;
static int gAccum = 0;

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
static Material gBunnyMaterial;
static Image gHeightmap;
static Mesh gLandscape;

bool loadBunny(void);
void drawBunny(void);
void setOrthographicProjection(void);
void restorePerspectiveProjection(void);
void renderBitmapString(float x, float y, void *font, char *string);
void drawTeapot(void);
bool loadHeightmap(void);
void drawLandscape(void);
void drawSun(void);

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

  glClearColor(0.3f, 0.4f, 0.6f, 1.f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Sunlight
  float lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.f };
  float lightSpecular[] = { 1.f, 1.f, 1.f, 1.f };

  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

  cameraInit();

  loadBunny();
  loadHeightmap();
}

void cleanUp(void) {
  LOG_DEBUG("Cleaning up a game");

  destroyMesh(&gBunny);
  destroyMesh(&gLandscape);
}

void displayHandler(void) {
  int t1 = glutGet(GLUT_ELAPSED_TIME);
  processKeyboard();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  processCamera();

  /* Draw scene here */
  drawSun();
//  drawGrid();
  drawLandscape();
//  drawBunny();
//  drawTeapot();
  /* =============== */

  glDisable(GL_LIGHTING);
  setOrthographicProjection();
  glPushMatrix();
  glLoadIdentity();
  glColor3f(0.f, 1.f, 1.f);
  renderBitmapString(5, 20, GLUT_BITMAP_HELVETICA_18, gDrawingTime);

  char sunAngle[64];
  sprintf(sunAngle, "Sun: %f", gLightAngle);
  renderBitmapString(5, 40, GLUT_BITMAP_HELVETICA_18, sunAngle);

  glPopMatrix();

  restorePerspectiveProjection();
  glEnable(GL_LIGHTING);

  glutSwapBuffers();

  int t2 = glutGet(GLUT_ELAPSED_TIME);

  gAccum++;
  if (gAccum > 5) {
    sprintf(gDrawingTime, "Draw time: %d", t2 - t1);
    gAccum = 0;
  }
}

void drawTeapot(void) {
  glPushMatrix();
  glTranslatef(10.f, 1.4f, 10.f);
  glColor3f(0.6f, 0.4f, 0.6f);
  glutSolidTeapot(2.0);
  glPopMatrix();
}

void reshapeHandler(int w, int h) {
  if (h < 1) {
    h = 1;
  }

  double ratio = (double)w / (double)h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, ratio, 0.1, 5000.0);
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

  if (isKeyPressed(U_KEY)) {
    cameraFly(1.f);
  }

  if (isKeyPressed(J_KEY)) {
    cameraFly(-1.f);
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
  if (!loadObj("../assets/bunny.obj", &gBunny)) {
    return false;
  }

  char mtlPath[MAX_FILE_PATH_LENGTH];
  sprintf(mtlPath, "%s%s", "../assets/", gBunny.materialLib);
  if (!loadMtl(mtlPath, &gBunnyMaterial)) {
    return false;
  }

  LOG_DEBUG("Material name: %s", gBunnyMaterial.name);
  LOG_DEBUG("Diffuse map: %s", gBunnyMaterial.diffuseMapPath);
  LOG_DEBUG("Diffuse color: %f %f %f",
            gBunnyMaterial.diffuseColor.x,
            gBunnyMaterial.diffuseColor.y,
            gBunnyMaterial.diffuseColor.z);

  /* TODO: add texture loading here */

  return true;
}
void drawBunny(void) {
  glPushMatrix();

//  glColor3f(gBunnyMaterial.diffuseColor.x,
//            gBunnyMaterial.diffuseColor.y,
//            gBunnyMaterial.diffuseColor.z);

  glBegin(GL_TRIANGLES);

  for (int i = 0; i < gBunny.faces.count; i++) {
    glNormal3f(gBunny.normals.data[gBunny.faces.data[i].n1].x,
               gBunny.normals.data[gBunny.faces.data[i].n1].y,
               gBunny.normals.data[gBunny.faces.data[i].n1].z);
    glVertex3f(gBunny.vertices.data[gBunny.faces.data[i].v1].x,
               gBunny.vertices.data[gBunny.faces.data[i].v1].y,
               gBunny.vertices.data[gBunny.faces.data[i].v1].z);

    glNormal3f(gBunny.normals.data[gBunny.faces.data[i].n2].x,
               gBunny.normals.data[gBunny.faces.data[i].n2].y,
               gBunny.normals.data[gBunny.faces.data[i].n2].z);
    glVertex3f(gBunny.vertices.data[gBunny.faces.data[i].v2].x,
               gBunny.vertices.data[gBunny.faces.data[i].v2].y,
               gBunny.vertices.data[gBunny.faces.data[i].v2].z);

    glNormal3f(gBunny.normals.data[gBunny.faces.data[i].n3].x,
               gBunny.normals.data[gBunny.faces.data[i].n3].y,
               gBunny.normals.data[gBunny.faces.data[i].n3].z);
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

bool loadHeightmap(void) {
  if (!loadTga("../assets/heightmap.tga", &gHeightmap)) {
    return false;
  }

  initMesh(&gLandscape);

  const float SCALE_FACTOR = 2.f;

  int w = gHeightmap.header.width;
  int h = gHeightmap.header.height;

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      int index = y * w * 4 + x * 4;

      float vx = ((float)x - (float)w / 2.f) * SCALE_FACTOR;
      float vy = (float)gHeightmap.imageData[index];
      float vz = ((float)y - (float)h / 2.f) * SCALE_FACTOR;

      addMeshVertex(&gLandscape, (Vec3) { .x = vx, .y = vy, .z = vz });
    }
  }

  int normalIndex = 0;

  for (int y = 0; y < h - 1; ++y) {
    for (int x = 0; x < w - 1; ++x) {
      int v1 = y * w + x;
      int v2 = (y + 1) * w + x;
      int v3 = y * w + x + 1;
      int v4 = (y + 1) * w + x + 1;

      Vec3 a = sub3(&gLandscape.vertices.data[v2], &gLandscape.vertices.data[v1]);
      Vec3 b = sub3(&gLandscape.vertices.data[v3], &gLandscape.vertices.data[v1]);
      Vec3 n1 = cross3(&a, &b);
      normalize3(&n1);

      addMeshNormal(&gLandscape, n1);
      addMeshFace(&gLandscape,
                  (Face) { .v1 = v1, .v2 = v2, .v3 = v3, //
                           .n1 = normalIndex,
                           .n2 = normalIndex,
                           .n3 = normalIndex });
      normalIndex++;

      Vec3 c = sub3(&gLandscape.vertices.data[v2], &gLandscape.vertices.data[v3]);
      Vec3 d = sub3(&gLandscape.vertices.data[v4], &gLandscape.vertices.data[v3]);
      Vec3 n2 = cross3(&c, &d);
      normalize3(&n2);

      addMeshNormal(&gLandscape, n2);
      addMeshFace(&gLandscape,
                  (Face) { .v1 = v3, .v2 = v2, .v3 = v4, //
                           .n1 = normalIndex,
                           .n2 = normalIndex,
                           .n3 = normalIndex });
      normalIndex++;
    }
  }

  Vec3Array smoothNormals;
  initArray(smoothNormals);

  for (int i = 0; i < gLandscape.vertices.count; ++i) {
    Vec3Array normals;
    initArray(normals);

    for (int j = 0; j < gLandscape.faces.count; ++j) {
      if (gLandscape.faces.data[j].v1 == i ||
          gLandscape.faces.data[j].v2 == i ||
          gLandscape.faces.data[j].v3 == i) {
        Vec3 n = gLandscape.normals.data[gLandscape.faces.data[j].n1];
        pushToArray(normals, n);
      }

      // Six is the maximum number of faces sharing the same vertex
      if (normals.count == 6) {
        break;
      }
    }

    Vec3 averageNormal = (Vec3) { .x = 0.f, .y = 0.f, .z = 0.f };
    for (int j = 0; j < normals.count; ++j) {
      averageNormal = add3(&averageNormal, &(normals.data[j]));
    }

    div3(&averageNormal, normals.count);
    normalize3(&averageNormal);

    pushToArray(smoothNormals, averageNormal);
  }

  destroyArray(gLandscape.normals);
  initArray(gLandscape.normals);

  for (int i = 0; i < smoothNormals.count; ++i) {
    pushToArray(gLandscape.normals, smoothNormals.data[i]);
  }

  for (int i = 0; i < gLandscape.faces.count; ++i) {
    int v1 = gLandscape.faces.data[i].v1;
    int v2 = gLandscape.faces.data[i].v2;
    int v3 = gLandscape.faces.data[i].v3;

    gLandscape.faces.data[i].n1 = v1;
    gLandscape.faces.data[i].n2 = v2;
    gLandscape.faces.data[i].n3 = v3;
  }

  return true;
}

void setColorByHeight(float height) {
  if (height >= 0.f && height <= 0.3f) {
    float color[4] = { 58.f / 255.f, 65.f / 255.f, 36.f / 255.f, 1.0 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color );
  } else if (height > 0.3f && height <= 0.7f) {
    float color[4] = { 62.f / 255.f, 37.f / 255.f, 22.f / 255.f, 1.0 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color );
  } else {
    float color[4] = { 1.f, 0.98f, 0.98f, 1.0 };
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color );
  }
}

void drawLandscape(void) {
  glPushMatrix();

  glEnable(GL_LIGHTING);

  glBegin(GL_TRIANGLES);

  for (int i = 0; i < gLandscape.faces.count; ++i) {
    int v1 = gLandscape.faces.data[i].v1;
    int v2 = gLandscape.faces.data[i].v2;
    int v3 = gLandscape.faces.data[i].v3;
    int n1 = gLandscape.faces.data[i].n1;
    int n2 = gLandscape.faces.data[i].n2;
    int n3 = gLandscape.faces.data[i].n3;

    setColorByHeight(gLandscape.vertices.data[v1].y / 255.f);
    glNormal3f(gLandscape.normals.data[n1].x,
               gLandscape.normals.data[n1].y,
               gLandscape.normals.data[n1].z);

    glVertex3f(gLandscape.vertices.data[v1].x,
               gLandscape.vertices.data[v1].y * 0.1f,
               gLandscape.vertices.data[v1].z);

    setColorByHeight(gLandscape.vertices.data[v2].y / 255.f);
    glNormal3f(gLandscape.normals.data[n2].x,
               gLandscape.normals.data[n2].y,
               gLandscape.normals.data[n2].z);

    glVertex3f(gLandscape.vertices.data[v2].x,
               gLandscape.vertices.data[v2].y * 0.1f,
               gLandscape.vertices.data[v2].z);

    setColorByHeight(gLandscape.vertices.data[v3].y / 255.f);
    glNormal3f(gLandscape.normals.data[n3].x,
               gLandscape.normals.data[n3].y,
               gLandscape.normals.data[n3].z);

    glVertex3f(gLandscape.vertices.data[v3].x,
               gLandscape.vertices.data[v3].y * 0.1f,
               gLandscape.vertices.data[v3].z);
  }

  glEnd();

  glPopMatrix();
}

void drawSun(void) {
//  gLightAngle += 0.1f;
//  if (gLightAngle > 360.f) {
//    gLightAngle -= 360.f;
//  }

  const float SCALE_FACTOR = 5.f;
  float lightX = 100.f * cosf(gLightAngle * (float)M_PI / 180.f) * SCALE_FACTOR;
  float lightY = 75.f * sinf(gLightAngle * (float)M_PI / 180.f) * SCALE_FACTOR;
  float lightZ = 100.f * sinf(gLightAngle * (float)M_PI / 180.f) * SCALE_FACTOR;
  float lightPosition[] = { lightX, lightY, lightZ, 1.f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  float lightBrightness = sinf(gLightAngle * (float)M_PI / 180.f);
  if (lightBrightness < 0.2f) {
    lightBrightness = 0.2f;
  }
  float lightDiffuse[] = { lightBrightness, lightBrightness, lightBrightness * 0.8f, 1.f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

  glDisable(GL_LIGHTING);
  glPushMatrix();
  glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
  glColor3f(1.f, 1.f, 1.f);
  glutSolidSphere(5.f * SCALE_FACTOR, 8, 8);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}
