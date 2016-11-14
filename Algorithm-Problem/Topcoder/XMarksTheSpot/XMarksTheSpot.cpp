// problem at : SRM 700 Div2 Level Tow

#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

class XMarksTheSpot{
public:
  int countArea(vi board){
    vpii unknown;
    int r=sz(board), c=sz(board[0]);
    int t=r,b=0,l=c,r=0;
    int cnt=0,ans=0;
    fori0(i,0,r) fori0(j,0,c){
      if(board[i][j]=='?'){
        unknown.push_back(make_pair(i,j));
        cnt++;
      }
      else if(board[i][j]=='O'){
        t=min(t,i);
        b=max(b,i);
        l=min(l,j);
        r=max(r,j);
      }
    }
    
    for(int i=0;i<1<<cnt;i++){
      int tt=t,bb=b,ll=l,rr=r;
      fori0(j,0,cnt){
        if((i>>j)&1){
          tt=min(tt,unknown[j].first);
          bb=max(bb,unknown[j].first);
          ll=min(ll,unknown[j].second);
          rr=max(rr,unknown[j].second);
        }
      }
      ans+=(bb-tt+1)*(rr-ll+1);
    }
    return ans;
  }
};
