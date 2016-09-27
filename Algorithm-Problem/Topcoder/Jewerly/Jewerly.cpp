// problem at : 2003 TCCC Online Round 4
//              https://community.topcoder.com/stat?c=problem_statement&pm=1166&rd=4705
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
using namespace std;
typedef long long ll;
typedef vector<int> vi;
class Jewerly {
public:
	ll nck[31][31];
	int forward[31][30001], backward[31][30001];
	void makeCombi() {
		fori0(i, 0, 31) nck[0][i] = 0;
		fori0(i, 0, 31) nck[i][0] = 1;
		fori0(n, 1, 31) fori0(k, 1, 31)
			nck[n][k] = nck[n - 1][k - 1] + nck[n - 1][k];
	}

	void knapsack(vi v, int arr[31][30001]) {
		arr[0][0] = 1;
		fori1(i, 1, 30) arr[i][0] = 0;
		fori1(i, 1, 30) {
			int m = v[i - 1];
			fori1(vv, 1, 30000) {
				arr[i][vv] = arr[i - 1][vv];
				if (vv >= m) arr[i][vv] += arr[i - 1][vv - m];
			}
		}
	}

	ll howMany(vector<int> list) {
		vi copy(list);
		int n = (int)list.size();
		makeCombi();
		sort(copy.begin(), copy.end());
		knapsack(copy, forward);
		sort(copy.begin(), copy.end(), std::greater<int>());
		knapsack(copy, backward);
		ll ans = 0;
		fori0(i, 0, n) {
			int equal = i;
			while (equal < n && list[equal] == list[i]) equal++;
			int size = equal - i;
			fori1(j, 1, size) {
				int subsum = j * list[i];
				fori1(ss, subsum, 30000)
					ans += forward[i][ss - subsum] * backward[n - i - j][ss] * nck[size][j];
			}
			i = equal;
		}
		return ans;
	}
};
