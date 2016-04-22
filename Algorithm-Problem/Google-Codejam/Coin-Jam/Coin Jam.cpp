// Problem : https://code.google.com/codejam/contest/6254486/dashboard#s=p2&a=2

#include <iostream>
#include <vector>
#define INPUT_PATH "C-small-practice.in"
#define OUTPUT_PATH "C-small-practice-out2.out"
#define MAX_LENG 16
using namespace std;

long long convertBinaryToBase(int x, int base) {
	// Some languages have built-ins which make this easy.
	// For example, in Python, we can avoid recursion and
	// just return int(bin(x)[2:], base)
	if (x == 0)
		return 0;
	return base * convertBinaryToBase(x / 2, base) + (x % 2);
}

long long findFactor(long long k) {
	for (long long d = 2; d * d <= k; d++)
		if (k % d == 0)
			return d;
	return 0;
}

void printCoins(int N, int X) {
	for (long long i = (1 << N - 1) + 1; X > 0; i += 2) {
		vector<long long> factors;
		for (int base = 2; base <= 10; base++) {
			long long x = convertBinaryToBase(i, base);
			long long factor = findFactor(x);
			if (!factor)
				break;
			factors.push_back(factor);
		}
		if (factors.size() < 9)
			continue;

		cout << convertBinaryToBase(i, 10);
		for (long long factor : factors)
			cout << " " << factor;
		cout << endl;
		X -= 1;
	}
}

void main() {
	//freopen(INPUT_PATH, "r", stdin);
	//freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		cout << "Case #" << currCase << ":" << endl;
		int N, J;
		cin >> N >> J;
		printCoins(N, J);
	}
	// _fcloseall();
}
