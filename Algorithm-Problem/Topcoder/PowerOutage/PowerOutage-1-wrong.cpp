#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <queue>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
typedef vector<vector<pair<int, int>>> vvii;
vvii adj;
bool list[51][51];
class PowerOutage {
public:
	int checkAndMinus(int tsum) {
		int res = tsum;
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int curnode = q.front(); q.pop();
			int nn = sz(adj[curnode]);
			fori0(i, 0, nn) {
				if (list[curnode][adj[curnode][i].first]) {
					res -= adj[curnode][i].second;
					q.push(adj[curnode][i].first);
					break;
				}
			}
		}
		return res;
	}

	int go(int curr, int time) {
		int n = sz(adj[curr]);
		if (n == 0) return time * 2;
		int ans = 0, m = 0, maxNode=adj[curr][0].first;
		fori0(i, 0, n) {
			int t = go(adj[curr][i].first, adj[curr][i].second);
			if (m < t) {
				m = t;
				maxNode = adj[curr][i].first;
			}
			ans += t;
		}
		list[curr][maxNode] = true;

		if (curr == 0)
			return checkAndMinus(ans);
		else
			return ans + time * 2;
	}

	int estimateTimeOut(vi from, vi to, vi t) {
		int n = sz(from);
		adj.resize(51);
		memset(list, 0, sizeof(list));
		fori0(i, 0, n)
			adj[from[i]].push_back(make_pair(to[i], t[i]));
		return go(0, 0);
	}
};
