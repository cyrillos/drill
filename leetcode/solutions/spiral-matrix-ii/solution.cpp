#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

template<typename K, typename V>
ostream& operator<<(ostream& out, unordered_map<K,V> v)
{
       out << '{';
       for (auto it = v.begin(); it != v.end(); ++it) {
               if (it != v.begin())
                       out << ", ";
               out << '[' << it->first << "]: " << it->second;
       }
       out << '}';
       return out;
}

class Solution {
public:
	// See spiral-matrix code for details.
	vector<vector<int>> generateMatrix(int n) {
		if (n < 1) {
			return {};
		} else if (n == 1) {
			return vector<vector<int>>(1, vector<int>(1, 1));
		}
		vector<vector<int>> m(n, vector<int>(n));

		int c[2] = {0, n-1};
		int r[2] = {0, n-1};
		int nr = 1;

		while (c[0] <= c[1] && r[0] <= r[1]) {
			for (int i = c[0]; i <= c[1]; i++)
				m[r[0]][i] = nr++;
			r[0]++;

			if (c[0] > c[1] || r[0] > r[1]) break;

			for (int i = r[0]; i <= r[1]; i++)
				m[i][c[1]] = nr++;
			c[1]--;

			if (c[0] > c[1] || r[0] > r[1]) break;

			for (int i = c[1]; i >= c[0]; i--)
				m[r[1]][i] = nr++;
			r[1]--;

			if (c[0] > c[1] || r[0] > r[1]) break;
			for (int i = r[1]; i >= r[0]; i--)
				m[i][c[0]] = nr++;

			c[0]++;
			if (c[0] > c[1] || r[0] > r[1]) break;
		}

		return m;
	}
};

int main()
{
	int input[] = {0, 1, 2, 3, 4, 5};
	Solution solution;
	for (auto n: input) {
		cout << n << " => " << solution.generateMatrix(n) << endl;
	}
	return 0;
}
