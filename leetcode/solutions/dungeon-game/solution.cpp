#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include<bits/stdc++.h>

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

static void show(vector<vector<int>>& dungeon)
{
	return;
	for (size_t r = 0; r < dungeon.size(); r++) {
		for (size_t c = 0; c < dungeon[0].size(); c++) {
			printf("s: %5d ", dungeon[r][c]);
		}
		printf("\n");
	}
	printf("\n---\n");
}

class Solution {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int nr_rows = dungeon.size();
		int nr_cols = dungeon[0].size();

		//
		// Start from the reverse: find out which minimal
		// HP needed at the end point. If value is already
		// a positive number then the minimum needed at this
		// point is 1; if value is negative invert it and
		// add 1 to be sure we have the minimum value once
		// we would reach this point.
		dungeon[nr_rows-1][nr_cols-1] =
			max(-dungeon[nr_rows-1][nr_cols-1], 0) + 1;

		//
		// Next walk over every possible way and keep
		// in mind that we can use max(a-b,1) formula,
		// where is `a` is the value required on previous
		// step and `b` is the value of the current cell. If
		// `b` is positive and less then `a` we can simply
		// decrease it, if it is negative we will have
		// new value to be raised up the way we won't die.
		//
		// For example
		//  -2  -3    3
		//  -5  -10   1
		//  10   30  -5
		//
		// Manually we know that the best path is
		//
		// x  x  x
		//       x
		//       x
		//
		// So we will have
		//
		//   7 5 2
		//       5
		//       6
		//
		// Lets see to the following path
		//
		// x
		// x
		// x x x
		//
		// We will have (taking the formula above)
		//
		//   8
		//   6
		//   1 1 6

		//
		// Fill corner lines.
		for (int r = nr_rows-2, c = nr_cols-1; r >= 0; r--)
			dungeon[r][c] = max(dungeon[r+1][c] - dungeon[r][c], 1);
		for (int c = nr_cols-2, r = nr_rows-1; c >= 0; c--)
			dungeon[r][c] = max(dungeon[r][c+1] - dungeon[r][c], 1);

		for (int r = nr_rows-2; r >= 0; r--) {
			for (int c = nr_cols-2; c >= 0; c--) {
				int a = max(dungeon[r][c+1] - dungeon[r][c], 1);
				int b = max(dungeon[r+1][c] - dungeon[r][c], 1);

				dungeon[r][c] = min(a, b);
				show(dungeon);
			}
		}

		// To handle a case where only one cell present
		return dungeon[0][0] > 0 ? dungeon[0][0] : 1;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{0}}, // 1
		{{1}}, // 1
		{{-1}}, // 2
		{{-1, 1, 1}}, // 2
		{{-1, -1, 10}}, // 3
		{{-1, -1, -1}}, // 4
		{
			{10, -100, 1000},
			{10, 100, -1000},
		}, // 91		
		{
			{ -2,  -3,  3 },
			{ -5, -10,  1 },
			{ 10,  30, -5 },
		}, // right -> right -> down -> down = 7
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << endl <<
			solution.calculateMinimumHP(nums) << endl;
	}
	return 0;
}
