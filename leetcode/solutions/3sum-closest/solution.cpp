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
	int threeSumClosest(vector<int>& nums, int target) {
		int best = 10000000;

		//
		// Key moment to work on sorted data: searching.
		sort(nums.begin(), nums.end());

		//
		// This is gonna be O(n^2) algo
		//
		// num1 num2 num3 num4
		// ^    ^         ^
		// pos  i         j
		//
		for (ssize_t pos = 0; pos < (ssize_t)nums.size() - 2; pos++) {
			ssize_t j = nums.size() - 1;
			ssize_t i = pos + 1;

			//
			// Iterate from [i:j] range with pos fixed
			while (i < j) {
				int sum = nums[pos] + nums[i] + nums[j];
				//
				// found exact
				if (sum == target)
					return target;

				//
				// figure out the minimum delta
				if (abs(sum - target) < abs(best - target))
					best = sum;

				// if we're positive, go left,
				// otherwise step right
				if (sum - target > 0)
					j--;
				else
					i++;
			}
		}

		return best;
	}
};

int main()
{
	struct {
		vector<int> nums;
		int target;
	} s[] = {
		{
			// 2 =>		vector<vector<int>> res;
			.nums = { -1, 2, 1, -4, },
			.target = 1,
		},
		{
			// 82
			.nums = { 1,2,4,8,16,32,64,128 },
			.target = 82,
		},
	};
	Solution solution;
	for (auto& v: s) {
		cout << v.nums << ", " << v.target << " => " <<
			solution.threeSumClosest(v.nums, v.target) << endl;
	}
	return 0;
}
