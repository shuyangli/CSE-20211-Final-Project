/*
	drawNumeral.h
	This is a simple library built upon the gfx library, which draws numbers 0 to 9 on the screen.

	Shuyang Li
	for CSE 20211
	First written on September 23, 2013
*/

#include "drawNumeral.h"
#include "gfx.h"
#include <math.h>

static int globalHeight = 100;

void dn_draw_numeral(int x, int y, int event) {

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
			dn_draw_numeral(x, y, -event);
		} else if (event >= 10) {
			draw_two_digits(x, y, event, height);
		}

	}
}

void dn_update_height(int newHeight) {
	globalHeight = newHeight;
}

int dn_get_height() {
	return globalHeight;
}

void draw_two_digits (int x, int y, int number, int height) {
	int width = height / 2;
	dn_draw_numeral(x, y, number / 10);
	dn_draw_numeral(x + width, y, number % 10);
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