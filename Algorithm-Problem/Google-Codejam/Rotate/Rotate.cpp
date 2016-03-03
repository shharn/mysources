// Rotate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice.out"
#define NOTHING 0
#define BLUE 1
#define RED 2
#define BOTH BLUE | RED
#define NEITHER 0
char color[4] = { '.', 'B', 'R' };
enum Direction { UP, UP_RIGHT, RIGHT, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT, UP_LEFT };

void initializePosition(int position[50][50], int N) {
	int i, j;
	char color;
	for (i = 0; i < N; i++) 
		for (j = 0; j < N; j++) {
			scanf("%c", &color);
			switch (color) {
			case ' ':
				j--;
				break;
			case '\n':
				j--;
				break;
			case 'B':
				position[i][j] = BLUE;
				break;
			case 'R':
				position[i][j] = RED;
				break;
			}
		}
	scanf("%c", &color);
}

void printMembers(int position[50][50], int N) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf("%c ", color[position[i][j]]);
		printf("\n");
	}
}

void PushRight(int position[50], int N) {
	int col;
	int rightMostEmptyPos = N - 1;
	for (col = N-1; col >= 0; col--) {
		if(position[col] != NOTHING){
			if (rightMostEmptyPos != col) {
				position[rightMostEmptyPos] = position[col];
				position[col] = NOTHING;
				rightMostEmptyPos = rightMostEmptyPos - 1;
			}
			else {
				rightMostEmptyPos = rightMostEmptyPos - 1;
			}
		}
	}
}

void RotateAndGravity(int position[50][50], int N) {
	int row;
	for (row = 0; row < N; row++) {
		PushRight(position[row], N);
	}
}

int checkOneDirection(int position[50][50], int currRow, int currCol, int direction, 
	int N, int K) {
	int count = 0;
	int firstColor = NEITHER;
	firstColor = position[currRow][currCol];
	if (firstColor != NOTHING) {
		switch (direction) {
		case UP:
			for (count = 1; count < K; count++) {
				if (currRow - count < 0)
					return NOTHING;
				if (position[currRow - count][currCol] != firstColor)
					return NOTHING;
			}
			break;
		case UP_RIGHT:
			for (count = 1; count < K;	count++) {
				if ((currRow - count < 0) || (currCol + count >= N))
					return NOTHING;
				if (position[currRow - count][currCol + count] != firstColor)
					return NOTHING;
			}
			break;
		case RIGHT:
			for (count = 1; count < K; count++) {
				if (currCol + count >= N)
					return NOTHING;
				if (position[currRow][currCol + count] != firstColor)
					return NOTHING;
			}
			break;
		case RIGHT_DOWN:
			for (count = 1; count < K; count++) {
				if ((currRow + count >= N) || (currCol + count >= N))
					return NOTHING;
				if (position[currRow + count][currCol + count] != firstColor)
					return NOTHING;
			}
			break;
		case DOWN:
			for (count = 1; count < K; count++) {
				if (currRow + count >= N)
					return NOTHING;
				if (position[currRow + count][currCol] != firstColor)
					return NOTHING;
			}
			break;
		case LEFT_DOWN:
			for (count = 1; count < K; count++) {
				if ((currRow + count >= N) || (currCol - count < 0))
					return NOTHING;
				if (position[currRow + count][currCol] != firstColor)
					return NOTHING;
			}
			break;
		case LEFT:
			for (count = 1; count < K; count++) {
				if (currCol - count < 0)
					return NOTHING;
				if (position[currRow][currCol - count] != firstColor)
					return NOTHING;
			}
			break;
		case UP_LEFT:
			for (count = 1; count < K; count++) {
				if ((currRow - count < 0) || (currCol - count < 0))
					return NOTHING;
				if (position[currRow - count][currCol - count] != firstColor)
					return NOTHING;
			}
			break;
		}
		return firstColor;
	}
	return NOTHING;
}

int check8Direction(int position[50][50], int currRow, int currCol, int N, int K) {
	int direction;
	int whichColor = 0;
	for (direction = UP; direction < 8; direction++)
		whichColor |= checkOneDirection(position, currRow, currCol, direction, N, K);
	return whichColor;
}

int Check_In_A_Row(int position[50][50], int N, int K) {
	bool findBlue = false, findRed = false;
	int row, col;
	for (row = N - 1; row >= 0; row--) {
		for (col = N - 1; col >= 0; col--) {
			int color = check8Direction(position, row, col, N, K);
			if ((color & BLUE) == BLUE)
				findBlue = true;
			else if ((color & RED) == RED)
				findRed = true;
		}
	}
	if (findBlue && findRed)
		return BOTH;
	else if (findBlue)
		return BLUE;
	else if (findRed)
		return RED;
	else
		return NEITHER;
}

int main()
{
	char selection[4][8] = { "NEITHER", "BLUE", "RED", "BOTH" };
	int position[50][50] = { 0 };
	int T, currCase = 1;
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	scanf("%d", &T);
	for (currCase = 1; currCase <= T; currCase++) {
		memset(position, 0, sizeof(position));
		int whichCase = 0;
		int N, K;
		scanf("%d %d", &N, &K);
		initializePosition(position, N);
		RotateAndGravity(position, N);
		whichCase = Check_In_A_Row(position, N, K);
		printf("Case #%d: %s\n", currCase, selection[whichCase]);
	}
	_fcloseall();
    return 0;
}

