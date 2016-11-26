// problem at : SRM 697 Div2 Level Two
//              https://community.topcoder.com/stat?c=problem_statement&pm=14369&rd=16776
#include <string>
#include <vector>
#include <math.h>
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
class DivisibleSetDiv2{
public:
  string isPossible(vector<int> b){
    for(int s=10000;s>=sz(b);s--){
      int ss=s;
      bool possible=true;
      fori0(i,0,sz(b)){
        int x=floor(ss/b[i]);
        while(x==0||x*b[i]<s) x++;
        if(ss>x){
          possible=false;
          break;
        }
        ss-=x;
      }
      if(possible) return "Possible";
    }
    return "Impossible";
  }
};
