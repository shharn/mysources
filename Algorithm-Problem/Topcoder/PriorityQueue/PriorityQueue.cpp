// problem at : SRM 692 Div2 Lv1
//              https://community.topcoder.com/stat?c=problem_statement&pm=14295&rd=16747
#include <vector>
#include <string>
using namespace std;
#define sz(c) ((int)(c).size())

class PriorityQueue {
public:
  int findAnnoyance(string S, vector<int> a) {
    int sum = 0;
    for(int i=0; i<sz(S)-1; i++) {
      for(int j=i+1; j<sz(S); j++) {
        if(S[j]=='b') sum += a[i];
      }
    }
    return sum;
  }
};
