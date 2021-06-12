#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <cassert>

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
	int brute_force(vector<int>& h) {
		int best = h[0];

		//
		// Brute force approach:
		//
		// - take each entry
		// - walk left while height is ge than entry
		// - walk right while height is ge than entry
		//
		// these generate max _horizontal_ rectangle
		// we can accumulate
		//
		//         +===+
		//         |   |
		// +===+   |   |
		// |   |   |   |
		// +~~~+===+~~~+
		// |   | x |   | entry 1: vertical 1, horizontal 3
		// +---+---+---+
		//   0   1   2
		//
		// IOW, each histogram entry might be considered as a
		// single _vertical_ rectangle, or as a part of horizontal
		// rectanle it forms with entries from left and right (if
		// left and right entries has greater or equal height).
		//
		// Thus simply consider _each_ entry. This is O(N^2) algo.

		for (ssize_t i = 0; i < (int)h.size(); i++) {
			int acc = h[i];
			for (ssize_t j = i-1; j >= 0; j--) {
				if (h[j] >= h[i])
					acc += h[i];
				else {
					// No need to continue
					// since if entry is lower
					// then it will be calculated
					// on next main for(i) iteration.
					break;
				}
			}
			for (ssize_t j = i+1; j < (int)h.size(); j++) {
				if (h[j] >= h[i])
					acc += h[i];
				else
					break;
			}
			best = max(best, max(acc, h[i]));
		}

		return best;
	}

	int stack_based(vector<int>& height) {
		//
		// When bars are traversed then we should only
		// consider i'th height _and_ max horizontal bars
		// formed by bars from left of the current entry.
		//
		// For example for bar 3 we have the following
		// combinations
		//
		//       +--+         +--+         +--+
		//       |YY|         |  |         |  |
		//    +--+  |      +--+  |      +--+  |
		//    |  |YY|      |YY|YY|      |  |  |
		// +--+  |  |   +--+  |  |   +--+  |  |
		// |  |  |YY|   |  |YY|YY|   |YY|YY|YY|
		// +--+--+--+   +--+--+--+   +--+--+--+
		//     a)           b)           c)
		//
		// which means we can stack each bar one after
		// another until bars are ended or there some
		// lower bar from the right. Note that there
		// is no a simple way - we *have* to calculate
		// any possible areas to find the maximal one.
		//
		// Assume we've a draw
		//
		//         top=4
		//         +---+
		//         |   |
		//     +---+   |
		//     |   |   +---+
		// +---+   |   |   |
		// |   |   |   |   |
		// +---+---+---+---+
		//   0   1   2   3
		//
		// Entries {0,1,2} are ascending, so we push them
		// on a stack and when we meet position 3, then
		// we can stop and investigate the range {1,2,3}
		// (excluding 0 because its height is lower than 3).
		//
		// Then we start poping stack merging bars 2 and
		// 3 trying to find a maximum area (here is all
		// possbile combinations)
		//
		//         +---+             +---+             +---+
		//         | Y |             |   |             |   |
		//     +---+ Y |         +---+   |         +---+   |
		//     |   | Y +---+     | Y |   +---+     | Y | Y +---+
		// +---+   | Y |   | +---+ Y |   |   | +---+ Y | Y |   |
		// |   |   | Y |   | |   | Y |   |   | |   | Y | Y |   |
		// +---+---+---+---+ +---+---+---+---+ +---+---+---+---+
		//   0   1   2   3     0   1   2   3     0   1   2   3
		//
		// Once area is found we can think as {1,2} is merged with {3}
		//         
		//     ````````+---+
		// +---+       |   |
		// |   |       |   |
		// +---+---+---+---+
		//   0   1   2   3
		//
		// Then we try to merge the rectangles remaining, so at the
		// end we will have all rectangles (including merged)
		// are ascending (or equal height).
		//
		// A special case where height of bar is zero, say
		//
		//         +---+
		//         |   |
		//     +---+   |
		//     |   |   +   +---+
		// +---+   |   |   |   |
		// |   |   |   |   |   |
		// +---+---+---+---+---+
		//   0   1   2   3   4
		//
		// when we reach idx 3 we pop _all_ entries from the
		// stack since there is nothing less the zero behind.
		// And left position set to -1 once we reach idx 0,
		// because bar at pos 3 _won't_ be used itself in height
		// calculation and can't be merged with previous bars
		// thus merged length is shorter by 1.
		//

		int best = 0, n = height.size();
		stack<int> idx;

		for (int i = 0; i < n; i++) {
			while (!idx.empty() && height[i] < height[idx.top()]) {
				int h = height[idx.top()];
				idx.pop();

				int j = idx.empty() ? -1 : idx.top();
				best = max(best, h * (i - j - 1));
			}
			idx.push(i);
		}

		//
		// Now all rectangles are ascending or equals,
		// so we can walk back and calculate the max areas. 

		while (!idx.empty()) {
			int h = height[idx.top()];
			idx.pop();

			int j = idx.empty() ? -1 : idx.top();
			best =  max(best, h * (n - j - 1));
		}

		return best;
	}

	int largestRectangleArea(vector<int>& height) {
		int res1 = brute_force(height);
		int res2 = stack_based(height);
		assert(res1 == res2);
		return res2;
	}
};

int main()
{
	vector<int> input[] = {
		{4,2,0,3,2,5},		// 6
		{0},
		{1},
		{1,1},
		{1,3,4,2},		// 6
		{1,2,3},		// 4
		{3,2,1},		// 4
		{2,1,5,6,2,3},		// 10
		{2,4},			// 4
		{1,2,3,4,2,3,1},	// 10
	};

	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.largestRectangleArea(nums) << endl;
	}
	return 0;
}
