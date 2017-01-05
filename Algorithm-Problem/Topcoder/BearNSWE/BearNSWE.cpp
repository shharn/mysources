// problem at : SRM 695 Div2 Level 1
#include <vector>
#include <math.h>
using namespace std;
#define sz(c) ((int)(c).size())
class BearNSWE{
public:
  double totalDistance(vector<int> a, string dir){
    int dist=0,x=0,y=0;
    for(int i=0;i<sz(a);i++){
      dist+=a[i];
      if(dir[i]=='N') y+=a[i];
      if(dir[i]=='S') y-=a[i];
      if(dir[i]=='W') x-=a[i];
      if(dir[i]=='E') x+=a[i];
    }
    return dist+sqrt(x*x+y*y);
  }
};
