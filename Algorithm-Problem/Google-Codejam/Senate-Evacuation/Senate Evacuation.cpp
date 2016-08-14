// problem at : https://code.google.com/codejam/contest/4314486/dashboard#s=p0

#include <iostream>
#include <vector>
#include <set>
#include <string>
#define INPUT_PATH "A-large-practice.in"
#define OUTPUT_PATH "A-large-practice-out.out"
#define FOR0(i, n) for(int (i)=0; (i)<(n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)
#define IT_SET set<pair<int, char>>::iterator
using namespace std;
vector<string> ans;
set<pair<int, char>> m;
int main() {
	freopen(INPUT_PATH, "r", stdin);
	freopen(OUTPUT_PATH, "w", stdout);
	int T;
	cin >> T;
	FOR1(ct, T) {
		int N;
		cin >> N;
		FOR0(i, N) {
			int t;
			cin >> t;
			m.insert(make_pair(t, 'A' + i));
		}

		while (m.size() > 0) {
			if (m.size() == 1) {
				IT_SET it = m.begin();
				string tmp;
				tmp.push_back(it->second);
				ans.insert(ans.end()-1, tmp);
				m.erase(*it);
				break;
			}
			IT_SET end, preend;
			int z = 0;
			for (end = m.begin(), preend = m.begin(); z < m.size() - 1; z++, end++);
			preend = end; preend--;

			pair<int, char> p1 = *end, p2 = *preend;
			int a = p1.first, b = p2.first;
			if (a - b > 1) {
				string tmp;
				tmp.push_back(end->second);
				tmp.push_back(end->second);
				ans.push_back(tmp);
				if (a > 2) m.insert(make_pair(end->first - 2, end->second));
				m.erase(*end);
			}
			else {
				string tmp;
				tmp.push_back(end->second);
				tmp.push_back(preend->second);
				ans.push_back(tmp);
				if(end->first > 1)	m.insert(make_pair(end->first - 1, end->second)); 
				if(preend->first > 1) m.insert(make_pair(preend->first - 1, preend->second));
				m.erase(*end);
				m.erase(*preend);
			}
		}
		cout << "Case #" << ct << ": ";
		for (vector<string>::iterator it = ans.begin(); it != ans.end(); it++)
			cout << *it << " ";
		cout << endl;
		ans.clear();
	}
	_fcloseall();
	return 0;
}
