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
#define CHAR_SIZE 35

// macro version for isValidPosition: for possible future optimization
// given a position (x, y) on the board, this macro returns if the position is available for the user to change, i.e. it's not one of the computer-generated numbers
#define isValidPosition(__VPPosX__, __VPPosY__) validPositions[__VPPosY__][__VPPosX__]

// notice that the board is arranged as board[y][x]

// typedef for boolean
typedef enum { false = 0, true } boolean;

// typedef for hardness
typedef enum { easy, medium, hard } hardness;

/*
   ==========================================================
   function prototypes to be implemented are all written here
   ==========================================================
*/

// show game menu and get user input
void showGameMenu(int *userChoice, hardness *h);

// displays instructions, and returns as the user prompts
void showInstructions();

/*
   ==========================================
   completed function prototypes are all here
   ==========================================
*/

// sets up graphics window
void openGraphics();

// sets up a new game of sudoku, and returns when the current game ends
void startGame(hardness h);

// generates the solution board, and removes an appropriate number of numbers to generate the puzzle board, and saves the valid positions in the valid positions board
void generateBoard(int solutionBoard[BOARD_SIZE][BOARD_SIZE], int puzzleBoard[BOARD_SIZE][BOARD_SIZE], boolean validPositions[BOARD_SIZE][BOARD_SIZE], hardness h);

// given a position and a move on the board, this function returns if the move is valid according to Sudoku rules
boolean isValidMove(const int xPos, const int yPos, const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE])

// gets the user input: an index on board, and an input number
void getUserInput(int *xIndex, int *yIndex, int *inputNum);

// checks if the game ends
boolean isGameEnd(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE]);

// solves a given board with backtracking
// note: they are not debugged
boolean solveBoard(int board[BOARD_SIZE][BOARD_SIZE], const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);
boolean solveBoardSub(int board[BOARD_SIZE][BOARD_SIZE], int curX, int curY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

// functions for drawing the game grid on screen
void draw_grid(double x, double y, double length, double box_length);
void draw_rect(int x, int y, double width, double height);

// function that draws buttons inside the actual game view
void drawGameButtons();

// helper function to translate from screen location to board index
void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY);

// helper function to translate from board index to screen location
void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY);

void drawGameMenu();

void printBoard(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE], const int validPositions[BOARD_SIZE][BOARD_SIZE]) {

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
		hardness h;
		showGameMenu(&userChoice, &h);

		switch (userChoice) {

			// if user chooses to start game
			case 1:
				startGame(h);
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

void openGraphics() {
	gfx_open(WINDOW_W, WINDOW_H, "Simple Sudoku");
	dc_updateHeight(CHAR_SIZE);
}

void startGame(hardness h) {

	// variable declaration for game board
	int solutionBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int puzzleBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean validPositions[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean userGivesUp = false;

	generateBoard(solutionBoard, puzzleBoard, validPositions, h);

	while (!isGameEnd(puzzleBoard) && !userGivesUp) {
		printBoard(puzzleBoard);

		int xPos, yPos, inputNum;
		getUserInput(&xPos, &yPos, &inputNum, &userGivesUp);

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

	// after solving the board, we update the puzzle board to be filled
	// we update valid positions to be all "open", since we'll keep the appropriate numbers
	int y, x;
	for (y = 0; y < BOARD_SIZE; y++) {
		for (x = 0; x < BOARD_SIZE; x++) {
			puzzleBoard[y][x] = solutionBoard[y][x];
			validPositions[y][x] = true;
		}
	}

	// then we dig holes in the boards
	// easy boards have 45 numbers, medium boards have 40, and hard ones have 35
	int numsToKeep = (h == easy) ? 45 : (h == medium) ? 40 : 35;

	while (numsToKeep > 0) {
		int nextX = rand() % BOARD_SIZE;
		int nextY = rand() % BOARD_SIZE;

		if (isValidPosition(nextX, nextY)) {
			// if the position is open, mark it as "invalid"
			validPositions[nextY][nextX] = false;
			
			// update numbers left
			numsToKeep--;
		}
	}

	// dig the actual holes
	for (y = 0; y < BOARD_SIZE; y++) {
		for (x = 0; x < BOARD_SIZE; x++) {
			if (isValidPosition(x, y))
				puzzleBoard[y][x] = 0;
		}
	}
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
			if (puzzleBoard[i][j] == 0) break;
		}
	}
}

void printBoard(const int puzzleBoard[BOARD_SIZE][BOARD_SIZE], const int validPositions[BOARD_SIZE][BOARD_SIZE]) {
	
	// to be implemented
	draw_grid(TOP_LEFT, TOP_LEFT, 9*BOX_LENGTH, BOX_LENGTH);
	drawGameButtons();

	int x, y;
	for (x = 0; x < BOARD_SIZE; x++) {
		for (y = 0; y < BOARD_SIZE; y++) {
			// if puzzleboard[y][x] != 0
			// if validPositions[y][x] == true, it's one of the numbers that the user fills in
			// print the number at the appropriate position

			// if validPositions[y][x] == false, it's one of the numbers that the program generated
			// print the number at the appropriate position

		}
	}
}

void getUserInput(int *xIndex, int *yIndex, int *inputNum) {

	boolean selectedGrid = false, inputedNumber = false;

	// while the user has not finished the input process
	while (!(selectedGrid && inputedNumber)) {
		char event = gfx_wait();
		int clickX = gfx_xpos();
		int clickY = gfx_ypos();

		switch (event) {
			case 1:
			screenToIndex(clickX, clickY, xIndex, yIndex);
			if (*xIndex != -1 && *yIndex != -1) {
				selectedGrid = true;
				// possibly highlight the grid?
			}
			break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			if (selectedGrid) {
				*inputNum = event - '0';
				inputedNumber = true;
			}
			break;

			default:
			// default case here just in case something comes up later on
			break;
		}
	}
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

void draw_rect(int x, int y, double width, double height)
{
	gfx_line(x,y, x+width, y);
	gfx_line(x+width, y, x+width, y+height);
	gfx_line(x+width, y+height, x, y+height);
	gfx_line(x, y+height, x, y);
}

void drawGameButtons()
{
	draw_rect(100, WINDOW_HEIGHT-100, 150, 50);
	draw_rect(350, WINDOW_HEIGHT-100, 150, 50);
}

void indexToScreen(const int indexX, const int indexY, int *screenX, int *screenY) {
	*screenX = TOP_LEFT + 19.28 + indexX * BOX_LENGTH;
	*screenY = TOP_LEFT + 10.28 + indexY * BOX_LENGTH;
}

void screenToIndex(const int screenX, const int screenY, int *indexX, int *indexY) {
	*indexX = (int)floor((screenX - 19.28) / BOX_LENGTH);
	*indexY = (int)floor((screenY - 10.28) / BOX_LENGTH);
	if ((*indexX) < 0 || (*indexX) > 8) *indexX = -1;
	if ((*indexY) < 0 || (*indexY) > 8) *indexY = -1;
}

void showGameMenu(int *userChoice, hardness *h) {
	drawGameMenu();

	
}

void drawGameMenu() {
	draw_rect(50,50, 500, 100); //"SUDOKU"
	draw_rect(150, 200, 300, 100); //"PRESS P TO PLAY"
	draw_rect(150, 350, 300, 100); //"PRESS I FOR INSTRUCTIONS"
	draw_rect(150, 500, 300, 100); //"PRESS Q TO QUIT"
	//draw_rect(0, height-50, width, 50); // Names
	gfx_color(255,0,255);
	dc_updateHeight(75);
	dc_drawString(172,60,"SUDOKU");
	gfx_color(255,128,0);
	dc_drawString(174,62,"SUDOKU");
	gfx_color(255,255,0);
	dc_drawString(176,64,"SUDOKU");

	dc_updateHeight(40);
	gfx_color(51,255,255);
	dc_drawString(257,230,"PLAY");
	dc_drawString(257,530,"QUIT");
	dc_drawString(158, 380,"INSTRUCTIONS");
	
	gfx_color(255,255,255);
	dc_updateHeight(25);
	dc_drawString(125,645,"SHUYANG LI AND ADAM GOINS");
}