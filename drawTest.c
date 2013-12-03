/*
	drawTest.c
	This program serves as a blackbox test for the drawNumeral and drawCharacters libraries

	Shuyang Li
	First written 
*/

#include "gfx.h"
#include <string.h>
#include <math.h>
#include "drawCharacters.h"

int main(int argc, char *argv[]) {

	char event = ' ';
	int x, y, height;
	const int WINDOW_W = 1000, WINDOW_H = 800;

	gfx_open(WINDOW_W, WINDOW_H, "Typewriter");
	while (event != 1) {
		event = gfx_wait();
		x = gfx_xpos();
		y = gfx_ypos();

		if (event == '-') {
			height = dc_getHeight();
			height /= 2;
			dc_updateHeight(height);
		} else if (event == '=') {
			height = dc_getHeight();
			height *= 2;
			dc_updateHeight(height);
		} else {
			if (event - '0' < 0 || event - '0' > 9) {
				dc_drawCharacter(x, y, event);
			} else {
				dc_drawNumeral(x, y, event - '0');
			}
		}
	}

	return 0;
}