// problem at : https://code.google.com/codejam/contest/5254486/dashboard#s=p1
#include <iostream>
#include <vector>
#define INPUT_PATH "B-small-practice.in"
#define OUTPUT_PATH "B-small-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	std::cin >> T;
	fori1(ct, 1, T) {
		int N, K, ans = 0;
		std::vector<int> members[4];
		std::cin >> N >> K;
		fori0(i, 0, 4) {
			fori0(j, 0, N) {
				int tmp;
				std::cin >> tmp;
				members[i].push_back(tmp);
			}
		}

		fori0(i, 0, N) fori0(j, 0, N) fori0(k, 0, N) fori0(l, 0, N) {
			if ((members[0][i] ^ members[1][j] ^ members[2][k] ^ members[3][l]) == K)
				ans++;
		}
		std::cout << "Case #" << ct << ": " << ans << std::endl;
		fori0(i, 0, 4)
			members[i].clear();
	}
	_fcloseall();
}
