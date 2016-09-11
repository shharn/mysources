// problem at : https://code.google.com/codejam/contest/10224486/dashboard#s=p2

#include <iostream>
#include "C-small.cpp"
#include "C-large.cpp"
#define LARGE
#ifdef LARGE
#define ns large
#else
#define ns small
#endif
#define FOR0(i, n) for(int (i)=0; (i)<(n);(i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)

int main() {
	ns::init();
	int T;
	std::cin >> T;
	FOR1(ct, T) {
		int R, C;
		std::cin >> R >> C;
		ns::readInput(R, C);
		std::cout << "Case #" << ct << ":" << std::endl;
		ns::solve(R, C);
	}
}
