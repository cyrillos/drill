#include <iostream>

using namespace std;

class Solution {
public:
	bool isRobotBounded(string s) {
		const int step[4][2] = {
			{ 0,  1 },	// move north
			{ 1,  0 },	// move east
			{ 0, -1 },	// move south
			{-1,  0 },	// move west
		};
		// initial position
		int x = 0, y = 0;
		// points to north
		int direction = 0;

		//
		// It is enough to play the steps and figure
		// out if we're at the same point we've been
		// starting from (0,0) or we're *not* pointing
		// to the north (ie same direction as we've been
		// starting from).
		//
		// While first case is obvious, the second one
		// is not so. But here is a rationale: any other
		// direction will be a part of a symmetry group
		// (can consider it as a circle segment).

		for (size_t i = 0; i < s.length(); i++) {
			switch (s[i]) {
			case 'G':
				x += step[direction][0];
				y += step[direction][1];
				break;
			case 'L':
				direction = (direction + 3) % 4;
				break;
			case 'R':
				direction = (direction + 1) % 4;
				break;
			}
		}
		return (x == 0 && y == 0) || direction != 0;
	}
};

int main()
{
	string input[] = {
		"GGLLGG",	// true
		"GG",		// false
		"GL",		// true
		"LLRR",		// true
		"GRGR",
	};
	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.isRobotBounded(s) << endl;
	}
	return 0;
}
