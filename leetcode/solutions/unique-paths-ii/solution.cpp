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
	int uniquePathsWithObstacles(vector<vector<int>>& grid) {
		int nr_rows = grid.size();
		int nr_cols = nr_rows > 0 ? grid[0].size() : 0;
		vector<vector<size_t>> dp(nr_rows, vector<size_t> (nr_cols, 0));

		if (nr_rows == 0 && nr_cols == 0)
                        return 0;

		if (grid[0][0] != 0)
			return 0;

		if (grid[nr_rows-1][nr_cols-1] != 0)
			return 0;

		//
		// Traditional DP: just assume ostacles
		// interrupt path and drop counters to zero.
		dp[0][0] = 1;
		for (int r = 1; r < nr_rows; r++) {
			if (grid[r][0] == 1)
				dp[r][0] = 0;
			else
				dp[r][0] = dp[r-1][0];
		}

		for (int c = 1; c < nr_cols; c++) {
			if (grid[0][c] == 1)
				dp[0][c] = 0;
			else
				dp[0][c] = dp[0][c-1];
		}

		for (int r = 1; r < nr_rows; r++) {
			for (int c = 1; c < nr_cols; c++) {
				if (grid[r][c] == 1) {
					dp[r][c] = 0;
				} else {
					dp[r][c] = dp[r-1][c] + dp[r][c-1];
				}
			}
		}

		return dp[nr_rows-1][nr_cols-1];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{0,0},
			{1,1},
			{0,0},		// 0
		},
		{
			{0, 0},		// 1
		},
		{
			{0, 1},		// 0
		},
		{
			{0,0,0},
			{0,1,0},
			{0,0,0},	// 2
		},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.uniquePathsWithObstacles(nums) << endl;
	}
	return 0;
}
