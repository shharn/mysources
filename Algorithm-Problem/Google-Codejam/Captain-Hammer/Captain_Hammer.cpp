// https://code.google.com/codejam/contest/6234486/dashboard#s=p1

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#define INPUT_PATH "B-small-practice.in"
#define OUTPUT_PATH "B-small-practiec-out.out"
using namespace std;

void main() {
	int T, currCase;
	double pi = 3.1415926535897932384626433832795;
	double g = 9.8;
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		long double V, D;
		cin >> V >> D;
		V *= V;
		long double degree, value;
		value = g * D / V;
		degree = asin(value) * (180 / pi) / 2;
		printf("Case #%d: %.7lf\n", currCase, degree);
 	}
	_fcloseall();
}
