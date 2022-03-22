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

class Solution {
public:
	//
	// Greedy algo won't work because local maximum may force us
	// to skip another maximum (because mults and nums are unordered).
	// For example
	//
	// [2,3,4] nums
	// [1,4,3] mults
	//
	// for greedy we have  1*4 + 4*3 + 3*2 = 22
	// while better to get 1*2 + 4*4 + 3*3 = 27
	//
	// Thus we need to consider _all_ possible combintaions.
	// For this sake lets use top down DP with memoization.
	//
	int dp(vector<vector<int>>& memo, vector<int>& nums, vector<int>& mults, int i, int l, int r) {
		if (i >= (int)mults.size())
			return 0;

		//
		// Already been seen (we use @l as parameter because
		// use use left recursion first).
		if (memo[l][i] != -1)
			return memo[l][i];

		//
		// Take left nums value and continue recursively,
		// thus we consider all left values down the calls.
		// Then when we exit from recursion we start taking
		// right values at every exit.
		auto left = mults[i] * nums[l] + dp(memo, nums, mults, i+1, l+1, r);

		//
		// Take right nums value and continue recursively. Some
		// of left taken values get already seen and reused from
		// memo.
		auto right = mults[i] * nums[r] + dp(memo, nums, mults, i+1, l, r-1);

		memo[l][i] = max(left, right);
		return memo[l][i];
	}

	int maximumScore(vector<int>& nums, vector<int>& multipliers) {
		vector<vector<int>> memo(1000, vector<int>(1000, -1));
		return dp(memo, nums, multipliers, 0, 0, nums.size()-1);
	}
};

int main()
{
	struct {
		vector<int> nums;
		vector<int> multipliers;
	} input[] = {
		{
			// output = 14
			.nums = {1,2,3},
			.multipliers = {3,2,1},
		}, {
			// output = 27
			.nums = {2,3,4},
			.multipliers = {1,4,3},
		}, {
			// output = 102
			.nums = {-5,-3,-3,-2,7,1},
			.multipliers = {-10,-5,3,4,6},
		},
	};
	Solution solution;
	for (auto& n: input) {
		cout << n.nums << ", " << n.multipliers << " => " <<
			solution.maximumScore(n.nums, n.multipliers) << endl;
	}
	return 0;
}
