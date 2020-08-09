#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
	bool isValidSudoku(vector<vector<char>>& board) {
		unsigned mask;

		auto valid_cross = [&](auto r, auto c) {
			mask = 0;
			for (auto cc = 0; cc < 9; cc++) {
				if (board[r][cc] == '.')
					continue;
				auto v = 1u << (board[r][cc] - '0');
				if (mask & v)
					return false;
				mask |= v;
			}

			mask = 0;
			for (auto rr = 0; rr < 9; rr++) {
				if (board[rr][c] == '.')
					continue;
				auto v = 1u << (board[rr][c] - '0');
				if (mask & v)
					return false;
				mask |= v;
			}

			return true;
		};

		//
		// Test horizontals and verticals.
		for (auto pos = 0; pos < 9; pos++) {
			if (!valid_cross(pos, pos))
				return false;
		}

		//
		// Test submatrixes.
		auto valid_sub = [&](auto r, auto c) {
			mask = 0;
			for (auto rr = r; rr < r + 3; rr++) {
				for (auto cc = c; cc < c+3; cc++) {
					if (board[rr][cc] == '.')
						continue;
					auto v = 1u << (board[rr][cc] - '0');
					if (mask & v)
						return false;
					mask |= v;
				}
			}
			return true;
		};

		for (auto r = 0; r < 9; r += 3) {
			for (auto c = 0; c < 9; c += 3) {
				if (!valid_sub(r, c))
					return false;
			}
		}

		return true;
	}
};

int main()
{
	vector<vector<char>> board = {
		{'.','.','.', '.','5','.', '.','1','.'},
		{'.','4','.', '3','.','.', '.','.','.'},
		{'.','.','.', '.','.','3', '.','.','1'},

		{'8','.','.', '.','.','.', '.','2','.'},
		{'.','.','2', '.','7','.', '.','.','.'},
		{'.','1','5', '.','.','.', '.','.','.'},

		{'.','.','.', '.','.','2', '.','.','.'},
		{'.','2','.', '9','.','.', '.','.','.'},
		{'.','.','4', '.','.','.', '.','.','.'}
	};

	Solution solution;
	cout << solution.isValidSudoku(board) << endl;

	return 0;
}
