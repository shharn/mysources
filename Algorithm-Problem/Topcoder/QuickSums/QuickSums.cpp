// problem at : SRM 179 Div2 Level Three
//              https://community.topcoder.com/stat?c=problem_statement&pm=2829&rd=5072

#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
typedef long long ll;
int memo[101][11][11];

class QuickSums{
public:
  int len;
  string S;
  ll s2l(string s){
    istringstrea is(s);
    ll n;
    is >> n;
    return n;
  }
  
  int go(int l, int r, int sum){
    if(l>=r) return 0;
    ll num = s2l(S.substr(l));
    if(num < sum) return memo[sum][l][r]=-1;
    if(num==sum) return memo[sum][l][r]=1;
    int min=-1;
    fori1(i,l+1,r){
      int t = s2l(S.substr(l,i-l));
      if(t>sum) break;
      int tt = go(i,r,sum-t);
      if(tt==-1) continue;
      min = tt+1;
    }
    return memo[sum][l][r]=(l==0&&r==len&&min!=-1?min-1:min);
  }
  
  int minSums(string s, int n){
    len = s.length();
    S=s;
    return go(0,len,n);
  }
};
