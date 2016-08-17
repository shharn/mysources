// problem at : https://code.google.com/codejam/contest/4314486/dashboard#s=p2

#include <iostream>
#define FOR0(i, n) for(int (i)=0; (i) < (n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
#define MIN(a, b) ((a)>(b) ? (b) : (a))
#define INPUT_PATH "C-large-practice.in"
#define OUTPUT_PATH "C-large-practice-out.out"
using namespace std;

void solve(int J, int P, int S, int K) {
	FOR1(i, J) {
		int startk = i;
		FOR1(j, P) {
			for (int cnt = 0; cnt < MIN(S, K); cnt++, startk = (startk + 1) % (S+1)) {
				if (startk == 0) startk++;
				cout << i << " " << j << " " << startk << endl;
			}
		}
	}
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		int J, P, S, K;
		cin >> J >> P >> S >> K;
		cout << "Case #" << ct << ": " << J*P*MIN(S, K) << endl;
		solve(J, P, S, K);
	}
	return 0;
}
