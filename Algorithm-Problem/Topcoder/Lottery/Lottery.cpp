#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<string> vs;
typedef long long ll;
typedef vector<pair<ll, string>> vpls;
class Lottery {
public:
	int s2i(string s) {
		stringstream ss(s);
		int n;
		ss >> n;
		return n;
	}

	void parse(string org, string& name, int& ch, int& bl, bool& sort, bool& uni) {
		stringstream ss(org);
		string s,u;
		getline(ss,name,':');
		ss >> ch >> bl >> s >> u;
		sort = s == "T" ? true : false;
		uni = u == "T" ? true : false;
	}

	ll TT(int ch, int bl) {
		ll dp[8][100] = { 0 };
		fori0(i, 0, ch) dp[0][i] = 1;
		fori0(b, 1, bl) fori0(i, 0, ch) fori0(j, i + 1, ch)
			dp[b][i] += dp[b - 1][j];
		ll res = 0;
		fori0(i, 0, ch) res += dp[bl - 1][i];
		return res;
	}

	ll FF(int ch, int bl) {
		ll n = 1;
		fori0(i, 0, bl) n *= ch;
		return n;
	}

	ll FT(int ch, int bl) {
		ll n = 1;
		fori0(i, 0, bl)
			n *= (ch - i);
		return n;
	}

	ll TF(int ch, int bl) {
		ll dp[8][100] = { 0 };
		fori0(i, 0, ch) dp[0][i] = 1;
		fori0(b, 1, bl)	fori0(i, 0, ch) fori0(j, i, ch)
					dp[b][i] += dp[b - 1][j];
		ll res = 0;
		fori0(i, 0, ch) res += dp[bl - 1][i];
		return res;
	}

	vs sortByOdds(vs s) {
		int n = sz(s);
		vpls l;
		fori0(i, 0, n) {
			string tmp = s[i];
			bool sort, uniq;
			int ch, bl;
			string name;
			parse(s[i], name, ch, bl, sort, uniq);
			ll cases;
			if (!sort && !uniq)
				cases = FF(ch, bl);
			else if (!sort && uniq)
				cases = FT(ch, bl);
			else if (sort && !uniq)
				cases = TF(ch, bl);
			else
				cases = TT(ch, bl);
			l.push_back(make_pair(cases, name));
		}
		sort(l.begin(), l.end());

		vs ans;
		fori0(i, 0, n) ans.push_back(l[i].second);
		return ans;
	}
};
