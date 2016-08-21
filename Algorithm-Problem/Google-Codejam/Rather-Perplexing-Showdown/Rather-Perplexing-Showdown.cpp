// problem at : https://code.google.com/codejam/contest/10224486/dashboard

#include <iostream>
#include <string>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice-out.out"
#define FOR0(i, n) for(int (i)=0; (i) < (n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
using namespace std;
string str[3];

string concat(string a, string b) {
	return (a > b) ? b + a : a + b;
}

void make(int N) {
	str[0] = "R";
	str[1] = "P";
	str[2] = "S";

	FOR0(i, N) {
		string tr = concat(str[0], str[2]);
		string tp = concat(str[1], str[0]);
		string ts = concat(str[2], str[1]);
		str[0] = tr;
		str[1] = tp;
		str[2] = ts;
	}
}

bool isPossible(int N, int R, int P, int S) {
	if (P == R && (P % 2) == 1 && (R % 2) == 1) {
		if (N % 2 == 1) return S == P - 1;
		else return S == P + 1;
	}
	else if (P == S && (P % 2) == 1 && (S % 2) == 1) {
		if (N % 2 == 1) return R == P - 1;
		else return R == P + 1;
	}
	else if (R == S && (R % 2) == 1 && (S % 2) == 1) {
		if (N % 2 == 1) return P == R - 1;
		else return P == R + 1;
	}
	return false;
}

void solve(int N, int R, int P, int S, int ct) {
	cout << "Case #" << ct << ": ";
	if (!isPossible(N, R, P, S)) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	make(N);
	int which, tp, tr, ts;
	FOR0(a, 3) {
		tp = tr = ts = 0;
		which = a;
		FOR0(i, (1<<N)) {
			if (str[a][i] == 'P') tp++;
			if (str[a][i] == 'R') tr++;
			if (str[a][i] == 'S') ts++;
		}
		if (P == tp && R == tr && S == ts)
			break;
	}

	FOR0(i, (1 << N))
		cout << str[which][i];
	cout << endl;
	FOR0(i, 3) str[i].clear();
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		int N, P, R, S;
		cin >> N >> R >> P >> S;
		solve(N, R, P, S, ct);
	}
	_fcloseall();
	return 0;
}
