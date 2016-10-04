// problem at : SRM 169 Div 1
//              https://community.topcoder.com/stat?c=problem_statement&pm=1957&rd=4650
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it, c) for(auto (it)=(c).begin();(it)!=(c).end();(it)++)
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<string> vs;
class GoldMine {
public:
	vd val[50], eval[50];
	int size;
	double s2d(const char *s) {
		double tmp;
		sscanf(s, "%lf", &tmp);
		return tmp / 100;
	}

	void getEval() {
		fori0(i, 0, size) fori1(j, 1, 6) {
				double tmp = 0;
				fori1(k, 0, 6) {
					if (j > k)
						tmp += val[i][k] * (k * 50 - (j - k) * 20);
					else if (j == k)
						tmp += val[i][k] * j * 50;
					else
						tmp += val[i][k] * j * 60;
				}
				eval[i].push_back(tmp);
		}
		fori0(i, 0, size) {
			double cache1 = eval[i][0], cache2;
			fori0(j, 1, 6) {
				cache2 = eval[i][j];
				eval[i][j] = eval[i][j] - cache1;
				cache1 = cache2;
			}
		}
	}

	vi getAllocation(vs m, int N) {
		size = m.size();
		fori0(i, 0, N) {
			val[i].clear();
			eval[i].clear();
		}

		fori0(i, 0, size) fori0(j, 0, 7)
				val[i].push_back(s2d(m[i].substr(j * 5, 3).c_str()));
		getEval();
		// for each mine
		int numSelected[50] = { 0 };
		int curridx[50] = { 0 };
		fori0(n, 0, N) {
			double max = -100000;
			int selIdx = 0;
			fori0(i, 0, size) { // iterate mines
				if (curridx[i] < 6 && max < eval[i][curridx[i]]) {
					max = eval[i][curridx[i]];
					selIdx = i;
				}
			}
			numSelected[selIdx]++;
			curridx[selIdx]++;
		}
		vi ans;
		fori0(i, 0, size)
			ans.push_back(numSelected[i]);
		return ans;
	}
};
