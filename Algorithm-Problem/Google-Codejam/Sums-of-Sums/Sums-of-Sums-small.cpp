#include <iostream>
#include <algorithm>
#include <vector>
#define SMALL_INPUT_PATH "D-small-practice.in"
#define SMALL_OUTPUT_PATH "D-small-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)
typedef long long ll;
typedef std::vector<ll> vll;
int org[1000];
vi list;

void partialSum() {
	fori0(i, 1, list.size())
		list[i] += list[i - 1];
}

void solve(int N, int Q, int ct) {
	std::cout << "Case #" << ct << ":\n";
	memset(org, 0, sizeof(org));
	list.clear();
	fori0(i, 0, N) std::cin >> org[i];
	fori0(i, 0, N) {
		list.push_back(org[i]);
		fori0(j, i + 1, N)
			list.push_back(list.back() + org[j]);
	}
	std::sort(list.begin(), list.end());
	partialSum();
	fori0(i, 0, Q) {
		int l, r;
		ll ans = 0;
		std::cin >> l >> r;
		ans = list[r - 1] - list[l - 1];
		std::cout << ans << std::endl;
	}
}

int main() {
  freopen(SMALL_INPUT_PATH, "r", stdin);
  freopen(SMALL_OUTPUT_PATH, "w", stdout);
  int T;
  std::cin >> T;
  fori1(ct, 1, T) {
	int N, Q;
		std::cin >> N >> Q;
		small::solve(N, Q, ct);
	}
	_fcloseall();
}
