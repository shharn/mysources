// Problem at https://code.google.com/codejam/contest/6254486/dashboard#s=p3&a=3

#include <iostream>
#include <vector>
#define INPUT_PATH "D-large-practice.in"
#define OUTPUT_PATH "D-large-practice-out.out"
#define MIN(i, j) ((i)>(j)? (j) : (i))
using namespace std;

vector<long long> solve(long long K, long long C, long long S) {
	vector<long long> ans;
	ans.clear();

	for (long long i = 1; i <= K; i += C) {
		long long p = 1;
		for (long long j = 0; j < C; j++)
			p = (p - 1)*K + MIN(i + j, K);
		ans.push_back(p);
	}
	return ans;
}

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currT;
	cin >> T;
	for (currT = 1; currT <= T; currT++) {
		long long K, C, S;
		cout << "Case #" << currT << ": ";
		cin >> K >> C >> S;
		if (C*S < K) {
			cout << "IMPOSSIBLE" << endl;
			continue;
		}
		vector<long long> answer = solve(K, C, S);
		for (int i = 0; i < answer.size(); i++)
			cout << answer[i] << " ";
		cout << endl;
	}
	_fcloseall();
}
