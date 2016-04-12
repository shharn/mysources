// Problem -> https://code.google.com/codejam/contest/6254486/dashboard#s=p0
#include <iostream>
#include <string>
#include <set>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice-out.out"
using namespace std;
set<char> elements;

void mark(int N) {
	string each_digits = std::to_string(N);
	for (int i = 0; i < each_digits.size(); i++)
		elements.insert(each_digits.at(i));
}

bool checkAllMembers() {
	return elements.size() == 10;
}

void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		elements.clear();
		int N, firstNumber;
		cin >> N;
		firstNumber = N;
		while (!checkAllMembers() && N != 0) {
			mark(N);
			N += firstNumber;
		}
		cout << "Case #" << currCase << ": ";
		if (checkAllMembers())
			cout << N - firstNumber;
		else
			cout << "INSOMNIA";
		cout << endl;
	}
	_fcloseall();
}
