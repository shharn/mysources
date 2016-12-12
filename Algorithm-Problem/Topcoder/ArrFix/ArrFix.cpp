// problem at : SRM 696 Div2 Level Two
//              https://community.topcoder.com/stat?c=problem_statement&pm=14361&rd=16775
#include <map>
#include <vector>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
class ArrFix{
public:
  int mindiff(vector<int> a, vector<int> b, vector<int> f){
    map<int, int> matched, unmatched;
    int nUnmatched=0,no_matched=0;
    fori0(i,0,sz(f)){
      if(a[i]==b[i])
        matched[b[i]]++;
      else{
        unmatched[b[i]]++;
        nUnmatched++;
      }
    }
    
    fori0(i,0,sz(f)){
      if(unmatched[f[i]]>0){
        nUnmatched--;
        unmatched[f[i]]--;
      }
      else if(matched[f[i]]>0)
        matched[f[i]]--;
      else 
        no_match++;
    }
    return no_match>nUnmatched?no_match:nUnmatched;
  }
};
