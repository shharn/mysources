// problem at : SRM 222 Round 1 - Division 1
//              https://community.topcoder.com/stat?c=problem_statement&pm=3450&rd=5868
#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it,c) for(auto (it)=(c).begin(); (it)!=(c).end();(it)++)
class GroceryBagger {
public:
	map<string, int> cache;
	int minimumBags(int strength, vector<string> type) {
		cache.clear();
		int ans = 0;
		int n = type.size();
		fori0(i, 0, n)
			cache[type[i]]++;

		forit(it, cache) {
			ans += it->second / strength;
			if (it->second % strength)
				ans++;
		}
		return ans;
	}
};
