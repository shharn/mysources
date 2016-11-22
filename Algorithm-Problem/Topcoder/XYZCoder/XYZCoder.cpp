// problem at : SRM 700 Div2 Level 3
//              https://community.topcoder.com/stat?c=problem_statement&pm=14401&rd=16821
#include <cstring>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef long long ll;
const ll mod=1000000007;
class XYZCoder{
public:
  ll dp[101][10001];
  int Room, Size;
  ll fact(int n){
    ll ans=1;
    fori1(i,1,n) ans*=i%mod;
    return ans;
  }
  
  int foo(int r, int rem){
    if(r>Room) return 1;
    if(dp[r][rem]) return dp[r][rem];
    ll ans=0;
    ans = foo(r+1, rem+Size-1);
    if(rem > 0) ans=(ans+foo(r, rem-1))%mod;
    return ans%mod;
  }
  
  int countWays(int room, int size){
    memset(dp, 0, sizeof(dp));
    Room=room, Size=size;
    return foo(1,0)*fact(room)%mod;
  }
};
