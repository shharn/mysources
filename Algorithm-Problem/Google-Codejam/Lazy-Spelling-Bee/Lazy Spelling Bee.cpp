// problem at : https://code.google.com/codejam/contest/5254486/dashboard#s=p0
#include <iostream>
#include <string>
#include <set>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-out.out"
#define fori0(i, s, e) for(int (i)=(s); (i)<(e); (i)++)
#define fori1(i, s, e) for(int (i)=(s); (i)<=(e); (i)++)
#define DIV 1000000007L
typedef long long ll;
int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int ct, T;
	std::cin >> T;
	fori1(ct, 1, T) {
		std::string W; 
		ll ans = 1;
		std::set<char> possibleMember;
		std::cin >> W;
		fori0(i, 0, W.length()) {
			possibleMember.clear();
			fori1(offset, -1, 1) {
				if (i + offset >= 0 && i+offset < W.length())
					possibleMember.insert(W[i + offset]);
			}
			ans *= possibleMember.size() % DIV;
			ans = ans % DIV;
		}
		std::cout << "Case #" << ct << ": " << ans << std::endl;
	}
	_fcloseall();
}
