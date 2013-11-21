/** 
 *	main.c
 *	This program is a sudoku game that generates a random sudoku board every time,
 *	and provides solution to the user if the user cannot figure it out.
 *
 *	Shuyang Li and Adam Goins
 *	for CSE 20211
 *	First written on November 20, 2013
 **/

#include <stdio.h>
#include "gfx.h"

#define BOARD_SIZE 9
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

// typedef for boolean type
typedef enum { false = 0, true } boolean;

/*
   ==========================================================
   function prototypes to be implemented are all written here
   ==========================================================
*/

// sets up graphics window
void open_graphics();

// show game menu and get user input
void show_game_menu(int * usr);

// sets up a new game of sudoku, and returns when the user quits
void start_game();

// displays instructions, and returns as the user prompts
void show_instructions();

/*
   ==========================================
   completed function prototypes are all here
   ==========================================
*/

boolean isValidPosition(const int posX, const int posY, const char validPositions[BOARD_SIZE][BOARD_SIZE]);

/*
   =============
   main function
   =============
*/

int main() {

	// this function sets up graphics window
	open_graphics();

	// flag to check if user quits the game
	boolean userQuitsGame = false;

	// main game loop
	while (!userQuitsGame) {

		// show game menu and get user choice
		int userChoice = 0;
		show_game_menu(&userChoice);

		switch (userChoice) {

			// if user chooses to start game
			case 1:
				start_game();
				break;

			// if user chooses to show instructions
			case 2:
				show_instructions();
				break;

			// if user chooses to quit game, we only need to set the flag
			case 3:
				userQuitsGame = true;
				break;
		}

	}
	
	return 0;
}

boolean isValidPosition(const int posX, const int posY, const char validPositions[BOARD_SIZE][BOARD_SIZE]) {
	return validPositions[posX][posY];
}

void start_game() {

	// variable declaration for game board
	int solutionBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int puzzleBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean validPositions[BOARD_SIZE][BOARD_SIZE] = { 0 };

	// to be completed

}