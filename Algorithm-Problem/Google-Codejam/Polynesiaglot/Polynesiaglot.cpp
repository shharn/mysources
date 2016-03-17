#include <iostream>
#define INPUT_PATH "C-small-practice-2.in"
#define OUTPUT_PATH "C-small-practice-2-out.out"
#define CONSONENT	1
#define VOWEL		2
using namespace std;

int answer = 0;
void search(int C, int V, int remain_L, int prev_char) {
	if (remain_L == 0)
		answer++;
	else {
		if (prev_char == VOWEL) {
			for (int i = 0; i < C; i++)
				search(C, V, remain_L - 1, CONSONENT);
			for (int i = 0; i < V; i++)
				search(C, V, remain_L - 1, VOWEL);
		}
		else {
			for (int i = 0; i < V; i++)
				search(C, V, remain_L - 1, VOWEL);
		}
	}
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		answer = 0;
		int C, V, L;
		cin >> C >> V >> L;
		search(C, V, L - 1, VOWEL);
		answer *= V;
		cout << "Case #" << currCase << ": " << answer % 1000000007 << endl;
	}
	_fcloseall();
	return 0;
}
