#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

typedef enum {
  ESCAPE_KEY = 27,
  F_KEY = 102,
  W_KEY = 119,
  SHIFT_W_KEY = 87,
  A_KEY = 97,
  SHIFT_A_KEY = 65,
  S_KEY = 115,
  SHIFT_S_KEY = 83,
  D_KEY = 100,
  SHIFT_D_KEY = 68,
  T_KEY = 116,
  SHIFT_T_KEY = 84,
  G_KEY = 103,
  SHIFT_G_KEY = 71
} Keys;

void pressKey(unsigned char key);

void resetKey(unsigned char key);

bool isKeyPressed(unsigned char key);

#endif /* KEYBOARD_H */
