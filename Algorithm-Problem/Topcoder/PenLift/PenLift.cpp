// problem at : SRM 144 Div 1 Level Three
//              https://community.topcoder.com/stat?c=problem_statement&pm=1649&rd=4515
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(it, c) for(auto (it)=(c).begin();(it)!=(c).end():(it)++)
#define sz(c) ((int)(c).size())
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<vi> vii;

vi tokenize(string s){
    stringstream ss(s);
    vi t;
    ss >> t[0] >> t[1] >> t[2] >> t[3];
    return t;
}

class PenLift{
public:
    int numTimes(vs s, int n){
        set<int> e;
        fori0(i,0,sz(s)){
            vi v=tokenize(s[i]);
            fori0(j,0,4) e.insert(v[j]);
        }
        
        map<int, int> m;
        int ct=0;
        // transform for optimization
        forit(it, e) m[*it]=ct++;
        
        // caculate the number of edges at each optimized point
        vii adj(40000);
        fori0(i,0,sz(a)){
            vi v=tokenize(a[i]);
            fori0(j,0,4) v[j]=m[v[j]];
            if(v[0]==v[2]){
                if(v[1]>v[3]) swap(v[1],v[3]);
                fori0(j,v[1],v[3]){
                    adj[v[0]*200+j].push_back(v[0]*200+j+1);
                    adj[v[0]*200+j+1].push_back(v[0]*200+j);
                }
            }
            else{
                if(v[0]>v[2]) swap(v[0],v[2]);
                fori0(j,v[0],v[2]){
                    adj[j*200+v[1]].push_back((j+1)*200+v[1]);
                    adj[(j+1)*200+v[1]].push_back(j*200+v[1]);
                }
            }
        }
        
        // sort(for gathering duplicate numbers in consecutive way) &
        // remain only one unique number
        fori0(i,0,sz(adj)){
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }
        
        int ans=0;
        fori0(i,0,sz(adj)){
            if(adj[i].size()){
                queue<int> q;
                q.push(i);
                int odds=0;
                while(!q.empty()){
                    int tq=q.front(); q.pop();
                    if(sz(adj[tq])%2) odds++;
                    fori0(j,0,sz(adj[tq])) q.push(adj[tq][j]);
                    adj[tq].clear();
                }
                if(odds==0) odds=2;
                if(b%2==0) odds=2;
                ans+=odds/2;
            }
        }
        return ans-1;
    }
};
