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

class Solution {
public:
	int trapRainWater(vector<vector<int>>& heightMap) {
		ssize_t nr_rows = heightMap.size();
		ssize_t nr_cols = nr_rows ? heightMap[0].size() : 0;
		int accum = 0;

		//
		// At least we must have a one cell
		// surrounded by 8 others.
		if (nr_cols < 3 || nr_rows < 3)
			return 0;

		struct cell {
			int row, col;
			int height;

			cell(int _row, int _col, const vector<vector<int>>& _map) :
				row(_row), col(_col), height(_map[_row][_col]) { }
		};

		auto cmp = [&](const cell& c1, const cell& c2) {
			return c1.height > c2.height;
		};

		vector<vector<bool>> visited;
		vector<cell> heap;

		visited.resize(nr_rows, vector<bool>(nr_cols));

		//
		// Walk the walls first since they are the bounds,
		// and can't keep the water on their own.
		for (ssize_t i = 0; i < nr_cols; i++) {
			heap.emplace_back(0, i, heightMap);
			heap.emplace_back(nr_rows - 1, i, heightMap);
			visited[0][i] = true;
			visited[nr_rows - 1][i] = true;
		}
		for (ssize_t i = 1; i < nr_rows - 1; i++) {
			heap.emplace_back(i, 0, heightMap);
			heap.emplace_back(i, nr_cols - 1, heightMap);
			visited[i][0] = true;
			visited[i][nr_cols - 1] = true;
		}

		//
		// Make a min heap from bounds.
		make_heap(heap.begin(), heap.end(), cmp);

		//
		// Initial minimal height should be less
		// than any other value.
		int min_height = -1;

		auto visit = [&](int row, int col) {
			if (!visited[row][col]) {
				visited[row][col] = true;
				heap.emplace_back(row, col, heightMap);
				push_heap(heap.begin(), heap.end(), cmp);
			}
		};

		//
		// Now the core algo: we use bfs from the cell
		// which has the minimal height, if its value is
		// less than current minimal found so far it means
		// all arounds are greater and we can accumulate
		// water. In turn if we found some higher value
		// it become a new bound over which water should
		// not overflow.
		//
		// Strictly speaking we're looking for path from
		// some low point climbing upward for this sake
		// the min heap is used.
		while (!heap.empty()) {
			pop_heap(heap.begin(), heap.end(), cmp);
			auto cell = heap.back();
			heap.pop_back();

			if (cell.height < min_height)
				accum += min_height - cell.height;
			else
				min_height = cell.height;

			if (cell.row > 0)
				visit(cell.row - 1, cell.col);
			if (cell.row < nr_rows - 1)
				visit(cell.row + 1, cell.col);
			if (cell.col > 0)
				visit(cell.row, cell.col - 1);
			if (cell.col < nr_cols - 1)
				visit(cell.row, cell.col + 1);
		}

		return accum;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{1, 4, 3, 1, 3, 2},
			{3, 2, 1, 3, 2, 4},
			{2, 3, 3, 2, 3, 1},		// => 4
		}, {
			{2, 2, 3, 4},
			{2, 1, 1, 3},
			{2, 2, 2, 3},
			{2, 3, 3, 3},			// => 2
		},
	};
	Solution solution;
	for (auto& nums: input) {
		auto res = solution.trapRainWater1(nums);
		cout << nums << " => " << res << endl;
	}
	return 0;
}
