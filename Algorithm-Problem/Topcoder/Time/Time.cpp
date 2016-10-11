// problem at : SRM 144 Div 2 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=1708
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())

class Time{
public:
	string i2s(int n){
		stringstream s;
		s<<n;
		return s.str();
	}
	
	string whatTime(int nt){
		string t;
		int n=nt;
		t.append(i2s(n/3600));
		t.append(":");
		n=n%3600;
		t.append(i2s(n/60));
		t.append(":");
		t.append(i2s(n%60));
		return t;
	}
};
