// problem at : SRM 698 Div2 Level Two
//              https://community.topcoder.com/stat?c=problem_statement&pm=14390

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#define MAX 50
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())

class RepeatStringEasy {
public:
	int maximalLength(string s) {
		int ans = 0;
		fori0(i, 0, sz(s))
			ans = max(ans, go(s.substr(0, i), s.substr(i)));
		return ans;
	}

	int go(string a, string b) {
		int dp[MAX + 1][MAX + 1] = { 0 };
		int n = sz(a);
		int m = sz(b);
		fori0(i, 0, n) fori0(j, 0, m) {
			if (a[i] == b[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
			else dp[i + 1][j + 1] = max(dp[i + 1][j], dp[i][j + 1]);
		}
		return dp[n][m] * 2;
	}
};
