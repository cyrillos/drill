#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

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
	int maximalRectangle(vector<vector<char>>& matrix) {
		int rows = (int)matrix.size();
		int cols = rows > 0 ? (int)matrix[0].size() : 0;

		if (rows == 0 || cols == 0)
			return 0;

		//
		// The base idea is the similar to the
		// largest-rectangle-in-histogram problem.
		//
		// In the former problem we've been working
		// on static 2d bars. Now we can use same approach
		// except we walk over each row and consider it
		// as a new base for diagrams.
		//
		// For example we have the following matrix
		//
		//
		//    *   0
		//    * * 1
		//  * * * 2
		//  * *   3
		//  * * * 4
		//  * * *
		//  0 1 2
		//
		//  At level 2 the picture gonna be
		//
		//    *   0
		//    * * 1 <--
		//  * * * 2
		//    ^
		//    |
		//
		//  and max rectangle is 4 stars. Thus
		//  we simply add row by row and calculate
		//  the maximal rectangle found so far.

		int best = 0;

		auto max_rect = [&](vector<int>& height, stack<int>& idx) {
			for (int i = 0; i < (int)height.size(); i++) {
				while (!idx.empty() && height[i] < height[idx.top()]) {
					int h = height[idx.top()];
					idx.pop();

					int l = idx.empty() ? -1 : idx.top();
					best = max(best, h * (i - l - 1));
				}
				idx.push(i);
			}

			int n = (int)height.size();
			while (!idx.empty()) {
				int h = height[idx.top()];
				idx.pop();

				int l = idx.empty() ? -1 : idx.top();
				best = max(best, h * (n - l - 1));
			}
			return best;
		};

		vector<int> height(cols, 0);
		stack<int> idx;

		for (int c = 0; c < cols; c++)
			height[c] = matrix[0][c] == '1' ? 1 : 0;
		best = max_rect(height, idx);

		for (int r = 1; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (matrix[r][c] == '1')
					height[c] += 1;
				else
					height[c] = 0;
			}
			best = max_rect(height, idx);
		}
		return best;
	}
};

int main()
{
	vector<vector<char>> input[] = {
		{
			{'1','0','1','0','0'},
			{'1','0','1','1','1'},
			{'1','1','1','1','1'},
			{'1','0','0','1','0'},
		},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.maximalRectangle(nums) << endl;
	}
	return 0;
}
