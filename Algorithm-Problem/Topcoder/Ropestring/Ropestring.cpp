// problem at : SRM 696 Div2 Level one
//              https://community.topcoder.com/stat?c=problem_statement&pm=14373&rd=16775
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
class Ropestring{
public:
  string makerope(string s){
    vector<int> odd,even;
    int cnt=0;
    fori0(i,0,sz(s)){
      if(s[i]=='-') cnt++;
      if(cnt>0 && (s[i]=='.'||i+1==sz(s)){
        if(cnt%2) odd.push_back(cnt);
        else even.push_back(cnt);
        cnt=0;
      }
    }
    sort(odd.begin(),odd.end(),std::greater<int>());
    sort(even.begin(),even.end(),std::greater<int>());
    string ans;
    fori0(i,0,sz(even)){
      int n=even[i];
      fori0(j,0,n) ans.append("-");
      if(sz(ans)<sz(s)) ans.append(".");
    }
    fori0(i,0,sz(odd)){
      int n=odd[i];
      fori0(j,0,n) ans.append("-");
      if(sz(ans)<sz(s)) ans.append(".");
    }
    fori0(i,sz(ans),sz(s)) ans.append(".");
    return ans;
  }
};
