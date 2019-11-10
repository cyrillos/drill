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
        int oddCells(int rows, int cols, vector<vector<int>>& indices) {
                vector<vector<int>> matrix(rows, vector<int>(cols, 0));
                int n_odds = 0;
                for (int k = 0; k < indices.size(); k++) {
			for (int i = 0; i < cols; i++) {
				int r = indices[k][0];
				matrix[r][i]++;
				if (matrix[r][i] % 2)
					n_odds++;
				else
					n_odds--;
			}
			for (int i = 0; i < rows; i++) {
				int c = indices[k][1];
				matrix[i][c]++;
				if (matrix[i][c] % 2)
					n_odds++;
				else
					n_odds--;
			}
                }

                return n_odds;
        }
};

int main()
{
	struct input {
		int			n; // rows
		int			m; // cols
		vector<vector<int>>	indices;
	} input[] = {
		{
			.n	= 2,
			.m	= 3,
			.indices= {{0,1}, {1,1}},
		}, {
			.n	= 2,
			.m	= 2,
			.indices= {{1,1}, {0,0}},
		},
	};

	Solution solution;
	for (auto& v: input) {
		printf("m %d n %d odds %d\n",
		       v.m, v.n,
		       solution.oddCells(v.n, v.m, v.indices));
	}
	return 0;
}
