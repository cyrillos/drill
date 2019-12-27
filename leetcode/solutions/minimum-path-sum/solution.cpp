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
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.size() < 1 || grid[0].size() < 1)
			return 0;

		size_t nr_rows = grid.size();
		size_t nr_cols = grid[0].size();

		for (size_t c = 1; c < nr_cols; c++)
			grid[0][c] += grid[0][c-1];

		for (size_t r = 1; r < nr_rows; r++)
			grid[r][0] += grid[r-1][0];

		for (size_t c = 1; c < nr_cols; c++) {
			for (size_t r = 1; r < nr_rows; r++) {
				grid[r][c] += min(grid[r-1][c], grid[r][c-1]);
			}
		}

		return grid[nr_rows-1][nr_cols-1];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{
				{1,3,1},
				{1,5,1},
				{4,2,1},
			}, // 7
		},
		{
			{
				{ 1 },
			},
		},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.minPathSum(nums) << endl;
	}
	return 0;
}
