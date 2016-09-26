// problem at : 2003 TCO Semifinals 4
//              (https://community.topcoder.com/stat?c=problem_statement&pm=1889&rd=4709)
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
using namespace std;
typedef long long ll;
class AvoidRoads {
public:
	ll road[101][101];
	map<string, vector<string>> badlist;
	string i2s(int a, int b) {
		char t[7] = { 0, };
		sprintf(t, "%d %d", a, b);
		return string(t);
	}

	bool check(int w, int h, int opw, int oph) {
		string tmp = i2s(w, h);
		string opnt = i2s(opw, oph);
		vector<string> list = badlist[tmp];
		fori0(i, 0, list.size())
			if (list[i] == opnt)
				return false;
		return true;
	}

	ll numWays(int width, int height, vector<string> bad) {
		memset(road, 0, sizeof(road));
		badlist.clear();
		fori0(i, 0, width) road[0][i] = 1;
		fori0(i, 0, height) road[i][0] = 1;
		fori0(i, 0, bad.size()) {
			string tmp = bad[i];
			int tokpos = tmp.find(" ", 0), cache;
			tokpos = tmp.find(" ", tokpos + 1);
			cache = tokpos + 1;
			string bad1 = tmp.substr(0, tokpos);
			string bad2 = tmp.substr(tokpos + 1, string::npos);
			badlist[bad1].push_back(bad2);
			badlist[bad2].push_back(bad1);
		}

		fori1(h, 0, height) fori1(w, 0, width) {
			ll val = 0;
			if (h == 0 && w == 0) continue;
			if (w - 1 >= 0 && check(w, h, w - 1, h))
				val += road[h][w-1];
			if (h - 1 >= 0 && check(w, h, w, h - 1))
				val += road[h - 1][w];
			road[h][w] = val;
		}
		return road[height][width];
	}
};
