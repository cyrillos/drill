#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

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
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int rows = matrix.size();
		int cols = matrix[0].size();
		int row = 0;

		//
		// Lookup for needed row
		if (rows > 1) {
			int l = 0, r = rows-1;
			while (l <= r) {
				int pos = (l + r) / 2;
				if (matrix[pos][cols-1] < target)
					l = pos+1;
				else if (matrix[pos][0] > target)
					r = pos-1;
				else {
					row = pos;
					break;
				}
			}
		}

		//
		// Lookup for needed col.
		int cl = 0, cr = cols-1;
		while (cl <= cr) {
			int pos = (cl + cr) / 2;
			if (matrix[row][pos] < target)
				cl = pos+1;
			else if (matrix[row][pos] > target)
				cr = pos-1;
			else
				return true;
		}

		return false;
	}
};

int main()
{
	struct {
		vector<vector<int>>	matrix;
		int			target;
	} d[] = {
#if 1
		{
			.matrix = {
				{1,3,5,7},
				{10,11,16,20},
				{23,30,34,60},
			},
			.target = 3,
		}, {
			.matrix = {
				{1,3,5,7},
				{10,11,16,20},
				{23,30,34,60},
			},
			.target = 13,
		}, {
			.matrix = {
				{1,3,5,7},
				{10,11,16,20},
				{23,30,34,60},
			},
			.target = 10,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 12,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 1,
		}
#else
		{
			.matrix = {
				{1,3,5,7},
			},
			.target = 1,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 0,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 2,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 3,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 4,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 5,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 7,
		}, {
			.matrix = {
				{1,3,5,7},
			},
			.target = 8,
		}
#endif
	};
	Solution solution;
	for (auto& v: d) {
		cout << v.matrix << ", " << v.target << " => " <<
			solution.searchMatrix(v.matrix, v.target) << endl;
	}
	return 0;
}
