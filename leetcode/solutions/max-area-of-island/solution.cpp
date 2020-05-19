#include <algorithm>
#include <iostream>
#include <stack>
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

ostream& operator<<(ostream& out, const vector<vector<char>>& v)
{
	out << '[' << endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << endl;
		out << *it;
	}
	out << endl << ']' << endl;
	return out;
}

class Solution {
public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		size_t rows = grid.size();
		size_t cols = rows > 0 ? grid[0].size() : 0;
		int res = 0;

		stack<pair<size_t,size_t>> q;

		auto mark_adjusted = [&](size_t row, size_t col) {
			int len = 0;
			q.push(make_pair(row, col));

			while (!q.empty()) {
				pair<size_t,size_t> v = q.top();
				row = v.first;
				col = v.second;
				q.pop();

				if (grid[row][col] != 1)
					continue;
				//
				// Mark as visited
				grid[row][col] = 2;
				len++;

				if (row < rows-1 && grid[row+1][col] == 1)
					q.push(make_pair(row+1, col));
				if (row > 0 && grid[row-1][col] == 1)
					q.push(make_pair(row-1, col));
				if (col < cols-1 && grid[row][col+1] == 1)
					q.push(make_pair(row, col+1));
				if (col > 0 && grid[row][col-1] == 1)
					q.push(make_pair(row, col-1));
			}

			res = len > res ? len : res;
		};

		for (size_t row = 0; row < rows; row++) {
			for (size_t col = 0; col < cols; col++) {
				if (grid[row][col] == 1) {
					mark_adjusted(row,col);
				}
			}
		}

		return res;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{1,1,1,1,0},
			{1,1,0,1,0},
			{1,1,0,0,0},
			{0,0,0,0,0},	// 8
		}, {
			{1,1,0,0,0},
			{1,1,0,0,0},
			{0,0,1,0,0},
			{0,0,0,1,1},	// 4
		},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << solution.maxAreaOfIsland(nums) << endl;
	}
	return 0;
}
