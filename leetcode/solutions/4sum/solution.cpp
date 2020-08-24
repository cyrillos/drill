#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

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
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> res;
		int n = nums.size();

		//
		// Nothing to handle
		if (n < 4)
			return { };

		//
		// Sort in ascending order, this is
		// important for binary search
		sort(nums.begin(), nums.end());

		//
		// The idea is to walk for every number
		// left to right and try to create a quadraplet.
		//
		// We fix first element position at @i, then
		// we iterate over subgroup starting from position
		// @j = @i + 1 and try to find a pair of elements with
		// sum required start from @j + 1. And so on.
		//
		for (int i = 0; i < n - 3; i++) {
			//
			// Skip repeating since we need
			// a unique quadraplet
			if (i > 0 && nums[i] == nums[i - 1])
				continue;

			//
			// Four sequential numbers are overflowing
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
				break;

			//
			// First and last three numbers are underflowing
			if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
				continue;

			//
			// Fix the first number position
			// and scan for three left
			for (int j = i + 1; j < n - 2; j++) {
				//
				// Skip repeating since we need
				// a unique quadraplet
				if (j > i + 1 && nums[j] == nums[j - 1])
					continue;

				//
				// Head is overflowing
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
					break;

				//
				// Tail is underflowing
				if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
					continue;

				//
				// Both @i and @j are fixed now lets try
				// to find required sum of two elements in
				// the tail of the sequence using binary search.
				int lo = j + 1, hi = n - 1;
				int sum_ij = nums[i] + nums[j];
				while (lo < hi) {
					int sum = nums[lo] + nums[hi] + sum_ij;
					if (sum < target) {
						lo++;
					} else if (sum > target) {
						hi--;
					} else {
						res.push_back({nums[i], nums[j], nums[lo], nums[hi]});

						// Skip repeating from left
						do {
							lo++;
						} while (nums[lo] == nums[lo - 1] && lo < hi);

						// Skip repeating from right
						do {
							hi--;
						} while (nums[hi] == nums[hi + 1] && lo < hi);
					}
				}
			}
		}

		return res;
	}
};

int main()
{
	struct {
		vector<int> nums;
		int target;
	} input[] = {
		{
			.nums = {-2, -1, 0, 1, 2},
			.target = 0,
		}, {
			.nums = {1, 0, -1, 0, -2, 2},
			.target = 0,
		}, {
			.nums = {1, 2, 3},
			.target = 6,
		}, {
			.nums = {1, 2, 3, 4},
			.target = 8,
		}, {
			.nums = {1, 2, 3, 4},
			.target = 10,
		}, {
			.nums = {1, 1, 1, 1, 1, 1},
			.target = 4,
		}, {
			.nums = {-3,-1,0,2,4,5}, // [[-3,-1,0,4]]
			.target = 0,
		}, {
			.nums = {-5,-4,-3,-2,-1,0,0,1,2,3,4,5},
			.target = 0,
		},
	};
	Solution solution;
	for (auto& n: input) {
		cout << n.nums << ", " << n.target << " => " <<
			solution.fourSum(n.nums, n.target) << endl;
	}
	return 0;
}
