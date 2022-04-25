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
	vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
		// 1 2 3
		// 4 5 6
		// 7 8 9
		int nr_rows = mat.size();
		if (nr_rows == 0)
			return {};
		int nr_cols = mat[0].size();
		if (nr_cols == 0)
			return {};

		//
		// Lets do a trick. Make the matrix being a rectangle
		// virtually, ie fill up with virtual columns,
		// then iterate diagonally top-down and reverse the
		// results when need to move bottom-up.
		//
		// a b c d e
		// 1 2 3 * *
		// 4 5 6 * *
		// 7 8 9 * *
		//
		// a b c
		// 1 2 3

		vector<int> res;
		vector<int> tmp;
		int vcols = nr_cols + nr_rows - 1;
		bool top_down = false;
		for (auto c = 0; c <= vcols; c++) {
			for (auto cc = c, rr = 0; cc >= 0; cc--, rr++) {
				if (cc < nr_cols && rr < nr_rows)
					tmp.push_back(mat[rr][cc]);
			}
			if (!top_down) {
				top_down = true;
				reverse(tmp.begin(), tmp.end());
			} else
				top_down = false;

			res.insert(res.end(), tmp.begin(), tmp.end());
			tmp.erase(tmp.begin(), tmp.end());
		}

		return res;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{1,2,3},{4,5,6},{7,8,9}},	// [1,2,4,7,5,3,6,8,9]
		{{1,2},{3,4}},			// [1,2,3,4]
		{{7},{9},{6}},			// [7,9,6]
		{{1},{2},{3},{4},{5},{6},{7},{8},{9},{10}},	// same
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.findDiagonalOrder(nums) << endl;
	}
	return 0;
}
