// problem at : SRM 701 Div2 Level Three
//              https://community.topcoder.com/stat?c=problem_statement&pm=14429&rd=16822
#include <cstring>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)

class ThueMorseGame{
public:
  string get(int n, int m){
    if(m==1){
      int nn=n;
      bool who=false;
      while(true){
        nn--;
        if(__builtin_popcount(nn)&1)
          return who?"Bob":"Alice";
        who = !who;
      }
    }
    
    int nn=0;
    while(nn+m<n){
      nn+=m+1;
      while(__builtin_popcount(nn)&1) nn++;
    }
    
    if(nn<n) return "Alice";
    else return "Bob";
  }
};
