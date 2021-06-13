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
	int maximalSquare(vector<vector<char>>& m) {
		int rows = m.size();
		int cols = m[0].size();

		vector<vector<int>> d(rows, vector<int> (cols, 0));
		int best = 0;

		//
		// Tradirional DP case where we're counting
		// squares in diagonal.
		//
		// For example
		//
		// {'1','1','1','1','0'},
		// {'1','1','1','1','0'},
		// {'1','1','1','1','1'},
		// {'1','1','1','1','1'},
		// {'0','0','1','1','1'},
		//
		// transforms to
		//
		// {'1','1','1','1','0'},
		// {'1','2','2','2','0'},
		// {'1','2','3','3','1'},
		// {'1','2','3','4','2'},
		// {'0','0','1','2','3'},
		//

		if (m[0][0] == '1')
			best = d[0][0] = 1;

		for (int c = 1; c < cols; c++)
			best = max(best, d[0][c] = m[0][c] == '1' ? 1 : 0);

		for (int r = 1; r < rows; r++)
			best = max(best, d[r][0] = m[r][0] == '1' ? 1 : 0);
		for (int r = 1; r <rows; r++) {
			for (int c = 1; c < cols; c++) {
				if (m[r][c] != '1')
					continue;
				if (d[r-1][c] && d[r][c-1] && d[r-1][c-1]) {
					d[r][c] = min(d[r-1][c-1],
						     min(d[r-1][c], d[r][c-1]))  + 1;
				} else
					d[r][c] = 1;
				best = max(best, d[r][c]);
			}
		}
		return best > 1 ? best * best : best;
	}
};

int main()
{
	vector<vector<char>> input[] = {
		{	// 4
			{'1','0','1','0','0'},
			{'1','0','1','1','1'},
			{'1','1','1','1','1'},
			{'1','0','0','1','0'},
		}, {
			// 1
			{'0','1'},
			{'1','0'},
		}, {
			// 16
			{'1','1','1','1','0'},
			{'1','1','1','1','0'},
			{'1','1','1','1','1'},
			{'1','1','1','1','1'},
			{'0','0','1','1','1'},
		}, {
			{'0','0','0','0','0'},
			{'0','0','0','0','0'},
			{'0','0','0','0','1'},
			{'0','0','0','0','0'}
		}
	};

	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.maximalSquare(nums) << endl;
	}
	return 0;
}
