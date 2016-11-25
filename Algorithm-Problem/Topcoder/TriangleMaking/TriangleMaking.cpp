// problem at : SRM 697 Div2 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14371&rd=16776
#include <vector>
#include <algorithm>
using namespace std;
class TriangleMaking{
public:
  int maxPerimeter(int a, int b, int c){
    vector<int> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    sort(v.begin(), v.end());
    int s = v[0]+v[1];
    int cc = s>v[2]?v[2]:s-1;
    return s+cc;
  }
};
