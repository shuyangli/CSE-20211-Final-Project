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
#define BOX_LENGTH 55.56
#define TOP_LEFT 50
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 700

// macro version for isValidPosition: for possible future optimization
// #define isValidPosition(__VPPosX__, __VPPosY__) validPositions[__VPPosY__][__VPPosX__]

// notice that the board is arranged as board[y][x]

// typedef for boolean
typedef enum { false = 0, true } boolean;

// typedef for hardness
typedef enum { easy, medium, hard } hardness;

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
void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE], hardness h);

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

// given a position and a move on the board, this function returns if the move is valid according to Sudoku rules
boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE])

// checks if the game ends
boolean isGameEnd(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]);

// solves a given board with backtracking
// note: they are not debugged
boolean solveBoard(int board[BOARD_SIZE][BOARD_SIZE], const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);
boolean solveBoardSub(int board[BOARD_SIZE][BOARD_SIZE], int curX, int curY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

void draw_grid(double x, double y, double length, double box_length);

/*
   =============
   main function
   =============
*/

int main(int argc, char *argv[]) {

	// generate new random seed
	srand((unsigned)time(NULL));

	// sets up graphics window
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

	hardness h;

	// TODO: prompt user to select hardness

	generateBoard(solutionBoard, puzzleBoard, validPositions, h);

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

void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE], hardness h) {

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

		// we first generate 18 random cells on the solution board
		int numLeft = 18;
		
		while (numLeft > 0) {
			int nextX = rand() % BOARD_SIZE;
			int nextY = (numLeft > 16) ? 0 : rand() % BOARD_SIZE;
			
			if (isValidPosition(nextX, nextY)) {
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
		// if it's solvable, then it's a finished solution board 
		if (solveBoard(solutionBoard, validPositions)) finished = true;
	}

	// after solving the board, we update the puzzle board and valid positions to fill all positions
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			puzzleBoard[i][j] = solutionBoard[i][j];
			validPositions[i][j] = false;
		}
	}

	// then we dig holes in the boards, 

}

boolean solveBoard(int board[BOARD_SIZE][BOARD_SIZE], const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {
	// backtracking algorithm to solve a given sudoku board

	// get the first valid position
	int beginX = 0, beginY = 0;
	while (true) {
		if (isValidPosition(beginX, beginY, validPositions)) break;
		int tempX = beginX;
		beginX = (tempX >= BOARD_SIZE - 1) ? 0 : beginX + 1;
		beginY = (tempX >= BOARD_SIZE - 1) ? beginY + 1 : beginY;
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
				nextX = (tempX >= BOARD_SIZE - 1) ? 0 : tempX + 1;
				nextY = (tempX >= BOARD_SIZE - 1) ? nextY + 1 : nextY;
				if (isValidPosition(nextX, nextY)) break;
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
	draw_grid(TOP_LEFT, TOP_LEFT, 9*BOX_LENGTH, BOX_LENGTH);
}

void getUserInput(int *xPos, int *yPos, int *inputNum) {

	// to be implemented
}

boolean isValidPosition(const int posX, const int posY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {
	return validPositions[posY][posX];
}

boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE]) {
	
	int i;
	int gridBaseX = (xPos / 3) * 3, gridBaseY = (yPos / 3) * 3;
	
	for (i = 0; i < 9; ++i) {
		
		// first horizontally
		if (board[yPos][i] == inputNum) return false;
		
		// then vertically
		if (board[i][xPos] == inputNum) return false;
		
		// finally the grid
		if (board[gridBaseY + (i / 3)][gridBaseX + (i % 3)] == inputNum) return false;
	}
	
	// if everything passes, return true
	return true;
}

void promptInvalid(const int xPos, const int yPos, const int inputNum) {

}

void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY) {

}

void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY) {

}

void draw_grid(double x, double y, double length, double box_length)
{
	int i,j;
	double k = x;
	for(i = 0; i < 10; i++)
	{
		if(i == 0|| i == 3|| i == 6||i == 9)
		{
			gfx_line(x-1,y, x-1,y+length);
			gfx_line(x+1,y, x+1,y+length);
			gfx_line(x-2,y, x-2,y+length);
			gfx_line(x+2,y, x+2,y+length);
		}
		gfx_line(x,y,x, y+length);
		x += box_length;
	}
	x = k;
	for(j = 0; j < 10; j++)
	{
		if(j == 0 || j == 3|| j == 6||j == 9)
		{
			gfx_line(x,y-1, x+length,y-1);
			gfx_line(x,y+1, x+length,y+1);
			gfx_line(x,y-2, x+length,y-2);
			gfx_line(x,y+2, x+length,y+2);
		}
		gfx_line(x,y,x+length, y);
		y += box_length;
	}
}