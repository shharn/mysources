// Problem at : https://code.google.com/codejam/contest/4304486/dashboard#s=p2

#include <iostream>
#include <algorithm>
#include <vector>
#define INPUT_PATH "C-large-practice.in"
#define OUTPUT_PATH "C-large-practice-out.out"
using namespace std;
int list[1001], d[1001];
bool used[1001];

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int currT, T;
	cin >> T;
	for (currT = 1; currT <= T; currT++) {
		cout << "Case #" << currT << ": ";
		memset(list, 0, sizeof(list));
		memset(d, 0, sizeof(d));

		int n, ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> list[i];

		for (int start = 1; start <= n; start++) {
			memset(used, 0, sizeof(used));
			int curr = start, tmp_ans = 0;
			while (!used[curr]){
				used[curr] = true;
				tmp_ans++;
				curr = list[curr];
			}
			if (curr == start)
				ans = max(ans, tmp_ans);
			if (ans == n)
				break;
		}
		
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (j != list[list[j]])
					d[list[j]] = max(d[list[j]], d[j] + 1);
			}
		}

		memset(used, 0, sizeof(used));
		if (ans != n) {
			int ans2 = 0;
			for (int i = 1; i <= n; i++) {
				if (i == list[list[i]] && !used[i]) {
					used[i] = used[list[i]] = true;
					ans2 += 2 + d[i] + d[list[i]];
					ans = max(ans, ans2);
				}
			}
		}
		cout << ans << endl;
	}
	_fcloseall();
	return 0;
}
