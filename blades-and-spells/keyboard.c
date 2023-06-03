#include <stdbool.h>

#include "keyboard.h"

static bool mKeyState[256];

void keyDown(unsigned char key) {
	mKeyState[key] = true;
}

void keyUp(unsigned char key) {
	mKeyState[key] = false;
}
