// problem at : https://code.google.com/codejam/contest/10224486/dashboard#s=p1

#include <iostream>
#include <algorithm>
#include <vector>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-out.out"
#define MAX 200
#define FOR0(i, n) for(int (i)=0; (i)<(n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
using namespace std;
typedef long double ld;
ld ans;
vector<ld> prob, whole;
ld prob2[MAX][MAX];

ld calcProb(int r, int c) {
  memset(prob2, 0, sizeof(prob2));
	prob2[0][0] = 1 - prob[0];
	prob2[1][0] = prob[0];
	FOR0(i, r+1) FOR0(j, c){
		prob2[i][j + 1] += (1-prob[j+1]) * prob2[i][j];
		if(i < r) prob2[i + 1][j + 1] += prob[j+1] * prob2[i][j];
	}
	return prob2[r][c];
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w" ,stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		whole.clear();
		ans = 0;
		int N, K;
		cin >> N >> K;
		FOR0(i, N) {
			ld tmp;
			cin >> tmp;
			whole.push_back(tmp);
		}
		std::sort(whole.begin(), whole.end());
		for (int i = 0; i <= K; i++) {
			prob.clear();
			for (int j = 0; j < i; j++) prob.push_back(whole[j]);
			for (int k = N - K + i; k < N; k++) prob.push_back(whole[k]);
			ans = max(ans, calcProb(K / 2, K-1));
		}
		cout.precision(16);
		cout << "Case #" << ct << ": " << ans << endl;
	}
	_fcloseall();
	return 0;
}
