#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<string>>& v)
{
	out << '[' << endl;
	for (auto it1 = v.begin(); it1 != v.end(); ++it1) {
		out << " [";
		for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
			if (it2 != it1->begin())
				out << "  ";
			out << '"' << *it2 << '"';
			if (it2 != it1->end() - 1)
				out << ',' << endl;
		}
		out << ']';
		if (it1 != v.end() - 1)
			out << ',';
		out << endl;
	}
	out << ']' << endl;
	return out;
}

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res;

		if (n < 4)
			return res;

		//
		// Tracker -- keep a queen position
		// per row, each member matches the
		// queen column position on the
		// appropriate row. Imagine it as
		//
		// +---+
		// | a |
		// +---+
		// | b |
		// +---+
		//
		// where @a is the position of Q on row 0,
		// @b is the position on row 1 and etc
		vector<int> track(n, -1);

		auto add_solution = [&]() {
			vector<string> r;
			r.reserve(n);

			for (int row = 0; row < n; row++) {
				string s(n, '.');
				int col = track[row];
				s[col] = 'Q';
				r.push_back(move(s));
			}
			res.push_back(move(r));
		};

		//
		// Test if we're allowed to place a queen
		// at the poistion [row; col] (remember
		// it is a square board) (we dont have to
		// check after @row, since they are empty
		// yet).
		auto is_allowed = [&](int row, int col) {
			for (int r = 0; r < row; r++) {
				// Vertical match
				if (track[r] == col)
					return false;

				// Diagonal matches
				// (consider sliding square
				// starting from position track[r],
				// and ending at position track[r])
				if (track[r] + row - r == col)
					return false;
				if (track[r] - row + r == col)
					return false;
			}
			return true;
		};

		int row = 0, col;
		while (row >= 0) {
			for (col = track[row] + 1; col < n; col++) {
				if (is_allowed(row, col))
					break;
			}

			if (col < n) {
				track[row] = col;
				//
				// it is a new solution
				if (row == n - 1) {
					add_solution();
				} else {
					// step on next row
					row++;
				}
			} else {
				// reset this position
				// and try previous
				// row to distribute.
				track[row--] = -1;
			}
		}

		return res;
	}
};

int main()
{
	int input[] = {
		4,
	};
	Solution solution;
	for (auto n: input) {
		cout << n << " => " << solution.solveNQueens(n) << endl;
	}
	return 0;
}
