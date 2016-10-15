// problem at : 2004 TCCC Online Round 1, Div1, Level Two
//              https://community.topcoder.com/stat?c=problem_statement&pm=1918&rd=5006
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++) 
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it, c) for(auto (it)=(c).begin();(it)!=(c).end();(it)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
class FlowerGarden{
public:
	vi getOrdering(vi h, vi b, vi w){
		vi ans;
		int n=sz(h);
		bool done[50]={0};
		fori0(i,0,n){
			int best=-1;
			fori0(j,0,n){
				if(!done[j]){
					bool candidate=true;
					fori0(k,0,n){
						if(k!=j&&!done[k]&&h[k]<h[j]&&b[k]<=w[j]&&w[k]>=b[j])
							candidate=false;
					}
					if(candidate && (best==-1 || h[best]<h[j])) best=j;
				}
			}
			res.push_back(h[best]);
			done[best]=true;
		}
		return ans;
	}
};
