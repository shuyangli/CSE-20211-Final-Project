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
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

// this library is for drawing numbers in the graphics window
#include "drawNumeral.h"

// this library is for drawing characters in the graphics window
// it's incomplete implementation as of November 21, 2013
#include "drawCharacters.h"

#define BOARD_SIZE 9
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

// notice that the board is arranged as board[y][x]

// typedef for boolean
typedef enum { false = 0, true } boolean;

// global flag for debug
boolean debug = false;

/*
   ==========================================================
   function prototypes to be implemented are all written here
   ==========================================================
*/

// sets up graphics window
void openGraphics();

// show game menu and get user input
void showGameMenu(int *userChoice);

// displays instructions, and returns as the user prompts
void showInstructions();

// generates the solution board, and removes an appropriate number of numbers to generate the puzzle board, and saves the valid positions in the valid positions board
void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

// gets the user input: a click at a position, and an input number
// need to handle the case where the user clicks multiple times
void getUserInput(int *xPos, int *yPos, int *inputNum);

// helper function to translate from screen location to board index
void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY);

// helper function to translate from board index to screen location
void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY);

boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int board);


/*
   ==========================================
   completed function prototypes are all here
   ==========================================
*/

// sets up a new game of sudoku, and returns when the current game ends
void startGame();

// given a position (x, y) on the board, this functions returns if the position is available for the user to change, i.e. it's not one of the computer-generated numbers
boolean isValidPosition(const int posX, const int posY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

// checks if the game ends
boolean isGameEnd(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]);

// solves a given board with backtracking
// note: they are not debugged
boolean solveBoard(int board[BOARD_SIZE][BOARD_SIZE], const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);
boolean solveBoardSub(int board[BOARD_SIZE][BOARD_SIZE], int curX, int curY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

/*
   =============
   main function
   =============
*/

int main(int argc, char *argv[]) {

	// generate new random seed
	srand((unsigned)time(NULL));

	// this function sets up graphics window
	openGraphics();

	// flag to check if user quits the game
	boolean userQuitsGame = false;

	// main game loop
	while (!userQuitsGame) {

		// clear screen before doing anything else
		gfx_clear();

		// show game menu and get user choice
		int userChoice = 0;
		showGameMenu(&userChoice);

		switch (userChoice) {

			// if user chooses to start game
			case 1:
				startGame();
				break;

			// if user chooses to show instructions
			case 2:
				showInstructions();
				break;

			// if user chooses to quit game, we only need to set the flag
			case 3:
				userQuitsGame = true;
				break;
		}
	}
	
	return 0;
}

/*
   =======================
   function implementation
   =======================
*/

void startGame() {

	// variable declaration for game board
	int solutionBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int puzzleBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean validPositions[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean userGivesUp = false;

	generateBoard(solutionBoard, puzzleBoard, validPositions);

	while (!isGameEnd(puzzleBoard) && !userGivesUp) {
		printBoard(puzzleBoard);

		int xPos, yPos, inputNum;
		getUserInput(&xPos, &yPos, &inputNum);

		if (isValidPosition(xPos, yPos, validPositions) && isValidMove(xPos, yPos, inputNum, puzzleBoard)) {
			puzzleBoard[yPos][xPos] = inputNum;
		} else {
			promptInvalid(xPos, yPos, inputNum);
		}
	}

	if (userGivesUp) {
		printBoard(solutionBoard);
		// wait for user to continue
	}
}

void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {

	// there might be a chance for the boards to fail, so we need a flag
	boolean finished = false;

	while (!finished) {

		// initialize all three boards
		int i, j;
		for (i = 0; i < BOARD_SIZE; i++) {
			for (j = 0; j < BOARD_SIZE; j++) {
				solutionBoard[i][j] = 0;
				puzzleBoard[i][j] = 0;
				validPositions[i][j] = true;
			}
		}

		// we first generate 11 random cells on the solution board
		// according to a paper, generating 11 random cells is both efficient and not failure-prone
		int numLeft = 11;

		while (numLeft > 0) {
			int nextX = rand() % BOARD_SIZE;
			int nextY = rand() % BOARD_SIZE;

			if (isValidPosition(nextX, nextY, validPositions)) {
				// if the position is valid, generate a random number at that position
				// note it's 1 ~ 9, not 0 ~ 8
				int num = rand() % 9 + 1;

				// if that number is valid, update accordingly
				if (isValidMove(nextX, nextY, num, solutionBoard)) {
					solutionBoard[nextY][nextX] = num;
					validPositions[nextY][nextX] = false;

					// update numbers left
					numLeft--;
				}
			}
		}

		// after generating the valid positions, solve the board
		// if it's solvable, then finished 
		if (solveBoard(solutionBoard, validPositions)) finished = true;
	}

}

boolean solveBoard(int board[BOARD_SIZE][BOARD_SIZE], const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {
	// backtracking algorithm to solve a given sudoku board

	// get the first valid position
	int beginX = 0, beginY = 0;
	while (true) {
		if (isValidPosition(beginX, beginY, validPositions)) break;
		int tempX = beginX;
		beginX = (tempX >= BOARD_SIZE) ? 0 : beginX + 1;
		beginY = (tempX >= BOARD_SIZE) ? beginY + 1 : beginY;
	}

	return solveBoardSub(board, beginX, beginY, validPositions);
}

boolean solveBoardSub(int board[BOARD_SIZE][BOARD_SIZE], int curX, int curY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {

	// handle end-game case: curY is out of bounds
	if (curY >= BOARD_SIZE) return true;

	// try solving this position
	int trial;
	for (trial = 1; trial <= 9; trial++) {
		if (isValidMove(curX, curY, trial, board)) {
			// if it's valid, commit to it
			board[curY][curX] = trial;

			// generate next x and y
			int nextX = curX, nextY = curY;

			while (true) {
				int tempX = nextX;
				nextX = (tempX >= BOARD_SIZE) ? 0 : tempX + 1;
				nextY = (tempX >= BOARD_SIZE) ? nextY + 1 : nextY;
				if (isValidPosition(nextX, nextY, validPositions)) break;
			}

			// backtracking: if the next steps are all successful, return success
			if (solveBoardSub(board, nextX, nextY, validPositions)) {
				return true;
			} else {
				// if not, undo this move and do next trial
				board[curY][curX] = 0;
			}
		}
	}

	// if all moves failed for this position, return failure
	return false;
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

void printBoard(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]) {
	
	// to be implemented
}

void getUserInput(int *xPos, int *yPos, int *inputNum) {

	// to be implemented
}

boolean isValidPosition(const int posX, const int posY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {
	return validPositions[posY][posX];
}

boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE]) {

	// first check horizontally
	int curX;
	for (curX = 0; curX < BOARD_SIZE; curX++) {
		if (board[yPos][curX] == inputNum) return false;
	}

	// then check vertically
	int curY;
	for (curY = 0; curY < BOARD_SIZE; curY++) {
		if (board[curY][xPos] == inputNum) return false;
	}

	// finally check the grid
	return checkGrid(xPos, yPos, inputNum, board);
}

boolean checkGrid(int x, int y,const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE]) {

	int baseX, baseY;

	if (x >= 0 && x < 3) baseX = 0;
	else if (x >= 3 && x < 6) baseX = 3;
	else baseX = 6;

	if (y >= 0 && y < 3) baseY = 0;
	else if (y >= 3 && y < 6) baseY = 3;
	else baseY = 6;

	int i, j;
	for (i = baseX; i < baseX + 3; i++) {
		for (j = baseY; j < baseY + 3; j++) {
			if (board[j][i] == inputNum) return false;
		}
	}

	return true;
}

void promptInvalid(const int xPos, const int yPos, const int inputNum) {

}

void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY) {

}

void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY) {

}