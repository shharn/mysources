// problem at : SRM 700 Div1 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14166&rd=16821

#include <vector>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
class FindingFriend{
public:
  int find(int roomSize, vi le, int fr){
    vi cpy(le);
    int n=sz(le), cnt=0;
    cpy.push_back(roomSize*n+1);
    sort(cpy.begin(), cpy.end());
    fori0(i,0,n+1){
      if(cpy[i]==fr) return 1;
      if(cpy[i]<fr){
        if(cpy[i]==roomSize*i+1) cnt=1;
        else cnt++;
      }
      else break;
    }
    return cnt;
  }
};
