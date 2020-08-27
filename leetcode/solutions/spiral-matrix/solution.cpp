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
    vector<int> spiralOrder(vector<vector<int>>& m) {
	    vector<int> res;

	    if (m.size() < 1 || m[0].size() < 1)
		    return {};

	    int nr_cols = m[0].size();
	    int nr_rows = m.size();

	    size_t size = nr_cols * nr_rows;
	    int pos = 0;

	    if (nr_cols == 1 || nr_rows == 1) {
		    res.resize(size);
		    if (nr_cols == 1) {
			    for (int i = 0; i < nr_rows; i++)
				    res[pos++] = m[i][0];
		    } else {
			    for (int i = 0; i < nr_cols; i++)
				    res[pos++] = m[0][i];
		    }
		    return res;
	    }

	    res.resize(size + size/2);

	    int c[2] = {0, nr_cols-1};
	    int r[2] = {0, nr_rows-1};


	    // Say matrix is 3x3
	    // c[] = {0, 2}
	    // r[] = {0, 2}

	    while (c[0] <= c[1] && r[0] <= r[1]) {
		    // Horizontal forward
		    for (int i = c[0]; i <= c[1]; i++)
			    res[pos++] = m[r[0]][i];
		    // First row is complete
		    r[0]++;
		    // r = {1, 2}

		    // Vertical top down
		    for (int i = r[0]; i <= r[1]; i++)
			    res[pos++] = m[i][c[1]];
		    // Last column is complete
		    c[1]--;
		    // c = {0 ,1}

		    // -- || --

		    // c = {0, 1}
		    // r = {1, 2}

		    // Horizontal backward
		    for (int i = c[1]; i >= c[0]; i--)
			    res[pos++] = m[r[1]][i];
		    // Last row is complete
		    r[1]--;
		    // r = {1, 1}

		    // Vertical down top
		    for (int i = r[1]; i >= r[0]; i--)
			    res[pos++] = m[i][c[0]];

		    // Last column is complete
		    c[0]++;
		    // c = {1, 1}

		    // c = {1, 1}
		    // r = {1, 1}
	    }

	    res.resize(size);
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
