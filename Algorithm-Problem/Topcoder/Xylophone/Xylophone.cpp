// problet at : SRM 700 Div2 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14415&rd=16821

#include <vector>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
typedef vector<bool> vb;
class Xylophone{
public:
  int countKeys(vi v){
    vb b(7, false);
    int cnt=0;
    fori0(i,0,sz(v))
      if(!b[v[i]%7]){
        b[v[i]%7]=true;
        cnt++;
      }
    return cnt;
  }
};
