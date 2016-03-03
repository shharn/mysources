#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#define FILENAME "B-large-practice.in"
#define OUTPUT_FILE "B-large-practice.out"
using namespace std;

int main(int argc, char *argv[])
{
	freopen(OUTPUT_FILE, "w", stdout);
	stack<string> members;
	std::ifstream fin(FILENAME);
	std::string line;
	std::stringstream linestream;
	int N;
	std::getline(fin, line);
	linestream.str(line);
	linestream >> N;
	int numOfCase = 1;

	while (numOfCase <= N)
	{
		std::getline(fin, line);
		linestream.clear();
		linestream.str(line);
		string temp;
		while (!linestream.eof())
		{
			linestream >> temp;
			members.push(temp);
		}

		printf("Case #%d: ", numOfCase);
		while (1)
		{
			temp = members.top();
			members.pop();
			if (!members.empty())
				cout << temp << " ";
			else
			{
				cout << temp << endl;
				break;
			}
		}
		numOfCase++;
	}
	return 0;
}
