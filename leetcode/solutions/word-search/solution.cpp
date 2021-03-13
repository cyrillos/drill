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

	bool dfs(vector<vector<char>>& board, string& word,
		 int rows, int cols, int wsize, int r, int c,
		 int wpos) {

		if (wpos >= wsize)
			return true;

		//
		// Walk over neighbours to find matches.
		int offs[4][2] = {
			{r+1, c},
			{r-1, c},
			{r, c+1},
			{r, c-1},
		};

		for (int i = 0; i < 4; i++) {
			r = offs[i][0];
			c = offs[i][1];

			if (r < 0 || r >= rows || c < 0 || c >= cols)
				continue;

			auto l = board[r][c];
			if (l != word[wpos])
				continue;

			// Mark as visited
			board[r][c] = '.';
			bool rc = dfs(board, word, rows, cols, wsize,
				      r, c, wpos+1);
			// Restore
			board[r][c] = l;
			if (rc)
				return true;
		}
		return false;
	}

	bool exist(vector<vector<char>>& board, string word) {
		int rows = board.size();
		int cols = board[0].size();
		int wsize = word.size();

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				auto l = board[r][c];
				if (l != word[0])
					continue;

				// Mark as visited
				board[r][c] = '.';
				bool rc = dfs(board, word,
					     rows, cols, wsize,
					     r, c, 1);
				if (rc)
					return rc;
				// Restore
				board[r][c] = l;
			}
		}

		return false;
	}
};

int main()
{
	struct {
		vector<vector<char>> board;
		string word;
	} input[] = {
		{
			// true
			.board = {
				{'A','B','C','E'},
				{'S','F','C','S'},
				{'A','D','E','E'},
			},
			.word = "ABCCED",
		}, {
			// true
			.board = {
				{'A','B','C','E'},
				{'S','F','C','S'},
				{'A','D','E','E'},
			},
			.word = "SEE",
		}, {
			// false
			.board = {
				{'A','B','C','E'},
				{'S','F','C','S'},
				{'A','D','E','E'},
			},
			.word = "ABCB",

		}, {
			// true
			.board = {
				{'C','A','A'},
				{'A','A','A'},
				{'B','C','D'},
			},
			.word = "AAB",
		},
	};
	Solution solution;
	for (auto& d: input) {
		cout << d.board << " , " << d.word << " => " <<
			solution.exist(d.board, d.word) << endl;
	}
	return 0;
}
