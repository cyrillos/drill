class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		int rows = board.size();
		int cols = board[0].size();
		int rows_idx = rows-1;
		int cols_idx = cols-1;

		auto alive_nr = [&](int _r, int _c) {
			int r1 = _r == 0 ? 0 : _r-1;
			int r2 = _r == rows_idx ? _r : _r+1;

			int c1 = _c == 0 ? 0 : _c-1;
			int c2 = _c == cols_idx ? _c : _c+1;
			int rc = 0;

			for (int r = r1; r <= r2; r++) {
				for (int c = c1; c <= c2; c++) {
					if (r == _r && c == _c)
						continue;
				    if (board[r][c] == 1 ||
				        board[r][c] == -1)
					    rc++;
                }
			}
			return rc;
		};

		//
		// Just put special marks while walking
		// over the board. That's simple.
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				int rc = alive_nr(r, c);
				if (rc < 2) {
					// dies
					if (board[r][c] == 1)
						board[r][c] = -1;
				} else if (rc == 2 || rc == 3) {
					// continue been alive
					// or become alive
					if (board[r][c] == 0 && rc == 3) {
						// become alive
						board[r][c] = -2;
					}
				} else if (rc > 3) {
					// dies
					if (board[r][c] == 1)
						board[r][c] = -1;
				}
			}
		}

		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (board[r][c] == -1)
					board[r][c] = 0;
				else if (board[r][c] == -2)
					board[r][c] = 1;
			}
		}
	}
};
