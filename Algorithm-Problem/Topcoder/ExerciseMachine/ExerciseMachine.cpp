#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())

int getSecond(string t){
  int t[3],i=0;
  stringstream ss(t);
  string tm;
  while(i<3){
    getline(ss,tm,':');
    t[i++]=atoi(tm.c_str());
  }
  return t[0]*3600+t[1]*60+t[2];
}

int gcd(int a, int b){
  if(a<b) swap(a,b);
  if(b==0) return a;
  return gcd(b,a%b);
}

int lcm(int a, int b){
  return a*b/gcd(a,b);
}

class ExerciseMachine{
public:
  int getPercentages(string t){
    int s=getSecond(t)%100;
    if(s==0) return 99;
    s=lcm(100,s)/s;
    return (100%s?100/s:100/s-1);
  }
};
