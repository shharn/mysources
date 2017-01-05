// problem at : SRM 695 Div2 Level 2
#include <string>
#include <vector>
using namespace std;
#define sz(c) ((int)(c).size())
class BearPasswordAny{
public:
  string findPassword(vector<int> x){
    int sum=0, N=sz(x);
    string ans;
    char a='a';
    for(int i=N;i>=1;--i){
      while(x[i-1]){
        sum+=i;
        for(int j=0;j<i;j++)
          ans+=a;
        a='a'+'b'-a;
        for(int j=i;j>=1;--j)
          x[j-1]-=i-j+1;
        for(int j=i;j>=1;--j){
          if(x[j-1]<0)
            return "";
        }
      }
    }
    if(sum!=N)
      return "";
    return ans;
  }
};
