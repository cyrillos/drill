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
	int minSubArrayLen(int target, vector<int>& nums) {
		int found = 1000000;
		int accum = 0;

		//
		// Simple slide window
		for (int l = 0, r = 0; r < (int)nums.size(); r++) {
			accum += nums[r];
			if (accum < target)
				continue;
			// try to shrink the left bound
			while (accum >= target) {
				found = min(found, (r - l) + 1);
				accum -= nums[l++];
			}
		}

		return found == 1000000 ? 0 : found;
	}
};

int main()
{
	struct {
		int target;
		vector<int> nums;
	} data[] = {
		{
			// 2
			.target = 7,
			.nums = {2,3,1,2,4},
		}, {
			// 1
			.target = 4,
			.nums = {1,4,4},
		}, {
			// 0
			.target = 11,
			.nums = {1,1,1,1,1,1,1,1},
		}, {
			// 3
			.target = 11,
			.nums = {1,2,3,4,5},
		}
	};
	Solution solution;
	for (auto& d: data) {
		cout << d.target << ", " << d.nums << " => " <<
			solution.minSubArrayLen(d.target, d.nums) << endl;
	}
	return 0;
}
