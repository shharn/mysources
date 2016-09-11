#include <iostream>
#include <vector>
#define INPUT_PATH "C-large-practice.in"
#define OUTPUT_PATH "C-large-out.out"
#define MAX 105
#define FOR1(i, s, n) for(int (i) = (s); (i)<(n); (i)++)
#define FOR2(i, s, n) for(int (i)=(s); (i)<=(n); (i)++)
typedef std::pair<int, int> pii;
namespace large {
	int lover[MAX];
	int initmove[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	int movepos[2][4][2] = { {{0, 1}, {-1, 0}, {0, -1}, {-1, 0}}, {{0, -1}, {-1, 0}, {0, 1}, {-1, 0}} };
	int dir[2][4] = { {1, 0, 3,2}, {3, 2, 1, 0} };
	// 0 : empty, 1 : '/', 2 : '\'
	int hedge[MAX][MAX];
	char ch[3] = "/\\";
	std::vector<pii> checker;
	
	void init() {
		freopen(INPUT_PATH, "r", stdin);
		//freopen(OUTPUT_PATH, "w", stdout);
	}

	void readInput(int R, int C) {
		FOR1(i, 0, R + C) {
			int a, b;
			std::cin >> a >> b;
			lover[a - 1] = b - 1;
			lover[b - 1] = a - 1;
		}
	}

	void print(int R, int C) {
		FOR1(i, 0, R) {
			FOR1(j, 0, C) std::cout << ch[hedge[i][j] - 1];
			std::cout << std::endl;
		}
	}

	pii getPos(int num, int R, int C) {
		if (num <= C)
			return std::make_pair(-1, num - 1);
		num -= C;
		if (num <= R)
			return std::make_pair(num - 1, C);
		num -= R;
		if (num <= C)
			return std::make_pair(R, C - num);
		num -= C;
		return std::make_pair(R - num, -1);
	}

	int getDir(pii pos, int R, int C) {
		if (pos.first < 0)
			return 2;
		if (pos.second >= C)
			return 3;
		if (pos.first >= R)
			return 0;
		return 1;
	}

	bool areMatch(pii a, pii b) {
		bool b1 = a.first == b.second;
		bool b2 = a.second == b.first;
		return b1 && b2;
	}

	int slash(int curdir) {
		if (curdir == 0)
			return 1;
		if (curdir == 1)
			return 0;
		if (curdir == 2)
			return 3;
		return 2;
	}

	char turnRight(int curdir) {
		if ((curdir + 1) % 4 == slash(curdir)) return '/';
		return '\\';
	}

	int go(pii& curr, int R, int C, int curdir) {
		if (curr.first == R || curr.second == C) {
			curr.first += initmove[curdir][0];
			curr.second += initmove[curdir][1];
			return curdir;
		}

		if (hedge[curr.first][curr.second] == 0)
			hedge[curr.first][curr.first] = turnRight(curdir);

		if (hedge[curr.first][curr.second] == 1) {
			curr.first += movepos[0][curdir][0];
			curr.second += movepos[0][curdir][1];
			return dir[0][curdir];
		}
		if (hedge[curr.first][curr.second] == 2) {
			curr.first += movepos[1][curdir][0];
			curr.second += movepos[1][curdir][1];
			return dir[1][curdir];
		}
	}

	bool make(int R, int C, pii p) {
		// p.first < p.second
		pii curr, dest;
		curr = getPos(p.second, R, C);
		int curdir = getDir(curr, R, C);
		dest = getPos(p.first, R, C);
		do {
			curdir = go(curr, R, C, curdir);
		} while (curr.first >= 0 && curr.first < R && curr.second >= 0 && curr.second < C);
		
		if (curr.first == dest.first && curr.second == dest.second)
			return true;
		else return false;
	}

	void solve(int R, int C) {
		FOR1(i, 0, (R + C) * 2) {
			if (!checker.empty() && areMatch(std::make_pair(i, lover[i]), checker.back())) {
				if (!make(R, C, checker.back()))
					break;
				checker.pop_back();
			}
			else
				checker.push_back(std::make_pair(i, lover[i]));
		}

		if (!checker.empty())
			std::cout << "IMPOSSIBLE";
		else
			print(R, C);
		checker.clear();
		memset(lover, 0, sizeof(lover));
		memset(hedge, 0, sizeof(hedge));
	}
}

