/*
	drawNumeral.h
	This is a simple library built upon the gfx library, which draws numbers 0 to 9 on the screen.

	Shuyang Li
	for CSE 20211
	First written on September 23, 2013
*/


#ifndef __drawNumeral_h__
#define __drawNumeral_h__

#define PI 3.14159265

/*
	draw_numeral
	this function draws the given number at position x and y with the default height
	x: x position
	y: y position
	number: number to draw on screen
*/
void dn_draw_numeral (int x, int y, int number);

/*
	dn_update_height
	this function updates the default height for drawing the numbers
	newHeight: new value of the neight

	recommended: update height before drawing the first figure to gain more control
	the default height is 100
*/
void dn_update_height (int newHeight);

/*
	dn_get_height
	this function returns the height currently used to draw the numbers
*/
int dn_get_height ();


// these are private helper functions
// draw_negative_sign: draw negative sign before the number
void draw_negative_sign(int x, int y, int height);

// draw_arc: draw an arc with axes between two angles
void draw_arc (int x, int y, int x_axis_radius, int y_axis_radius, float alpha, float beta);

// draw_two_digits: draw a number that has 2 digits
void draw_two_digits (int x, int y, int number, int height);


// functions to draw specific characters
// these functions use draw_arc as well as the gfx library to draw appropriate numbers on screen
// however, you should use draw_numeral instead of these specific functions to draw the numbers
void draw_one (int x, int y, int height);
void draw_two (int x, int y, int height);
void draw_three (int x, int y, int height);
void draw_four (int x, int y, int height);
void draw_five (int x, int y, int height);
void draw_six (int x, int y, int height);
void draw_seven (int x, int y, int height);
void draw_eight (int x, int y, int height);
void draw_nine (int x, int y, int height);
void draw_zero (int x, int y, int height);


#endif