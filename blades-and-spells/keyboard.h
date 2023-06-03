#ifndef BNS_KEYBOARD_H
#define BNS_KEYBOARD_H

typedef enum {
	ESCAPE_KEY = 27,
	F_KEY = 102
} Keys;

void keyDown(unsigned char);

void keyUp(unsigned char);

#endif /* BNS_KEYBOARD_H */
