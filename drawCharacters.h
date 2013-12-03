/* 
	drawCharacters.c
	This library provides the proper functions to draw a given character on
	the X11 window, based on the gfx library provided by Prof. Thain
	
	Shuyang Li
	for CSE 20211
	First written on September 23, 2013
*/

#ifndef __draw_characters__
#define __draw_characters__

#define PI 3.14159265

/*
	dc_drawString
	this function draws a given string at position x and y with the default height
	x: x position
	y: y position
	str: string to draw on screen
*/
void dc_drawString(int x, int y, char *str);

/*
	dc_drawCharacter
	this function draws a given character at position x and y with the default height
	x: x position
	y: y position
	c: character to draw on screen
*/
void dc_drawCharacter(int x, int y, char c);

/*
	dc_drawNumeral
	this function draws the given number at position x and y with the default height
	x: x position
	y: y position
	number: number to draw on screen
*/
void dc_drawNumeral (int x, int y, int number);

/*
	dn_updateHeight
	this function updates the default height for drawing the numbers
	newHeight: new value of the neight

	recommended: update height before drawing the first figure to gain more control
	the default height is 100
*/
void dc_updateHeight (int newHeight);

/*
	dn_getHeight
	this function returns the height currently used to draw the numbers
*/
int dc_getHeight ();


// these are private helper functions
// draw_negative_sign: draw negative sign before the number
void draw_negative_sign(int x, int y, int height);

// draw_arc: draw an arc with axes between two angles
void draw_arc (int x, int y, int x_axis_radius, int y_axis_radius, float alpha, float beta);

// draw_two_digits: draw a number that has 2 digits
void draw_two_digits (int x, int y, int number, int height);


// functions to draw specific characters
// these functions use draw_arc as well as the gfx library to draw appropriate numbers on screen
// however, you should use dc_drawString, dc_drawCharacter and dc_drawNumeral instead of these specific functions
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

void draw_A(int x, int y, int height);
void draw_B(int x, int y, int height);
void draw_C(int x, int y, int height);
void draw_D(int x, int y, int height);
void draw_E(int x, int y, int height);
void draw_F(int x, int y, int height);
void draw_G(int x, int y, int height);
void draw_H(int x, int y, int height);
void draw_I(int x, int y, int height);
void draw_J(int x, int y, int height);
void draw_K(int x, int y, int height);
void draw_L(int x, int y, int height);
void draw_M(int x, int y, int height);
void draw_N(int x, int y, int height);
void draw_O(int x, int y, int height);
void draw_P(int x, int y, int height);
void draw_Q(int x, int y, int height);
void draw_R(int x, int y, int height);
void draw_S(int x, int y, int height);
void draw_T(int x, int y, int height);
void draw_U(int x, int y, int height);
void draw_V(int x, int y, int height);
void draw_W(int x, int y, int height);
void draw_X(int x, int y, int height);
void draw_Y(int x, int y, int height);
void draw_Z(int x, int y, int height);


#endif