#include <iostream>
#include <vector>
#define INPUT_PATH "B-large-practice.in"
#define OUTPUT_PATH "B-large-practice-out.out"
#define ITER vector<int>::iterator
using namespace std;
vector<int> members;

void PrintMembers() {
	for (ITER it = members.begin(); it != members.end(); it++)
		cout << *it << " ";
	cout << endl;
}

void OneTurns() {
	for (ITER it = members.begin(); it != members.end(); it += 2) {
		ITER next_iter = it + 1;
		iter_swap(it, next_iter);
	}
}

void TwoTurns() {
	ITER it;
	ITER next_iter;
	int memory = *members.begin(), prev_memory;
	for (it = members.begin(); it != (members.end() - 2); it += 2) {
		next_iter = it + 2;
		memory = *next_iter;
		if (it == members.begin())
			*next_iter = *it;
		else
			*next_iter = prev_memory;
		prev_memory = memory;
	}
	next_iter = members.begin();
	*next_iter = memory;

	for (it = members.begin() + 1, memory = *it; it != members.end() - 1; it += 2)
		*it = *(it + 2);
	*it = memory;
}

void FindPrevNextMember(int& right, int& left, int K) {
	ITER it;
	for (it = members.begin(); it != members.end(); it++) {
		if (*it == K) {
			if (it == members.begin())
				right = *(members.end() - 1);
			else
				right = *(it - 1);

			if (it == members.end() - 1)
				left = *members.begin();
			else
				left = *(it + 1);
			break;
		}
	}
}

void StartDance(int D, int N) {
	int tmp = 0;
	while (tmp < N) {
		if (N - tmp > 1) {
			TwoTurns();
			tmp += 2;
		}
		else {
			OneTurns();
			tmp++;
		}
	}
}

void parseMembersFromFile(int D) {
	for (int i = 1; i <= D; i++)
		members.push_back(i);
}

int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T, currCase;
	cin >> T;
	for (currCase = 1; currCase <= T; currCase++) {
		members.clear();
		int D, K, N;
		cin >> D >> K >> N;
		N = N % D;
		parseMembersFromFile(D);
		StartDance(D, N);
		int right, left;
		FindPrevNextMember(right, left, K);
		cout << "Case #" << currCase << ": " << left << " " << right << endl;
	}
	_fcloseall();
	return 0;
}
