class Solution {
public:
	//
	// An idea is simple: walk on bounds of the maze and
	// find 'O' (opens) then use BFS to mark such paths
	// as visited with '.' symbol, then simply walk the
	// whole maze again and revert '.' back to 'O' where
	// every 'O' inside will be surrounded and can be
	// marked as 'X'.
	//
	// We can use queue here as well but recursion fits
	// just fine.
	//
	int rows, cols;
	void bfs(int r, int c, vector<vector<char>>& board) {
		if (r < 0 || r >= rows || c < 0 || c >= cols)
			return;
		if (board[r][c] != 'O')
			return;
		board[r][c] = '.';
		bfs(r, c-1, board);
		bfs(r, c+1, board);
		bfs(r-1, c, board);
		bfs(r+1, c, board);
	}

	void solve(vector<vector<char>>& board) {
		rows = board.size();
		cols = board[0].size();

		for (auto c = 0; c < cols; c++) {
			if (board[0][c] == 'O')
				bfs(0, c, board);
			if (board[rows-1][c] == 'O')
				bfs(rows-1, c, board);
		}

		for (auto r = 0; r < rows; r++) {
			if (board[r][0] == 'O')
				bfs(r, 0, board);
			if (board[r][cols-1] == 'O')
				bfs(r, cols-1, board);
		}

		//
		// Final pass: revert '.' to 'O' and
		// surround anything else left
		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				if (board[r][c] == '.')
					board[r][c] = 'O';
				else if (board[r][c] == 'O')
					board[r][c] = 'X';
			}
		}
    }
};
