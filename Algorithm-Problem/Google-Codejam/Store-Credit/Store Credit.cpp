// Store Credit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int N;
	freopen("A-large-practice.in", "r", stdin);
	freopen("A-large-practice_output.out", "w", stdout);
	cin >> N;
	int numOfCase = 1;
	int items[2000] = { 0 };
	while (numOfCase <= N)
	{
		int max_credit;
		cin >> max_credit;
		int numOfItems;
		cin >> numOfItems;
		int sum = 0;
		int firstIndex = -1, secondIndex = -1;
		for (int i = 0; i < numOfItems; i++)
			cin >> items[i];

		bool End = false;
		for (int i = 0; i < numOfItems - 1 && !End; i++)
		{
			if (items[i] >= max_credit) continue;
			sum = items[i];
			for (int j = i + 1; j < numOfItems; j++)
			{
				if (sum + items[j] == max_credit)
				{
					firstIndex = i;
					secondIndex = j;
					cout << "Case #" << numOfCase << ": " << i+1 << " " << j+1 << endl;
					End = true;
					break;
				}
			}

		}
		numOfCase++;
	}
	return 0;
}

