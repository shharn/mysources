#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<string> vs;
class BinaryCode {
public:
	vs decode(string q) {
		string p1, p2;
		vs ans;
		ans.clear();
		int n = q.length();
		p1.append("0"); p2.append("1");
		fori0(i, 0, n - 1) {
			stringstream ss;
			char c1 = q[i] - p1[i] + '0';
			if (i > 0) c1 = c1- p1[i - 1] + '0';
			if (c1 > '1') {
				p1 = "NONE";
				break;
			}
			ss << c1; 
			p1.append(ss.str());
		}
		fori0(i, 0, n - 1) {
			stringstream ss;
			char c1 = q[i] - p2[i] + '0';
			if (i > 0) c1 = c1 - p2[i - 1] + '0';
			if (c1>'1') {
				p2 = "NONE";
				break;
			}
			ss << c1;
			p2.append(ss.str());
		}
		if (p1 != "NONE" && q[n - 1] != p1[n - 2] + p1[n - 1] - '0')
			p1 = "NONE";
		if (p2 != "NONE" && q[n - 1] != p2[n - 2] + p2[n - 1] - '0')
			p2 = "NONE";
		ans.push_back(p1);
		ans.push_back(p2);
		return ans;
	}
};
