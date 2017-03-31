// problem at : SRM711 Div2 Lv2 
// https://community.topcoder.com/stat?c=problem_statement&pm=14555&rd=16880
#include <string>
#include <set>
using namespace std;

class StringTransform {
public:
  string isPossible(string s, string t) {
    set<char> a;
    for (int i = 0; i < s.length(); i++)
      a.insert(s[i]);
      
    for (int i = 0; i < s.length(); i++) {
      int found = a.count(t[i]);
      if (!found)
        return "Impossible";
      int pos = s.find_first_of(t[i]);
      if (pos > i) 
        return "Impossible";
    }
    return "Possible";
  }
};
