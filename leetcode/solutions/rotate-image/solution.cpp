#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static void show(vector<vector<int>>& v)
{
	for (auto i = 0; i < v.size(); i++) {
		for (auto j = 0; j < v.size(); j++) {
			cout << v[i][j] << ", ";
		}
		cout << endl;
	}
	cout << "---" << endl;
}

class Solution {
public:
	void rotate(vector<vector<int>>& m) {
		//
		// We simply need to transpose
		// the matrix and reverse the
		// rows.
		//
		// When matrix is transposed it
		// might be considered as mapped
		// over main diagonal. And then
		// we reverse the rows. These two
		// operations as simply isomorphic
		// to one clockwise rotation.
		//
		// 1 2 3      1 4 7
		// 4 5 6  =>  2 5 8
		// 7 8 9      3 6 9
		int n = m.size();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < i; j++) {
				swap(m[i][j], m[j][i]);
			}
		}

		//
		// 1 4 7    7 4 1
		// 2 5 8 => 8 5 2
		// 3 6 9    9 6 3
		for(int i = 0; i < n; i++) {
			reverse(m[i].begin(), m[i].end());
		}
	}
};

int main()
{
	vector<vector<int>> v = {
		{
			{1,2,3},
			{4,5,6},
			{7,8,9},
		},
	};
	Solution s;
	show(v);
	s.rotate(v);
	show(v);

	return 0;
}
