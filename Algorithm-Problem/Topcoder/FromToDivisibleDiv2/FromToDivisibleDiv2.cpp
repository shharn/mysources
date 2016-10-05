// problem at : SRM 699 Div 2 Level Three
//              https://community.topcoder.com/stat?c=problem_statement&pm=14395&rd=16803
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it,c) for(auto (it)=(c).begin(); (it)!=(c).end();(it)++)
#define sz(c) ((int)c.size())
#define MAX 100000
typedef vector<int> vi;
typedef vector<bool> vb;
class FromToDivisibleDiv2 {
public:
	int shortest(int N, int S, int T, vi a, vi b) {
		vb visited(N + 1);
		vi dist(N + 1, -1);
		int m = sz(a);
		queue<int> q;
		dist[S] = 0;
		q.push(S);

		while (!q.empty()) {
			int t = q.front(); q.pop();
			fori0(i, 0, m) {
				if (t % a[i] == 0 && !visited[b[i]]) {
					visited[b[i]] = true;
					for (int j = b[i]; j <= N; j += b[i]) {
						if (dist[j] == -1) {
							dist[j] = dist[t] + 1;
							q.push(j);
						}
					}
				}
			}
		}
		return dist[T];
	}
};
