#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define sz(c) ((int)(c).size())
#define forit(it, c) for(auto (it)=(c).begin();(it)!=(c).end();(it)++)
typedef vector<int> vi;
typedef vector<pair<int, int>> vpii;
typedef vector<string> vs;
class Bonuses{
public:
    vi getDivision(vi p){
        vi ans;
        int n=sz(p), sum=0, psum=0;
        bool used[50];
        fori0(i,0,n) sum+=p[i];
        fori0(i,0,n){
            int pp=(double)p[i]/(double}sum*100;
            psum+=pp;
            ans.push_back(pp);
        }
        
        int re=100-psum;
        fori0(i,0,re){
            int max=0, idx=0;
            fori0(j,0,n){
                if(max<p[j]&&!used[j]){
                    max=p[j];
                    idx=j;
                }
            }
            used[idx]=true;
            ans[idx]++;
        }
        return ans;
    }
};
