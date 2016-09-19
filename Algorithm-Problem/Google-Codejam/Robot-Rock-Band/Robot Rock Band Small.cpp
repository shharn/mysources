// problem at : https://code.google.com/codejam/contest/5254486/dashboard#s=p1
#include <iostream>
#include <unordered_map>
#define INPUT_PATH "B-small-practice.in"
#define OUTPUT_PATH "B-small-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)

mll members[4];
int N;
ll K;

void readInput() {
	std::cin >> N >> K;
	fori0(i, 0, 4) fori0 (j, 0, N) {
		ll tmp;
		std::cin >> tmp;
		if (members[i][tmp])
			members[i][tmp]++;
		else members[i][tmp] = 1;
	}
}

void solve(int ct) {
	ll ans = 0;
	forit(mll, it1, members[0]) forit(mll, it2, members[1]) forit(mll, it3, members[2]) forit(mll, it4, members[3]){
		if ((it1->first ^ it2->first ^ it3->first ^ it4->first) == K)
			ans += it1->second * it2->second * it3->second * it4->second;
	}
	std::cout << "Case #" << ct << ": " << ans << std::endl;
	fori0(i, 0, 4)
		members[i].clear();
}

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	std::cin >> T;
	fori1(ct, 1, T) {
		int ans = 0;
		std::vector<int> members[4];
		std::cin >> N >> K;
		readInput();
		solve(ct);
	}
	_fcloseall();
}
