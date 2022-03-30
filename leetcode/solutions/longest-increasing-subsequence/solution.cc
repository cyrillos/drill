#include <algorithm>
#include <iostream>
#include <stack>
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

ostream& operator<<(ostream& out, const vector<vector<char>>& v)
{
	out << '[' << endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << endl;
		out << *it;
	}
	out << endl << ']' << endl;
	return out;
}

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> dp(nums.size(), 1);
		int best = 0;

		//
		// Use DP: try to increas _every_ previous
		// subsequence seen so far. O(n^2) of course.
		for (int i = 1; i < nums.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] > nums[j])
					dp[i] = max(dp[j]+1, dp[i]);
			}
		}

		//
		// Finally scan for best.
		for (int i = 0; i < nums.size(); i++)
			best = max(best, dp[i]);

		return best;

		//
		// Important
		// ---------
		// There is a better version. Since we're not
		// asked to find exact sequence but only the
		// length of the sequence we can use a binary
		// search here. Allocate a new array @d where we
		// collect seen subsequence so far, once we
		// consider a new number in @nums we try to
		// insert it into @d simiraly like we do with
		// insertions sort except instead of real insert
		// we change a suitable number. One can think
		// of it as merging two sorted overlapped arrays.
		//
		// For example we have a sequence [1, 4, 2, 6, 8, 3, 5, 7, 10]
		// which can be split as
		//
		// [1, 4, 6, 8, 10] and [1, 2, 3, 5, 7, 10]
		//
		// Lets merge them once we walk @nums left to right
		// keeping an order
		//
		// (1)  [1]
		// (4)  [1, 4]
		// (2)  [1, 2] (override 4 with 2)
		// (6)  [1, 2, 6]
		// (8)  [1, 2, 6, 8]
		// (3)  [1, 2, 3, 8] (6 -> 3)
		// (5)  [1, 2, 3, 5] (8 -> 5)
		// (7)  [1, 2, 3, 5, 7]
		// (10) [1, 2, 3, 5, 7, 10]
		//
		// This works only because we're not interested in exact
		// numbers but length only, otherwise such trick won't work
		// because we might merge head of one subsequence and tail
		// of another.
	}
};

int main()
{
	vector<int> input[] = {
		{0,3,1,6,2,2,7},	// 3,6,2,7
		{10,9,2,5,3,7,101,18},	// 2,3,7,101
		{0,1,0,3,2,3},		// 0,1,2,3
		{7,7,7,7,7,7,7},	// 7
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << solution.lengthOfLIS(nums) << endl;
	}
	return 0;
}
