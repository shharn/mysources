#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
class SortingSubsets{
public:
  int getMinimalSize(vi a){
    vi sorted(a);
    sort(sorted.begin(), sorted.end());
    int cnt=0;
    fori0(i,0,sz(a))
      if(a[i]!=sorted[i]) cnt++;
    return cnt;
  }
};
