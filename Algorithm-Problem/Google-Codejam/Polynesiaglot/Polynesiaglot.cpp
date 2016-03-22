#include <iostream>
#define INPUT_PATH "C-small-practice-2.in"
#define OUTPUT_PATH "C-small-practice-2-out.out"
#define CONSONENT	1
#define VOWEL		2
using namespace std;

unsigned long long search(int C, int V, int remain_L, int prev_char) {
	unsigned long long answer = 0;
	if (remain_L == 0) {
		if (prev_char == CONSONENT)
			return C;
		else
			return V;
	}
	else {
		if (prev_char == VOWEL) {
			answer += V * search(C, V, remain_L - 1, CONSONENT);
			answer += V * search(C, V, remain_L - 1, VOWEL);
			return answer;
		}
		else
			return C * search(C, V, remain_L - 1, VOWEL);
	}
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		unsigned long long answer = 0;
		int C, V, L;
		cin >> C >> V >> L;
		answer = V * search(C, V, L - 1, VOWEL);
		cout << "Case #" << currCase << ": " << (answer % (unsigned long long)1000000007) << endl;
	}
	_fcloseall();
	return 0;
}
