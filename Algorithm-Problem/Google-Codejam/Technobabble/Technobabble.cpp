// problem at : https://code.google.com/codejam/contest/11254486/dashboard#s=p2

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
#define INPUT_PATH "C-large-practice.in"
#define OUTPUT_PATH "C-large-practice-out.out"
#define FOR0(i, n) for(int (i) = 0; (i) < (n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i) <= (n); (i)++)
#define MAX 1000
map<string, int> a, b;
int parent[MAX], used[MAX], memo;
vector<int> edges[MAX];

bool findMEC(int p) {
	if (p == -1) return true;
	if (used[p] == memo) return false;
	used[p] = memo;
	for (int c : edges[p]) {
		if (findMEC(parent[c])) {
			parent[c] = p;
			return true;
		}
	}
	return false;
}

int getMEC() {
	int na = a.size();
	int nb = b.size();
	int matching = 0;
	memo = 0;
	FOR0(i, nb) parent[i] = -1;
	FOR0(i, na) {
		memo++;
		matching += findMEC(i);
	}
	return na + nb - matching;
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		int N, mec;
		a.clear(); b.clear();
		cin >> N;
		FOR0(i, N) {
			string ta, tb;
			cin >> ta >> tb;
			if (!a.count(ta)) {
				int pos = a.size();
				a[ta] = pos;
			}
			if (!b.count(tb)) {
				int pos = b.size();
				b[tb] = pos;
			}
			edges[a[ta]].push_back(b[tb]);
		}
		mec = getMEC();
		int ans = N - mec;
		cout << "Case #" << ct << ": " << ans << endl;

		FOR0(i, a.size()) edges[i].clear();
		memset(used, 0, sizeof(used));
	}
	_fcloseall();
	return 0;
}
