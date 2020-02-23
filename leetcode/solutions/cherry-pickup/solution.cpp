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

#define MEMO_NONE -10000

class Solution {
public:
	int dp(vector<vector<int>>& grid,
	       vector<vector<vector<int>>>& memo,
	       size_t r1, size_t c1, size_t c2)
	{
		size_t nr = grid.size();
		//
		// 1) instead of walking two path consider
		//    the case where two walkers are moving
		//    from (0,0) to (nr-1,nr-1) position
		//
		// 2) there are 2 * (nr-1) steps from start
		//    to end; you may consider the step is
		//    row plus col, ie t = r + c (indeed,
		//    one step either horizontal or vertical)
		//
		//    once step is choosen the position of the
		//    second walker is known:
		//
		//	t = r1+c1 = r2+c2 (because we're walking
		//	on same grid simultaneously)
		//
		//    thus if we have r1,c1,c2 choosen
		//
		//	r2 = r1+c1-c2
		//
		// 3) memo[r1][c1][c2] is max number of cherries
		//    when two walkers passed from 0,0 to r1,c1 / r2,c2
		//
		// 4) once we find max value at pair r1,c1 / r2,c2
		//    we can try all other ways down (4 ways, see below)
		//
		size_t r2 = r1 + c1 - c2;

		//
		// if we're are over the bounds or
		// meet a thorn return NONE, note we
		// don't care which person hit it since
		// only if both can walk we find a path,
		// all other path are considered below
		if (nr == r1 || nr == r2 ||
		    nr == c1 || nr == c2 ||
		    grid[r1][c1] == -1 ||
		    grid[r2][c2] == -1)
			return MEMO_NONE;

		//
		// if we're at the end point return it
		if (r1 == nr-1 && c1 == nr-1)
			return grid[r1][c1];

		//
		// if we know the max number of
		// the cherries already
		if (memo[r1][c1][c2] != MEMO_NONE)
			return memo[r1][c1][c2];

		//
		// don't account same cherry twice
		// if both walks are on same cell.
		// otherwise accume they are at positions
		// (r1,c1) (r2,c2) where either empty
		// place or cherry. it is enough to compare
		// either r's or c's since we can't move
		// diagonally
		int ans = grid[r1][c1] + (c1 != c2) * grid[r2][c2];

		//
		// from pair r1/c1, r2/c2 we can walk 4 ways
		// 1) person 1 moves right, person 2 moves right =>
		//    r1, c1+1, c2+1
		// 2) person 1 moves  down, person 2 moves right =>
		//    r1+1, c1, c2+1
		// 3) person 1 moves right, person 2 moves  down =>
		//    r1, c1+1, c2
		// 4) person 1 moves  down, person 2 moves  down =>
		//    r1+1, c1, c2

		ans += max(this->dp(grid, memo, r1, c1+1, c2+1),
			   max(this->dp(grid, memo, r1+1, c1, c2+1),
			       max(this->dp(grid, memo, r1, c1+1, c2),
				   this->dp(grid, memo, r1+1, c1, c2))));

		memo[r1][c1][c2] = ans;
		return ans;
	}

	int cherryPickup(vector<vector<int>>& grid) {
		size_t nr = grid.size();
		vector<vector<vector<int>>> memo(nr,
			vector<vector<int>>(nr,
			vector<int>(nr, MEMO_NONE)));

		return max(0, this->dp(grid, memo, 0, 0, 0));
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{
				{0, 1, -1},
				{1, 0, -1},
				{1, 1,  1},
			},	// => 5
		},
	};

	Solution solution;
	for (auto& grid: input) {
		cout << grid << " => " << solution.cherryPickup(grid) << endl;
	}
	return 0;
}
