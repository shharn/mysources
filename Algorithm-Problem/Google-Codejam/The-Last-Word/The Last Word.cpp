#include <iostream>
#include <string>
#include <deque>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice-out.out"
using namespace std;
deque<char> answer;
void main() {
	int T, currT;
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	cin >> T;
	for (currT = 1; currT <= T; currT++) {
		answer.clear();
		string str;
		string firstWord;
		cin >> str;
		firstWord = str[0];
		answer.push_front(firstWord[0]);
		for (int i = 1; i < str.length(); i++) {
			if (firstWord[0] < str[i] || firstWord[0] == str[i])
				answer.push_front(str[i]);
			else
				answer.push_back(str[i]);
			firstWord = answer.front();
		}
		cout << "Case #" << currT << ": ";
		int size = answer.size();
		for (int i = 0; i < size; i++) {
			cout << answer.front();
			answer.pop_front();
		}
		cout << endl;
	}
	_fcloseall();
}
