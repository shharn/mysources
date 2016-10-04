// problem at : SRM 699 Div 2
//              https://community.topcoder.com/stat?c=problem_statement&pm=14397
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it, c) for(auto (it)=(c).begin();(it)!=(c).end();(it)++)
typedef vector<int> vi;
typedef long long ll;
class LastDigit {
public:
	ll calc(ll n) {
		ll power = 1, s = 0;
		fori0(i, 0, 18) {
			s += n / power;
			power *= 10;
		}
		return s;
	}

	ll findX(ll S) {
		ll low = 0, high = S;
		while (low <= high) {
			ll mid = (low + high) >> 1;
			ll t = calc(mid);
			if (t > S)
				high = mid-1;
			else if (t < S)
				low = mid+1;
			else
				return mid;
		}
		return -1;
	}
};
