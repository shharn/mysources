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
		ll s = 0, factor = 1, d;
		int size = 0;
		while (true) {
			if (n / factor != 0) {
				size++;
				factor *= 10;
			}
			else break;
		}
		size--;
		factor /= 10;
		ll memo = factor;
		fori1(i, 0, size) {
			ll nn = n;
			ll a = memo;
			ll local = 0;
			fori1(j, 0, i) {
				local += nn / a;
				nn = nn % a;
				a /= 10;
			}
			s += local*factor;
			factor /= 10;
		}
		return s;
	}

	ll findX(ll S) {
		ll low = 0, high = 1e18;
		while (low < high) {
			ll mid = (low + high) / 2;
			ll t = calc(mid);
			if (t > S)
				high = mid;
			else if (t < S)
				low = mid;
			else
				return mid;
		}
		return -1;
	}
};
