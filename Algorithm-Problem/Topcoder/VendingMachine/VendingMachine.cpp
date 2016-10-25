// problem at : SRM 145 Div 1 Level Two
//              https://community.topcoder.com/stat?c=problem_statement&pm=1130&rd=4530
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vi> vvi;

int s2i(string s){
    stringstream ss(s);
    int n;
    ss >> n;
    return n;
}

class VendingMachine{
public:
  vvi p;
  vi ps;
  int ct, cp, t;
  int goToHighest(){
    int maxp=0;
    fori0(i,1,sz(ps)) if(ps[maxp]<ps[i]) maxp=i;
    return maxp;
  }
  
  int getTime(int r, int c){
    int minp=min(c,cp);
    int maxp=max(c,cp);
    int res +=min(abs(cp-c),minp+sz(ps)-maxp);
    ps[c]-=p[r][c];
    p[r][c]=0;
    return res;
  }
  
  int motorUse(vs price, vs purchase){
    ct=cp=t=0;
    p.resize(sz(price));
    fori0(i,0,sz(price)){
        string tstr=price[i];
        int j=0, pos1=0,pos2=-1;
        while(pos2!=-1 || pos1<=0){
            pos1=pos2+1;
            pos2=tstr.find(' ', pos1);
            if(pos2==-1)
                p[i].push_back(s2i(tstr.substr(pos1)));
            else
                p[i].push_back(s2i(tstr.substr(pos1, pos2-pos1)));
            if(i==0)
                ps.push_back(p[i].back());
            else
                ps[j++]+=p[i].back();
        }
    }
    
    int col = goToHighest();
    int(col != cp){
        ++t;
        cp = col;
    }
    
    fori0(i,0,sz(purchase)){
        string tstr=purchase[i];
        int r,c,time,pos1=0,pos2=0;
        pos2=tstr.find(',',pos1);
        r=s2i(tstr.substr(pos1,pos2-pos1));
        pos1=pos2+1;
        pos2=tstr.find(':',pos1);
        c=s2i(tstr.substr(pos1,pos2-pos1));
        pos1=pos2+1;
        time=s2i(tstr.substr(pos1));
        if(time-ct>=5){
            col = goToHighest();
            if(col != cp){
                int minp = min(col,cp);
                int maxp = max(col,cp);
                t+=min(abs(col-cp), minp+sz(ps)-maxp);
                cp=col;
            }
        }
        int needTime=getTime(r,c);
        if(needTime==-1) return -1;
        t+=needTime;
        ct=time;
    }
    col = goToHighest();
    if(col!=cp) ++t;
    return t;
  }
};
