#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ApplicationServices/ApplicationServices.h>

#include <GLUT/glut.h>

#include "keyboard.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

float gTriangleAngle = 0.f;
bool gKeyState[256];
bool gFpsMode = false;

void initGame(void);
void displayHandler(void);
void reshapeHandler(int, int);
void keyDownHandler(unsigned char, int, int);
void keyUpHandler(unsigned char, int, int);
void mouseMotionHandler(int, int);
void processKeyboard(void);

void drawGrid(void);
void drawTriangle(void);

int main(int argc, char** argv) {
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
}

void displayHandler(void) {
	processKeyboard();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(5.f, 2.f, 5.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f);

	drawGrid();
	drawTriangle();

	glutSwapBuffers();
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

	glMatrixMode(GL_MODELVIEW);
}

void keyDownHandler(unsigned char key, int x, int y) {
	if (key == ESCAPE_KEY) {
		exit(EXIT_SUCCESS);
	}

	keyDown(key);

	glutPostRedisplay();
}

void keyUpHandler(unsigned char key, int x, int y) {
	keyUp(key);

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
	static bool justWarped = false;

	if (justWarped) {
		justWarped = false;
		return;
	}

	if (gFpsMode) {
		justWarped = true;
		int w = glutGet(GLUT_WINDOW_WIDTH);
		int h = glutGet(GLUT_WINDOW_HEIGHT);
		float windowPosX = (float)glutGet(GLUT_WINDOW_X);
		float windowPosY = (float)glutGet(GLUT_WINDOW_Y);

		CGPoint warpPoint = CGPointMake((float)w / 2 + windowPosX, (float)h / 2 + windowPosY);
		CGWarpMouseCursorPosition(warpPoint);
		CGAssociateMouseAndMouseCursorPosition(true);

		int dx = (w / 2) - x;
		int dy = (h / 2) - y;

		if (dx && dy) {
			printf("dx: %d, dy: %d\n", dx, dy);
		}
	}

	glutPostRedisplay();
}

void processKeyboard(void) {
	if (gKeyState[F_KEY]) {
		gKeyState[F_KEY] = false;
		gFpsMode = !gFpsMode;

		if (gFpsMode) {
			CGDisplayHideCursor(CGMainDisplayID());
		} else {
			CGDisplayShowCursor(CGMainDisplayID());
		}
	}
}
