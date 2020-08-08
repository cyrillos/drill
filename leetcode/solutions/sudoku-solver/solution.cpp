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

class Solution {
public:
	bool solve(vector<vector<char>>& board, vector<pair<int,int>>& dot_pos, int dot_nr) {
		//
		// Already saw everything.
		if (dot_nr >= (int)dot_pos.size())
			return true;

		int row = dot_pos[dot_nr].first;
		int col = dot_pos[dot_nr].second;

		//
		// The idea is to set a value from [1;9]
		// range to to dot position and check if
		// it matches the constraints.
		for (int i = 0; i < 9; i++) {
			char c = i + '1';
			int allowed = true;

			//
			// Test if there the same number
			// along a row or a col.
			for (int j = 0; j < 9; j++) {
				if (board[row][j] == c ||
				    board[j][col] == c) {
					allowed = false;
					break;
				}
			}

			if (allowed) {
				//
				// Now test a 3x3 subbox.
				int r_sub = row / 3 * 3;
				int c_sub = col / 3 * 3;

				for (int rr = r_sub; rr < r_sub + 3; rr++) {
					for (int cc = c_sub; cc < c_sub + 3; cc++) {
						if (board[rr][cc] == c) {
							allowed = false;
							break;
						}
					}
				}

				// This number is allowed, lets try to
				// find anoner one which would fit recursively.
				if (allowed) {
					board[row][col] = c;
					if (solve(board, dot_pos, dot_nr + 1))
						return true;

					// This number didn't fit, restore
					// the dot back and try another
					// number from [1;9].
					board[row][col] = '.';
				}
			}
		}

		return false;
	}

	void solveSudoku(vector<vector<char>>& board) {
		vector<pair<int,int>> dot_pos;

		assert(board.size() == 9);
		assert(board[0].size() == 9);

		//
		// Remember the positions
		// we need to fill up
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				if (board[row][col] == '.')
					dot_pos.push_back({row, col});
			}
		}

		//
		// Recursively try any possible
		// configuration.
		solve(board, dot_pos, 0);
	}

};

int main()
{
	vector<vector<char>> input[] = {
		{
			{'5','3','.', '.','7','.', '.','.','.'},
			{'6','.','.', '1','9','5', '.','.','.'},
			{'.','9','8', '.','.','.', '.','6','.'},

			{'8','.','.', '.','6','.', '.','.','3'},
			{'4','.','.', '8','.','3', '.','.','1'},
			{'7','.','.', '.','2','.', '.','.','6'},

			{'.','6','.', '.','.','.', '2','8','.'},
			{'.','.','.', '4','1','9', '.','.','5'},
			{'.','.','.', '.','8','.', '.','7','9'},
		},
	};
	Solution solution;
	for (auto& board: input) {
		for (size_t r = 0; r < 9; r++) cout << board[r] << endl;
		cout << "---" << endl;
		solution.solveSudoku(board);
		for (size_t r = 0; r < 9; r++) cout << board[r] << endl;
	}
	return 0;
}
