// problem at : SRM 698 Div2 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14389

#include <iostream>
#include <string>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)

class Initials {
public:
	string getInitials(string s) {
		string ans;
		ans.append(s.substr(0,1));
		int pos = 0;
		while (true) {
			pos = s.find(' ', pos + 1);
			if (pos == string::npos)
				break;
			ans.append(s.substr(pos + 1, 1));
		}
		return ans;
	}
};
