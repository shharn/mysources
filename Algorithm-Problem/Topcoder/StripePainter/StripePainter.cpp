// problem at : SRM 150 Round 1
//              https://community.topcoder.com/stat?c=problem_statement&pm=1215&rd=4555
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
typedef map<int, int> mii;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)

class StripePainter {
public:
	string S;
	mii m;
	int go(int s, int e, char color) {
		if (s >= e) return 0;
		int code = s * 10000 + e * 100 + color;
		if (m.count(code)) return m[code];
		if (S[s] == color) return m[code] = go(s + 1, e, color);
		if (S[e - 1] == color) return m[code] = go(s, e - 1, color);
		int best = 1000;
		fori1(i, s + 1, e) {
			int cse = 1 + go(s, i, S[s]) + go(i, e, color);
			best = min(best, cse);
		}
	}

	int minStrokes(string s) {
		S = s;
		int len = s.length();
		m.clear();
		go(0, len, '?');
	}
};
