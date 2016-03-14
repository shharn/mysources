#include <iostream>
#include <vector>
#include <algorithm>
#define INPUT_PATH "A-small-practice.in"
#define OUTPUT_PATH "A-small-practice-out.out"
#define ITER vector<int>::iterator 
using namespace std;
vector<int> whole, result;


void print_members(int currCase) {
	cout << "Case #" << currCase << ": ";
	for (ITER it = result.begin(); it != result.end(); it++)
		cout << *it << " ";
	
	cout << endl;
}

bool check(int item) {
	for (ITER it = whole.begin(); it != whole.end(); it++) {
		int tmp = *it;
		if ((double)tmp == (double)item * 0.75) {
			whole.erase(it);
			result.push_back(tmp);
			return true;
		}
		else if ((double)tmp * 0.75 == (double)item) {
			whole.erase(it);
			result.push_back(item);
			return true;
		}
	}
	whole.push_back(item);
	return false;
}

void main() {
	int T, currCase;
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		whole.clear();
		result.clear();
		int numOfItems, item;
		cin >> numOfItems;
		for (int i = 0; i < numOfItems; ) {
			cin >> item;
			if (!whole.empty())
				check(item) ? i++ : 0;
			else
				whole.push_back(item);
		}
		std::sort(result.begin(), result.end());
		print_members(currCase);
	}
	_fcloseall();
}
