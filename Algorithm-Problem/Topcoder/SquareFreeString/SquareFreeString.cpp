// problem at : SRM 701 Div 2, Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14428

#include <cstring>
using namespace std;
#define sz(c) ((int)(c).size())

class SquareFreeString{
public:
  bool check(string s){
    string l = s.substr(0,sz(s)/2);
    string r = s.substr(sz(s)/2);
    return l==r;
  }
  
  string isSquareFree(string s){
    int n = sz(s);
    if(n<2) return "square-free";
    for(int i=2;i<=n;i+=2)
      for(int j=0;j+i<=n;j++)
        if(check(s.substr(j,i))) return "not square-free";
    return "square-free";
  }
};
