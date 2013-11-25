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

static int globalHeight = 100;

void dc_drawCharacter(int x, int y, int width, int height, char c) {
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
	}
}

void dc_drawNumeral(int x, int y, int event) {
	int height = globalHeight;
	switch (event) {

		case 0:
		draw_zero(x, y, height);
		break;

		case 1:
		draw_one(x, y, height);
		break;

		case 2:
		draw_two(x, y, height);
		break;

		case 3:
		draw_three(x, y, height);
		break;

		case 4:
		draw_four(x, y, height);
		break;

		case 5:
		draw_five(x, y, height);
		break;

		case 6:
		draw_six(x, y, height);
		break;

		case 7:
		draw_seven(x, y, height);
		break;

		case 8:
		draw_eight(x, y, height);
		break;

		case 9:
		draw_nine(x, y, height);
		break;

		default:
		if (event < 0) {
			draw_negative_sign(x, y, height);
			dc_drawNumeral(x, y, -event);
		} else if (event >= 10) {
			draw_two_digits(x, y, event, height);
		}

	}
}

void draw_A(int x, int y, int width, int height) {
	gfx_line (x, y + height, x + width / 2, y);
	gfx_line (x + width / 2, y, x + width, y + height);
	gfx_line ( x + width / 4, y + height / 2, x + width * 3 / 4, y + height / 2);
}

void draw_B(int x, int y, int width, int height) {}
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

void dc_update_height(int newHeight) {
	globalHeight = newHeight;
}

int dc_get_height() {
	return globalHeight;
}

void draw_two_digits (int x, int y, int number, int height) {
	int width = height / 2;
	dc_drawNumeral(x, y, number / 10);
	dc_drawNumeral(x + width, y, number % 10);
}

void draw_negative_sign(int x, int y, int height) {
	int length = height / 5;
	gfx_line(x - 1.2 * length, y + height / 2, x - 0.2 * length, y + height / 2);
}

void draw_arc (int x, int y, int x_axis_radius, int y_axis_radius, float alpha, float beta) {
	float theta, dtheta = 0.03;
	int x1, y1, x2, y2;
	for (theta = alpha; theta < beta; theta += dtheta) {
		x1 = x + x_axis_radius + x_axis_radius * cos(theta);
		y1 = y + y_axis_radius - y_axis_radius * sin(theta);
		x2 = x + x_axis_radius + x_axis_radius * cos(theta + dtheta);
		y2 = y + y_axis_radius - y_axis_radius * sin(theta + dtheta);
		gfx_line(x1, y1, x2, y2);
	}
}

void draw_one(int x, int y, int height) {
	int width = height / 2;
	gfx_line(x, y + height, x + width, y + height);
	gfx_line(x + width / 2, y + height, x + width / 2, y);
	gfx_line(x, y + height / 10, x + width / 2, y);
}

void draw_two (int x, int y, int height) {
	int width = height / 2;
	gfx_line(x, y + height, x + width, y + height);
	draw_arc(x, y, width / 2, height / 4, 0, PI);
	gfx_line(x + width, y + height / 4, x, y + height);
}

void draw_three (int x, int y, int height) {
	int width = height / 2;
	draw_arc(x, y, width / 2, height / 4, - PI / 2, PI);
	draw_arc(x, y + height / 2, width / 2, height / 4, - PI, PI / 2);
}

void draw_four (int x, int y, int height) {
	int width = height / 2;
	gfx_line(x, y + height * 3 / 4, x + width, y + height * 3 / 4);
	gfx_line(x, y + height * 3 / 4, x + width * 2 / 3, y);
	gfx_line(x + width * 2 / 3, y, x + width * 2 / 3, y + height);
	// gfx_line(x + width * 2 / 3 - width / 5, y + height, x + width * 2 / 3 + width / 5, y + height);
}

void draw_five (int x, int y, int height) {
	int width = height / 2;
	int radius = (2 - sqrt(2)) * width;
	gfx_line(x, y, x + width, y);
	gfx_line(x, y, x, y + height / 2);
	// gfx_line(x, y + height / 2, x + width / 2, y + height / 2);
	draw_arc(x + width - 2 * radius, y + height - 2 * radius, radius, radius, - PI * 3 / 4, PI * 3 / 4);
}

void draw_six (int x, int y, int height) {
	int width = height / 2;
	int radius = width / 2;
	// draw_arc(x, y, width / 2, height * 3 / 4, PI / 2, PI);
	gfx_line(x + radius, y, x + radius * (1 - sqrt(8) / 3), y + height / 2 + radius * 2 / 3);
	draw_arc(x, y + height / 2, radius, radius, 0, 2 * PI);
}

void draw_seven (int x, int y, int height) {
	int width = height / 2;
	gfx_line(x, y, x + width, y);
	gfx_line(x + width, y, x, y + height);
}

void draw_eight (int x, int y, int height) {
	int width = height / 2;
	int radius = width / 2;
	draw_arc(x, y, radius, radius, 0, 2 * PI);
	draw_arc(x, y + height / 2, radius, radius, 0, 2 * PI);
}

void draw_nine (int x, int y, int height) {
	int width = height / 2;
	int radius = width / 2;
	draw_arc(x, y, radius, radius, 0, 2 * PI);
	gfx_line(x + width - radius * (1 - sqrt(8) / 3), y + height / 2 - radius * 2 / 3, x + radius, y + height);
}

void draw_zero (int x, int y, int height) {
	int width = height / 2;
	draw_arc(x, y, width / 2, height / 2, 0, 2 * PI);
}