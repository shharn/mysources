#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define sz(c) ((int)(c).size())
typedef vector<string> vs;
int ct[27];
class DitherCounter{
public:
    int count(string d, vs scr){
        memset(ct, 0, sizeof(ct));
        int n=sz(scr), ans=0;
        fori0(i,0,n) fori0(j,0,n) ct[scr[i][j]-'A']++;
        fori0(i,0,sz(d)) ans+=ct[d[i]-'A'];
        return ans;
    }
};
