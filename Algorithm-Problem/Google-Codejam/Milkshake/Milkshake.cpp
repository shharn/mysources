// Milkshake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#define MALTED		1
#define UNMALTED	0
#define DONT_CARE	-1
#define NOT_FOUND	-1
#define FILENAME	"B-large-practice.in"
using namespace std;
int state[2000];
int preferences[2000][2000];

bool check(int currPerson, int numOfTypes)
{
	for (int i = 0; i < numOfTypes; i++)
		if (preferences[currPerson][i] != DONT_CARE)
			if (preferences[currPerson][i] == state[i])
				return true;
	return false;
}

bool mark(int currPerson, int numOfTypes)
{
	int malted_pos = NOT_FOUND;
	for (int i = 0; i < numOfTypes; i++)
		if (preferences[currPerson][i] == MALTED && state[i] == UNMALTED)
			malted_pos = i;

	if(malted_pos == NOT_FOUND)
		return false;
	else{
		state[malted_pos] = MALTED;
		return true;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	freopen("B-large-practice-output.out", "w", stdout);
	std::ifstream fin(FILENAME);
	std::string line;
	std::stringstream linestream;
	std::getline(fin, line);

	int C;
	linestream.str(line);
	linestream >> C;
	int numOfCase = 1;
	while (numOfCase <= C){
		int N, M;
		std::getline(fin, line);
		linestream.clear();
		linestream.str(line);
		linestream >> N;

		std::getline(fin, line);
		linestream.clear();
		linestream.str(line);
		linestream >> M;
		memset(state, UNMALTED, sizeof(state));
		memset(preferences, 0xff, sizeof(preferences)); // initialize to -1
		for (int i = 0; i < M; i++){
			int T;

			std:getline(fin, line);
			linestream.clear();
			linestream.str(line);
			linestream >> T;
			for (int j = 0; j < T; j++){
				int temp1, temp2;
				linestream >> temp1 >> temp2;
				preferences[i][temp1 - 1] = (temp2 > 0) ? MALTED : UNMALTED;
			}
		}

		bool isSatisfied = true;
		for(int k=0; k<2; k++){
			for (int i = 0; i < M; i++){
				if (!check(i, N)){
					if (k == 1){
						isSatisfied = false;
						break;
					}
					if (!mark(i, N))
						break;
				}
			}
		}

		cout << "Case #" << numOfCase++ << ": ";
		if (isSatisfied){
			for (int i = 0; i < N; i++){
				if (i == N - 1) 
					cout << state[i] << endl;
				else 
					cout << state[i] << " ";
			}
		}
		else
			cout << "IMPOSSIBLE" << endl;
	}

	fclose(stdout);
	return 0;
}

