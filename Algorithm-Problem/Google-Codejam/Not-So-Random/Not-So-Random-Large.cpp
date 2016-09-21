#include <iostream>
#include <vector>
#define INPUT_PATH "C-large-practice.in"
#define OUTPUT_PATH "C-large-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)
#define forit(type, it, container) for(type::iterator (it)=container.begin(); (it)!=container.end(); (it)++)

double prob[100000][2];
void solve(int N, int X, int K, double A, double B, double C, int ct) {
	memset(prob, 0, sizeof(prob));
	double ans = 0;
	fori0(bit, 0, 30) {
		prob[0][0] = 0.0;
		prob[0][1] = 1.0;
		int bk = (K >> bit) & 1;
		int bx = (X >> bit) & 1;
		fori1(i, 1, N) {
			prob[i][0] = prob[i - 1][bk & 0] * A + prob[i - 1][bk | 0] * B + prob[i - 1][bk ^ 0] * C;
			prob[i][1] = prob[i - 1][bk & 1] * A + prob[i - 1][bk | 1] * B + prob[i - 1][bk ^ 1] * C;
		}
		ans += (1 << bit)*prob[N][bx];
	}
	std::cout.precision(16);
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
		solve(N, X, K, A / 100, B / 100, C / 100, ct);
	}
	_fcloseall();
}
