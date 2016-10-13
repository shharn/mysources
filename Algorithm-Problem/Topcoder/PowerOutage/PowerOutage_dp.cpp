#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
class PowerOutage{
public:
  int estimateTimeOut(vi fj, vi tj, vi t){
    int sum=0, m=0, n=sz(fj);
    vi dp(50);
    dp[0]=0;
    fori0(i,0,n) sum+=t[i];
    fori0(i,0,50){
      fori0(j,0,n){
        if(tj[j]==i){
          dp[i]=dp[fj[j]]+t[j];
          break;
        }
      }
      m = max(m, dp[i]);
    }
    return sum*2-m;
  }
};
