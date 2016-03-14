#include <iostream>
#include <string>
#include <set>
#define INPUT_PATH "C-small-practice-2.in"
#define OUTPUT_PATH "C-small-practice-2-out.out"
#define ITERATOR set<string>::iterator
using namespace std;
set<string> deck;
void main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		deck.clear();
		int answer = 0, numOfWords;
		cin >> numOfWords;
		cin.ignore(10000, '\n');
		for (int i = 0; i < numOfWords; i++) {
			string tmp;
			getline(cin, tmp);
			if (!deck.empty()) {
				ITERATOR tmp_it = deck.end();
				tmp_it--;
				if (*tmp_it > tmp) answer++;
			}
			deck.insert(tmp);
		}
		cout << "Case #" << currCase << ": " << answer << endl;
	}
	_fcloseall();
}
