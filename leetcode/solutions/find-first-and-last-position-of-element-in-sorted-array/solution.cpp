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
	vector<int> searchRange(vector<int>& nums, int target) {
		auto bsearch = [&](vector<int>& n, int lo, int hi, int v) {
			while (lo <= hi) {
				int pos = (lo + hi) / 2;
				if (n[pos] < v)
					lo = pos+1;
				else if (n[pos] > v)
					hi = pos-1;
				else
					return pos;
			}
			return -1;
		};

		int lo = 0, hi = nums.size() - 1;
		if (lo > hi)
			return {-1, -1};
		if (nums[lo] > target && nums[hi] < target)
			return {-1, -1};
		if (hi == 0) {
			if (target == nums[0])
				return {0,0};
			else
				return {-1,-1};
		}

		int s = -1, e = -1;
		int pos = bsearch(nums, lo, hi, target);
		if (pos == -1)
			return {-1, -1};
		// lookup for a lower bound
		s = e = pos;
		while ((pos = bsearch(nums, lo, pos-1, target)) != -1)
			s = pos;
		// lookup for an upper bound
		pos = e;
		while ((pos = bsearch(nums, pos+1, hi, target)) != -1)
			e = pos;

		return {s, e};
	}
};

int main()
{
	struct {
		vector<int> nums;
		int target;
	} d[] = {
		{
			.nums = {5,7,7,8,8,10},
			.target = 8,	// => 3,4
		}, {
			.nums = {1},
			.target = 1,	// => 0,0
		}, {
			.nums = {5,7,7,8,8,10},
			.target = 6,	// => -1,-1
		}, {
			.nums = {5,7,7,8,8,10},
			.target = 4,	// => -1,-1
		}, {
			.nums = {5,7,7,7,7,8,8,8,8,10,10,10},
			.target = 5,	// => 0,0
		}, {
			.nums = {5,7,7,7,7,8,8,8,8,10,10,10},
			.target = 10,	// => 9,11
		}
	};
	Solution solution;
	for (size_t i = 0; i < sizeof(d)/sizeof(d[0]); i++) {
		cout << d[i].nums << ", " << d[i].target << " => "
			<< solution.searchRange(d[i].nums, d[i].target) << endl;
	}
	return 0;
}
