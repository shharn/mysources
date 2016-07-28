// Problem at : https://code.google.com/codejam/contest/11254486/dashboard

#include <iostream>
#include <vector>
#include <string>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice-out.out"
using namespace std;
typedef vector<string>::iterator vi;
int n[10], b[26];
int ct[26] = { -1, -1, -1, -1, -1, 5, -1, -1, 9, -1, -1, -1, -1, -1, 1, -1, -1, 3, 7, 8, 4, -1, 2, 6, -1, 0 };
char a[11] = { 'U', 'W', 'X', 'Z', 'F', 'S', 'R', 'T', 'I', 'O' };
vector<string> c = { "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" };

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int currT, T;
	cin >> T;
	for (currT = 1; currT <= T; currT++) {
		string tmp;
		cin >> tmp;
		memset(n, 0, sizeof(n));
		for (int i = 0; i < tmp.length(); i++)
			b[tmp[i] - 'A']++;

		for (int i = 0; i < 10; i++) {
			int count = b[a[i] - 'A'];
			if (count > 0) {
				n[ct[a[i] - 'A']] = count;
				for (int j = 0; j < c[ct[a[i] - 'A']].length(); j++)
					b[c[ct[a[i] - 'A']][j] - 'A'] -= count;
			}
		}

		cout << "Case #" << currT << ": ";
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < n[i]; j++)
				cout << i;
		cout << endl;
	}
	_fcloseall();
	return 0;
}
