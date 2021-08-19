class Solution {
public:
	//
	// Just use BFS to find steps needed.
	void wallsAndGates(vector<vector<int>>& rooms) {
		const int rows = rooms.size();
		const int cols = rooms[0].size();

		if (rows < 2 && cols < 2)
			return;

		const vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		queue<pair<int, int>> q;

		for (auto r = 0; r < rows; r++) {
			for (auto c = 0; c < cols; c++) {
				if (rooms[r][c] == 0)
					q.emplace(r, c);
			}
		}

		while (!q.empty()) {
			auto cell = q.front();
			q.pop();

			for (auto d: dirs) {
				auto r = cell.first + d.first;
				auto c = cell.second + d.second;

				if (r < 0 || c < 0 || r >= rows || c >= cols)
					continue;

				auto delta = rooms[cell.first][cell.second] + 1;
				if (rooms[r][c] <= delta)
					continue;

				rooms[r][c] = delta;
				q.emplace(r, c);
			}
		}
	}
};
