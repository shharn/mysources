// problem at : https://code.google.com/codejam/contest/11254486/dashboard#s=p1

#include <iostream>
#include <string>
#include <stdlib.h>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-practice-out.out"
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
#define FOR0(i, n) for(int (i)=0; (i)<(n); (i)++)
#define LL_MAX 1ll << 61
typedef long long ll;
using namespace std;
ll diff;
string ansC, ansJ;

ll strToInt(string a) {
	ll z = 0, n = a.length(), f = 1;
	FOR0(i, n){
		z += f * (a[n - i - 1] - '0');
		f *= 10;
	}
	return z;
}

void check(string a, string b) {
	ll aaa = strToInt(a);
	ll bbb = strToInt(b);
	if (diff > abs(aaa - bbb)) {
		diff = abs(aaa - bbb);
		ansC = a; ansJ = b;
	}
	else if (diff == abs(aaa - bbb)) {
		ll c = strToInt(ansC), j = strToInt(ansJ);
		if ((aaa < c) || (bbb < j)) {
			ansC = a; ansJ = b;
		}
	}
}

void make(string a, string b, int i, int n) {
	int aa = a[i - 1] - '0';
	int bb = b[i - 1] - '0';
	for (int x = i; x < n; x++) {
		if(a[x] == '?') a[x] = (aa > bb) ? '0' : '9';
		if(b[x] == '?') b[x] = (aa > bb) ? '9' : '0';
	}
	check(a, b);
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int currT, T;
	cin >> T;
	FOR1(currT, T) {
		diff = LL_MAX; ansC.clear(); ansJ.clear();
		string C, J;
		cin >> C >> J;
		int n = C.length();
		bool done = false;
		FOR0(i, n) {
			if (C[i] != '?' && J[i] != '?') {
				int a = C[i] - '0';
				int b = J[i] - '0';
				if (a != b) {
					make(C, J, i + 1, n);
					done = true;
					break;
				}
			}
			else if (C[i] == '?' && J[i] == '?') {
				C[i] = '0'; J[i] = '1';
				make(C, J, i+1, n);
				C[i] = '1'; J[i] = '0';
				make(C, J, i + 1, n);
				C[i] = J[i] = '0';
			}
			else {
				char m;
				if (C[i] == '?') {
					m = J[i];
					if ((J[i] - '0') > 0) {
						C[i] = J[i] - 1;
						make(C, J, i + 1, n);
					}
					if ((J[i] - '0') < 9) {
						C[i] = J[i] + 1;
						make(C, J, i + 1, n);
					}
					C[i] = m;
				}
				else {
					m = C[i];
					if((C[i] - '0') > 0){
						J[i] = C[i] - 1;
						make(C, J, i + 1, n);
					}
					if ((C[i] - '0') < 9) {
						J[i] = C[i] + 1;
						make(C, J, i + 1, n);
					}
					J[i] = m;
				}
			}
		}
		if(!done)
			check(C, J);
		cout << "Case #" << currT << ": " << ansC << " " << ansJ << endl;
	}
	_fcloseall();
	return 0;
}
