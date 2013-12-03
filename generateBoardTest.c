#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 9

typedef enum { false = 0, true } boolean;

boolean debug = true;

boolean checkGrid(int x, int y, const int inputNum, const int board[BOARD_SIZE][BOARD_SIZE]) {

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


boolean isValidPosition(const int posX, const int posY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]) {

	return validPositions[posY][posX];
}

void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
	int i = 0, j = 0;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

boolean solveBoardSub(int board[BOARD_SIZE][BOARD_SIZE], int curX, int curY, const boolean validPositions[BOARD_SIZE][BOARD_SIZE]);

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
				printf("%d at %d %d\n", num, nextX, nextY);
				printBoard(solutionBoard);

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
		else printf("failed\n");
	}

}

int main() {

	// generate new random seed
	srand(time(NULL));

	int solutionBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int puzzleBoard[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boolean validPositions[BOARD_SIZE][BOARD_SIZE] = { 0 };

	generateBoard(solutionBoard, puzzleBoard, validPositions);

	printBoard(solutionBoard);

	return 0;
}