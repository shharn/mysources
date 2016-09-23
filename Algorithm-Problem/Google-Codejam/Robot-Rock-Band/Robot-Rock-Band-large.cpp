#include <iostream>
#include <unordered_map>
#define LARGE_INPUT "B-large-practice.in"
#define LARGE_OUTPUT "B-large-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)
#define forit(type, it, container) for(type::iterator (it) = container.begin(); (it) != container.end(); (it)++)
#define MAX(a, b) ((a) > (b) ? (a):(b))
typedef long long ll;
typedef std::unordered_map<ll, ll> mll;

int N;
mll m;
ll K;
ll members[4][1000];
void readInput() {
  std::cin >> N >> K;
  fori0(i, 0, 4) fori0(j, 0, N) std::cin >> members[i][j];
}

void solve(int ct) {
	ll ans = 0;
	m.clear();
	fori0(i, 0, N) fori0(j, 0, N) m[members[0][i] ^ members[1][j]]++;
	fori0(i, 0, N) fori0(j, 0, N) {
		ll tmp = members[2][i] ^ members[3][j] ^ K;
		if (m.find(tmp) != m.end())
			ans += m[tmp];
	}
	std::cout << "Case #" << ct << ": " << ans << std::endl;
}

void main() {
	freopen(LARGE_INPUT, "r", stdin);
	freopen(LARGE_OUTPUT, "w", stdout);
	int T;
	std::cin >> T;
	fori1(ct, 1, T) {
		large::readInput();
		large::solve(ct);
	}
	_fcloseall();
}
