#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

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
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		if (rows == 0)
			return {};
		int cols = matrix[0].size();
		if (cols == 0)
			return {};

		vector<int> res(rows * cols);

		int left = 0, right = cols-1, top = 0, down = rows-1;
		int pos = 0;
		while (pos < rows * cols) {
			// top | left to right
			for (int c = left; c <= right; c++)
				res[pos++] = matrix[top][c];
			// right | top to bottom
			for (int r = top+1; r <= down; r++)
				res[pos++] = matrix[r][right];
			if (top != down) {
				// bottom | right to left
				for (int c = right-1; c >= left; c--)
					res[pos++] = matrix[down][c];
			}
			if (left != right) {
				// left | bottom to top
				for (int r = down-1; r > top; r--)
					res[pos++] = matrix[r][left];
			}
			left++, right--, top++, down--;
		}

		return res;
	}
};

int main()
{
        vector<vector<int>> input[] = {
                {
                       {1, 2, 3},
                       {4, 5, 6},
                       {7, 8, 9},
               }, {
                       {1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9,10,11,12},
               }, {
                       {1, 2, 3 },
                       {4, 5, 6 },
                       {7, 8, 9 },
                       {10,11,12},
               }, {
                       {1, 2},
                       {3, 4},
               }, {
                       {6,9,7},
               }, {
                       {6},
                       {9},
                       {7},
                }
        };

	Solution solution;
	for (auto& m: input) {
		cout << m << " => " <<
			solution.spiralOrder(m) << endl;
	}
	return 0;
}
