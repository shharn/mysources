// problem at : https://code.google.com/codejam/contest/5254486/dashboard#s=p2
#include <iostream>
#include <vector>
#define INPUT_PATH "C-small-practice.in"
#define OUTPUT_PATH "C-small-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)
#define forit(type, it, container) for(type::iterator (it)=container.begin(); (it)!=container.end(); (it)++)
typedef std::vector<std::pair<int, double>> vpid;

void solve(int N, int X, int K, double A, double B, double C, int ct) {
	vpid c;
	c.push_back(std::make_pair(X&K, A));
	c.push_back(std::make_pair(X | K, B));
	c.push_back(std::make_pair(X^K, C));
	fori0(i, 1, N) {
		vpid nc;
		forit(vpid, it, c) {
			nc.push_back(std::make_pair(it->first&K, it->second*A)); 
			nc.push_back(std::make_pair(it->first | K, it->second*B));
			nc.push_back(std::make_pair(it->first^K, it->second*C));
		}
		c = nc;
	}
	double ans=0;
	forit(vpid, it, c)
		ans += it->first * it->second;
	std::cout.precision(25);
	std::cout << "Case #" << ct << ": " << ans << std::endl;
}

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	std::cin >> T;
	fori1(ct, 1, T) {
		int N, X, K;
		double A, B, C;
		std::cin >> N >> X >> K >> A >> B >> C;
		solve(N, X, K, A/100, B/100, C/100, ct);
	}
	_fcloseall();
}
