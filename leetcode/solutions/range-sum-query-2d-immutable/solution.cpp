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

class NumMatrix {
public:
	int nr_rows;
	int nr_cols;

	vector<vector<int>> m;
	vector<vector<int>> c;

	NumMatrix(vector<vector<int>>& matrix) {
		this->nr_rows = matrix.size();
		this->nr_cols = this->nr_rows > 0 ? matrix[0].size() : 0;
		this->m = matrix;

		this->c = vector<vector<int>>(this->nr_rows, vector<int>(this->nr_cols, 0));

		// just keep in cache columns sums
		// per row, then we can simply find
		// answer removing previous sums.
		for (auto i = 0; i < this->nr_rows; i++) {
			this->c[i][0] = this->m[i][0];
			for (auto j = 1; j < this->nr_cols; j++) {
				this->c[i][j] = this->c[i][j-1] + this->m[i][j];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int sum = 0;

		for (auto i = row1; i <= row2; i++) {
			sum += this->c[i][col2];
			if (col1 > 0)
				sum -= this->c[i][col1-1];
		}

		return sum;
	}
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
//["NumMatrix","sumRegion","sumRegion","sumRegion"]
//[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]

//expected: [null,8,11,12]

int main()
{
	vector<vector<int>> matrix = {
		{3,0,1,4,2},
		{5,6,3,2,1},
		{1,2,0,1,5},
		{4,1,0,1,7},
		{1,0,3,0,5},
	};

	NumMatrix m(matrix);
	cout << m.sumRegion(2,1,4,3) << endl;
	cout << m.sumRegion(1,1,2,2) << endl;
	cout << m.sumRegion(1,2,2,4) << endl;
	return 0;
}
