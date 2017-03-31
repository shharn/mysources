// problem at : SRM711 Div2 Lv1
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

class SqureMaking {
public:
	int getMinimalPrice(int a, int b, int c, int d) {
		vector<int> v(4);
		v[0] = a;
		v[1] = b;
		v[2] = c;
		v[3] = d;

		int ans = 1 << 30;
		for (int i = 0; i < 4; i++) {
			int tmp = 0;
			for (int j = 0; j < 4; j++)
				tmp += abs(v[i] - v[j]);
			ans = min(ans, tmp);
		}
		return ans;
	}
};
