// question from -> https://code.google.com/codejam/contest/4304486/dashboard#s=p1&a=1

#include <iostream>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-practice-out.out"
using namespace std;

bool flag[2501];
void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currT;
	cin >> T;
	for (currT = 1; currT <= T; currT++) {
		memset(flag, 0, sizeof(flag));
		int N;
		cin >> N;
		for (int i = 0; i < 2 * N - 1; i++) {
			for (int j = 0; j < N; j++) {
				int temp;
				cin >> temp;
				flag[temp] = !flag[temp];
			}
		}
		cout << "Case #" << currT << ": ";
		for (int i = 0; i < 2501; i++) if (flag[i]) cout << i << " ";
		cout << endl;
	}
	_fcloseall();
}
