// Minimum Scalar Product.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool compare(long long i, long long j)
{
	return (i < j);
}

int _tmain(int argc, _TCHAR* argv[])
{
	freopen("A-large-practice.in", "r", stdin);
	freopen("A-large-practice_output.out", "w", stdout);
	int T;
	cin >> T;
	int numOfCase = 1;
	vector<long long> first, second;
	while (numOfCase <= T){
		int N;
		cin >> N;
		for (int i = 0; i < N; i++){
			long long temp;
			cin >> temp;
			first.push_back(temp);
		}
		for (int i = 0; i < N; i++){
			long long temp;
			cin >> temp;
			second.push_back(temp);
		}
		std::sort(first.begin(), first.end(), compare);
		std::sort(second.begin(), second.end(), compare);
		long long sum = 0;
		for (int i = 0; i < N; i++)
			sum += first[i] * second[N - i - 1];

		cout << "Case #" << numOfCase << ": " << sum << endl;
		first.clear();
		second.clear();
		numOfCase++;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

