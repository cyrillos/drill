#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

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
	int minimumTotal(vector<vector<int>>& t) {
		int rows = t.size();
		int cols = rows;
		int r, c;

		//
		// Walk upside down accumulating
		// the minimum sum.
		//
		//     2
		//    3 4
		//   6 5 7
		//  4 1 8 3
		//
		// [2,3,5,1] -> 11
		//
		//   -1		          [-1]
		//   2 3	         [1 || 2]
		// 1 -1 -3	[2 | 0 | -2 || 3 | 1 | -1]
		//
		// [-1, 2, -1] -> -1 + 2 - 2 = -1
		for (r = rows-1; r > 0; r--) {
			for (c = 0; c < cols-1; c++) {
				int v1 = t[r][c] + t[r-1][c];
				int v2 = t[r][c+1] + t[r-1][c];
				t[r-1][c] = min(v1, v2);
			}
			cols--;
		}

		return t[0][0];
	}
};

int main()
{
	vector<vector<int>> data[] = {
		{{2},{3,4},{6,5,7},{4,1,8,3}},	// 11
		{{-1},{2,3},{1,-1,-3}},		// -1
		{{-10}},			// -10
	};
	Solution solution;
	for (auto& d: data) {
		cout << endl << d << " => " <<
			solution.minimumTotal(d) << endl;
	}
	return 0;
}
