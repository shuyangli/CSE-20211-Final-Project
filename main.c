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

// this library is for drawing numbers in the graphics window
#include "drawNumeral.h"

// this library is for drawing characters in the graphics window
#include "drawCharacters.h"

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
void show_game_menu(int *userChoice);

// displays instructions, and returns as the user prompts
void show_instructions();

// generates the solution board, and removes an appropriate number of numbers to generate the puzzle board, and saves the valid positions in the valid positions board
void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

// helper function to translate from screen location to board index
void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY);

// helper function to translate from board index to screen location
void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY);

/*
   ==========================================
   completed function prototypes are all here
   ==========================================
*/

// sets up a new game of sudoku, and returns when the current game ends
void start_game();

// given a position (x, y) on the board, this functions returns if the position is available for the user to change, i.e. it's not one of the computer-generated numbers
boolean isValidPosition(const int posX, const int posY, const char validPositions[BOARD_SIZE][BOARD_SIZE]);

// checks if the game ends
boolean isGameEnd(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]);

// updates the board with a given input at a given position
void updateBoard(const int xPos, const int yPos, const int inputNum, int puzzleBoard[BOARD_SIZE][BOARD_SIZE]);

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


void start_game() {

	// variable declaration for game board
	int solutionBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int puzzleBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean validPositions[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean userGivesUp = false;

	generateBoard(solutionBoard, puzzleBoard, validPositions);

	while (!isGameEnd(puzzleBoard) && !userGivesUp) {
		print_board(puzzleBoard);

		int xPos, yPos, inputNum;
		get_user_input(&xPos, &yPos, &inputNum);

		if (isValidPosition(xPos, yPos, validPositions) && isValidMove(xPos, yPos, inputNum, puzzleBoard)) {
			updateBoard(xPos, yPos, inputNum, puzzleBoard);
		} else {
			promptInvalid(xPos, yPos, inputNum);
		}
	}

	if (userGivesUp) {
		print_board(solutionBoard);
		// wait for user to continue
	}
}

void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {

	// to be implemented
}

boolean isGameEnd(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]) {

	int i, j;
	int numBlank = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (puzzleBoard[i][j] == 0) numBlank++;
		}
	}

	return (numBlank == 0);
}

void print_board(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]) {
	
	// to be implemented
}

void get_user_input(int *xPos, int *yPos) {

	// to be implemented
}

boolean isValidPosition(const int posX, const int posY, const char validPositions[BOARD_SIZE][BOARD_SIZE]) {

	return validPositions[posX][posY];
}

boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int puzzleBoard) {

	// to be implemented
}

void updateBoard(const int xPos, const int yPos, const int inputNum, int puzzleBoard[BOARD_SIZE][BOARD_SIZE]) {
	// it's okay to just set the board, since we have checked that the input is valid
	puzzleBoard[xPos][yPos] = inputNum;
}

void promptInvalid(const int xPos, const int yPos, const int inputNum) {

}

void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY) {

}

void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY) {

}