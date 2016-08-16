// problem at : https://code.google.com/codejam/contest/4314486/dashboard#s=p1

#include <iostream>
#include <vector>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-practice-out.out"
#define MAX 50
#define FOR0(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i) <= (n); (i)++)
using namespace std;
typedef long long ll;
ll e[MAX], m, M;
int adj[MAX][MAX];

void dfs(int start, int b) {
	for (int i = start + 1; i < b; i++) {
		if(e[i] < 1)
			dfs(i, b);
		ll subm = e[start] + e[i];
		if (subm <= M) {
			e[start] += e[i];
			adj[start][i] = 1;
		}
		if (start == 0) m = e[start];
		if (m == M) break;
	}
}

void solve(int b, int ct) {
	cout << "Case #" << ct << ": ";
	if ((1ll << (b-2)) < M) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	e[b - 1] = 1;
	cout << "POSSIBLE" << endl;
	dfs(0, b);
	FOR0(i, b) {
		FOR0(j, b) cout << adj[i][j];
		cout << endl;
	}
	m = 0;
	memset(adj, 0, sizeof(adj));
	FOR0(i, b) e[i] = 0;
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		int b;
		cin >> b >> M;
		solve(b, ct);
	}
	_fcloseall();
	return 0;
}
