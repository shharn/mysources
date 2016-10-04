// problem at : SRM 699 Div2 Level One
//              https://community.topcoder.com/stat?c=problem_statement&pm=14398&rd=16803
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
#define fori0(i,s,e) for(int (i)=(s);(i)<(e);(i)++)
#define fori1(i,s,e) for(int (i)=(s);(i)<=(e);(i)++)
class UpDownHiking{
public:
	int maxHeight(int N, int A, int B){
		int minidx,mindif=10000;
		fori1(i,1,N){
			int up = abs(A*i);
			int down = abs(B*N-1);
			if(mindif > abs(up-down)){
				mindif = abs(up-down);
				minidx = i;
			}
		}
		int up=abs(A*minidx);
		int down = abs(B*N-minidx);
		return (up > down?down:up);
	}
};
