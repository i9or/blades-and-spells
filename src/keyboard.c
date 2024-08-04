#include <stdbool.h>

#include "keyboard.h"

static bool mKeyState[256];

void pressKey(unsigned char key) {
  mKeyState[key] = true;
}

void resetKey(unsigned char key) {
  mKeyState[key] = false;
}

bool isKeyPressed(unsigned char key) {
  return mKeyState[key];
}
