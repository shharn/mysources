#include <iostream>
#include <vector>
#include <stack>
#define FOR0(i, n) for(int (i)=0; (i)<(n);(i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
#define MAX 105
#define INPUT_PATH "C-small-practice.in"
#define OUTPUT_PATH "C-small-out.out"
namespace small {
	using namespace std;
	typedef pair<int, int> pii;
	vector<pii> lover;
	int a[MAX][MAX];
	char ch[2] = { '/', '\\' };
	bool found = false;
	// dir[0][][] -> slash, dir[1][][] -> back slash
	int dir[2][4][2] = { { { 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 } },
	{ { 0, 1 },{ -1, 0 },{ 0, -1 },{ 1, 0 } } };
	int fromd[2][4] = { { 1, 0, 3, 2 },{ 3,2,1,0 } };

	void init() {
		freopen(INPUT_PATH, "r", stdin);
		freopen(OUTPUT_PATH, "w", stdout);
	}

	void readInput(int R, int C) {
		FOR0(i, R + C) {
			int a, b;
			std::cin >> a >> b;
			lover.push_back(make_pair(a, b));
		}
	}

	pii getPos(int l, int R, int C) {
		int r, c;
		if (l <= C) {
			r = 0;
			c = l - 1;
		}
		else if (l <= R + C) {
			r = l - C - 1;
			c = C - 1;
		}
		else if (l <= R + 2 * C) {
			r = R - 1;
			c = C - (l - (R + C));
		}
		else {
			r = R - (l - (R + 2 * C));
			c = 0;
		}
		return make_pair(r, c);
	}

	void print(int r, int c) {
		FOR0(i, r) {
			FOR0(j, c) cout << ch[a[i][j]];
			cout << endl;
		}
	}

	bool check(int R, int C) {
		// check if the hedges are properly placed
		for (int i = 0; i < lover.size(); i++) {
			pii p = lover[i], start, dest;
			int from;
			bool possible = false;
			if (p.first <= C) from = 0; // from top
			else if (p.first <= R + C) from = 1; // from right
			else if (p.first <= R + 2 * C) from = 2; // from bottom
			else from = 3; // from left

			start = getPos(p.first, R, C);
			dest = getPos(p.second, R, C);
			if (p.second <= C) dest.first--;
			else if (p.second <= R + C) dest.second++;
			else if (p.second <= R + 2 * C) dest.first++;
			else dest.second--;
			do {
				int cr = start.first, cc = start.second;
				start.first += dir[a[cr][cc]][from][0];
				start.second += dir[a[cr][cc]][from][1];
				from = fromd[a[cr][cc]][from];
			} while (start.first > -1 && start.first < R
				&& start.second > -1 && start.second < C);

			if (!(start.first == dest.first && start.second == dest.second))
				return false;
		}
		return true;
	}

	void push_next(stack<pii>& s, int cr, int cc, int R, int C) {
		if (cr == R - 1 && cc == C - 1) return;
		int nr = cc < (C - 1) ? cr : cr + 1;
		int nc = (cc + 1) % C;
		a[nr][nc] = 0;
		s.push(make_pair(nr, nc));
	}

	void solve(int R, int C) {
		stack<pii> s;
		s.push(make_pair(0, 0));
		bool try_other = false;
		while (!s.empty()) {
			pii p = s.top();
			s.pop();
			if (try_other) {
				a[p.first][p.second]++;
				try_other = false;
			}

			if (p.first == R - 1 && p.second == C - 1) {
				if (check(R, C)) {
					found = true;
					break;
				}
				a[p.first][p.second]++;
			}

			if (a[p.first][p.second] != 2) {
				s.push(make_pair(p.first, p.second));
				push_next(s, p.first, p.second, R, C);
			}
			else
				try_other = true;
		}

		if (found)
			print(R, C);
		else
			cout << "IMPOSSIBLE" << endl;

		memset(a, 0, sizeof(a));
		found = false;
		lover.clear();
	}
}
