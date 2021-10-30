class Solution {
public:
	//
	// Just use known BFS
	int orangesRotting(vector<vector<int>>& grid) {
		queue<pair<int,int>> q;
		int rows = grid.size();
		int cols = grid[0].size();

		vector<vector<int>> dp(rows, vector<int>(cols, 0));

		int nr_fresh = 0;
		int res = 0;


		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (grid[r][c] == 2)
					q.push({r, c});
				else if (grid[r][c] == 1)
					nr_fresh++;
			}
		}

		while (!q.empty()) {
			auto f = q.front();
			q.pop();

			auto r = f.first;
			auto c = f.second;
			int dr, dc;

			res = max(dp[r][c] + 1, res);

			dr = r + 1;
			if (dr < rows && grid[dr][c] == 1) {
                grid[dr][c] = 2;
				q.push({dr, c});
				dp[dr][c] = res;
				nr_fresh--;
			}

			dr = r - 1;
			if (dr >= 0 && grid[dr][c] == 1) {
				grid[dr][c] = 2;
				q.push({dr, c});
				dp[dr][c] = res;
				nr_fresh--;
			}

			dc = c + 1;
			if (dc < cols && grid[r][dc] == 1) {
				grid[r][dc] = 2;
				q.push({r, dc});
				dp[r][dc] = res;
				nr_fresh--;
			}

			dc = c - 1;
			if (dc >= 0 && grid[r][dc] == 1) {
				grid[r][dc] = 2;
				q.push({r, dc});
				dp[r][dc] = res;
				nr_fresh--;
			}
		}

		if (nr_fresh)
			return -1;

		return res == 0 ? 0 : res-1;
	}
};
