/* 
	drawCharacters.c
	This library provides the proper functions to draw a given character on
	the X11 window, based on the gfx library provided by Prof. Thain
	
	Shuyang Li
	for CSE 20211
	First written on September 23, 2013
*/

#include "drawCharacters.h"
#include "gfx.h"
#include <math.h>

#define PI 3.14159265


void drawCharacter(int x, int y, int width, int height, char c) {
	switch (c) {
		case 'a':
		case 'A':
		draw_A(x, y, width, height);
		break;

		case 'b':
		case 'B':
		draw_B(x, y, width, height);
		break;

		case 'c':
		case 'C':
		draw_C(x, y, width, height);
		break;

		case 'd':
		case 'D':
		draw_D(x, y, width, height);
		break;

		case 'e':
		case 'E':
		draw_E(x, y, width, height);
		break;

		case 'f':
		case 'F':
		draw_F(x, y, width, height);
		break;

		case 'g':
		case 'G':
		draw_G(x, y, width, height);
		break;

		case 'h':
		case 'H':
		draw_H(x, y, width, height);
		break;

		case 'i':
		case 'I':
		draw_I(x, y, width, height);
		break;

		case 'j':
		case 'J':
		draw_J(x, y, width, height);
		break;

		case 'k':
		case 'K':
		draw_K(x, y, width, height);
		break;

		case 'l':
		case 'L':
		draw_L(x, y, width, height);
		break;

		case 'm':
		case 'M':
		draw_M(x, y, width, height);
		break;

		case 'n':
		case 'N':
		draw_N(x, y, width, height);
		break;

		case 'o':
		case 'O':
		draw_O(x, y, width, height);
		break;

		case 'p':
		case 'P':
		draw_P(x, y, width, height);
		break;

		case 'q':
		case 'Q':
		draw_Q(x, y, width, height);
		break;

		case 'r':
		case 'R':
		draw_R(x, y, width, height);
		break;

		case 's':
		case 'S':
		draw_S(x, y, width, height);
		break;

		case 't':
		case 'T':
		draw_T(x, y, width, height);
		break;

		case 'u':
		case 'U':
		draw_U(x, y, width, height);
		break;

		case 'v':
		case 'V':
		draw_V(x, y, width, height);
		break;

		case 'w':
		case 'W':
		draw_W(x, y, width, height);
		break;

		case 'x':
		case 'X':
		draw_X(x, y, width, height);
		break;

		case 'y':
		case 'Y':
		draw_Y(x, y, width, height);
		break;

		case 'z':
		case 'Z':
		draw_Z(x, y, width, height);
		break;

		default:
		draw_nonsense(x, y, width, height);
		break;
	}
}

void draw_A(int x, int y, int width, int height) {
	gfx_line (x, y + height, x + width / 2, y);
	gfx_line (x + width / 2, y, x + width, y + height);
	gfx_line ( x + width / 4, y + height / 2, x + width * 3 / 4, y + height / 2);
}

void draw_B(int x, int y, int width, int height) {
	gfx_line (x, y + height, x, y);
	draw_char_arc (x, y + height / 4, width / 2, - PI / 2, PI / 2);
	draw_char_arc (x, y + height * 3 / 4, width / 2, - PI / 2, PI / 2);
}

void draw_C(int x, int y, int width, int height) {}
void draw_D(int x, int y, int width, int height) {}
void draw_E(int x, int y, int width, int height) {}
void draw_F(int x, int y, int width, int height) {}
void draw_G(int x, int y, int width, int height) {}
void draw_H(int x, int y, int width, int height) {}
void draw_I(int x, int y, int width, int height) {}
void draw_J(int x, int y, int width, int height) {}
void draw_K(int x, int y, int width, int height) {}
void draw_L(int x, int y, int width, int height) {}
void draw_M(int x, int y, int width, int height) {}
void draw_N(int x, int y, int width, int height) {}
void draw_O(int x, int y, int width, int height) {}
void draw_P(int x, int y, int width, int height) {}
void draw_Q(int x, int y, int width, int height) {}
void draw_R(int x, int y, int width, int height) {}
void draw_S(int x, int y, int width, int height) {}
void draw_T(int x, int y, int width, int height) {}
void draw_U(int x, int y, int width, int height) {}
void draw_V(int x, int y, int width, int height) {}
void draw_W(int x, int y, int width, int height) {}
void draw_X(int x, int y, int width, int height) {}
void draw_Y(int x, int y, int width, int height) {}
void draw_Z(int x, int y, int width, int height) {}

void draw_arc(int x, int y, int radius, double alpha, double beta) {
	double theta, dtheta = 0.01;
	for (theta = alpha; theta <= beta; theta += dtheta) {
		double ax = x + radius * cos(theta);
		double ay = y + radius * sin(theta);
		double bx = x + radius * cos(theta + dtheta);
		double by = y + radius * sin(theta + dtheta);
		gfx_line(ax, ay, bx, by);
	}
}