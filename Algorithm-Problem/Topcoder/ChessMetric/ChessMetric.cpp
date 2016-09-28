// problem at : TCCC 03 Round 4
//              https://community.topcoder.com/stat?c=problem_statement&pm=1592&rd=4482
#include <iostream>
#include <vector>
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
#define forit(container, it) for(typeof((c).begin() (it) = (c).begin(); (it) != (c).end(); (it)++)
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
ull memory[51][100][100];
class ChessMetric {
public:
	int dy[16] = { -1, -1, -1, 0, 1, 1, 1, 0, -1, -1, 1, 1, -2, -2, 2, 2 };
	int dx[16] = { -1, 0, 1, 1, 1, 0, -1, -1, -2, 2, -2, 2, -1, 1, -1, 1 };
	ull howMany(int size, vi start, vi end, int numMoves) {
		memset(memory, 0, sizeof(memory));
		memory[0][start[0]][start[1]] = 1;
		fori0(mv,0,numMoves) fori0(y, start[0], size) fori0(x, start[1], size){
			if (memory[mv][y][x] > 0) {
				fori0(i, 0, 16) {
					int yy = y + dy[i];
					int xx = x + dx[i];
					if (0 <= yy && yy < size && 0 <= xx && xx < size)
						memory[mv + 1][yy][xx] += memory[mv][y][x];
				}
			}
		}
		return memory[numMoves][end[0]][end[1]];
	}
};
