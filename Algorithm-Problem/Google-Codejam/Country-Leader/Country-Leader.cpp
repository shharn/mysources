// problem at : https://code.google.com/codejam/contest/11274486/dashboard
#include <iostream>
#include <string>
#include <vector>
#include <map>
#define SMALL_INPUT "A-small-practice.in"
#define SMALL_OUTPUT "A-small-out.out"
#define LARGE_INPUT "A-large-practice.in"
#define LARGE_OUTPUT "A-large-out.out"
#define fori0(i, s, e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i, s, e) for(int (i)=(s);(i)<=(e);(i)++)

void solve(int ct, int N) {
	std::string candidate;
	int candidate_size = 0;
	fori0(i, 0, N) {
		std::map<char, int> checker;
		std::string tmp;
		std::cin >> tmp;
		fori0(j, 0, tmp.length())
			checker[tmp[j]]++;
		if (candidate_size < checker.size()) {
			candidate = tmp;
			candidate_size = checker.size();
		}
		if (candidate_size == checker.size() && candidate > tmp)
			candidate = tmp;
	}
	std::cout << "Case #" << ct << ": " << candidate << std::endl;
}

void main() {
	freopen(LARGE_INPUT, "r", stdin);
	freopen(LARGE_OUTPUT, "w", stdout);
	int T;
	std::cin >> T;
	fori1(ct, 1, T) {
		int N;
		std::cin >> N;
		solve(ct, N);
	}
	_fcloseall();
}
