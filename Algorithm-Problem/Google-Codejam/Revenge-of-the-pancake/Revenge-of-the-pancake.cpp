// Problem -> https://code.google.com/codejam/contest/6254486/dashboard#s=p1
#include <iostream>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-practice-out.out"
#define FLIP(x) ((x==HAPPY) ? (BLANK) : (HAPPY))
#define SWAP(x, y, tmp) (tmp)=(x); (x)=(y); (y)=(tmp)
#define MAX_SIZE 100
#define HAPPY 1
#define BLANK 0
using namespace std;
int minCount = 0;

void Flip(int *data, int from, int to) {
	int left = from, right = to;
	while (left < right) {
		data[left] = FLIP(data[left]);
		data[right] = FLIP(data[right]);
		int tmp;
		SWAP(data[left], data[right], tmp);
		left++;
		right--;
	}
	if (left == right)
		data[left] = FLIP(data[left]);
	minCount++;
}

int FindLeftmostHappyIndexFromTheRight(int *data, int length) {
	int pos = -1;
	for (int i = length - 1; i >= 0; i--) {
		if (data[i] != HAPPY) {
			pos = i;
			break;
		}
	}
	return pos;
}

void Round(int *data, int length) {
	if (data[0] == HAPPY) {
		int pos = 0;
		for (int i = 1; i < length; i++) {
			if (data[i] != HAPPY) {
				pos = i-1;
				break;
			}
		}
		Flip(data, 0, pos);
	}
	int to = FindLeftmostHappyIndexFromTheRight(data, length);
	Flip(data, 0, to);
}

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		minCount = 0;
		int pancakeStack[MAX_SIZE];
		char stack[MAX_SIZE + 1] = { 0 };
		cin >> stack;
		for (int i = 0; i < strlen(stack); i++)
			pancakeStack[i] = (stack[i] == '+' ? HAPPY : BLANK);
		while (FindLeftmostHappyIndexFromTheRight(pancakeStack, strlen(stack)) != -1) {
			Round(pancakeStack, strlen(stack));
		}
		cout << "Case #" << currCase << ": " << minCount << endl;
	}
	_fcloseall();
}
