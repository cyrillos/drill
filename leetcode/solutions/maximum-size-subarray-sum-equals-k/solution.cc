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
	int maxSubArrayLen(vector<int>& nums, int k) {
		//
		// In idea is pretty simple. Consider
		// an array of integers
		//
		//            0   1   2   3 indices
		//      (1) [a1, a2, a3, a4]
		//
		// and their prefix sum, ie
		//
		//            0      1         2            3
		//      (2) [a1, a1+a2, a1+a2+a3, a1+a2+a3+a4]
		//
		// Assume that k = a2+a3 (indices 1 and 2) then we
		// can rewrite it as
		//
		//            0      1     2        3
		//      (3) [a1, a1+a2, a1+k, a1+k+a4]
		//           ^
		//           `--------------v
		//          [a1-k, a1+a2-k, a1, a1+a4]
		//
		// thus when we traverse the element a1+k we can
		// substract k and reach elemet 0, ie a1+k-k=a1,
		// ie we need to remove a1 from prefix sum to reach
		// the target.
		//
		unordered_map<int,int> m;
		int prefix_sum = 0;
		int max_len = 0;

		for (auto i = 0; i < nums.size(); i++) {
			prefix_sum += nums[i];
			//
			// Strict match, since we're walking
			// left to right it gonna be maximal.
			if (prefix_sum == k)
				max_len = i + 1;

			//
			// In case if current element is ending
			// one of subarray, choose maximal.
			auto prefix = prefix_sum - k;
			if (m.find(prefix) != m.end()) {
				auto l = m[prefix];
				max_len = max(max_len, i - l);
			}

			//
			// Collect prefix sum for fast lookup.
			if (m.find(prefix_sum) == m.end())
				m[prefix_sum] = i;
		}

		return max_len;
	}
};

int main()
{
	struct {
		vector<int> nums;
		int k;
	} input[] = {
		{
			.nums = {1,-1,5,-2,3},
			.k = 3,
		}, {
			.nums = {-2,-1,2,1},
			.k = 1,
		},
	};
	Solution solution;
	for (auto& v: input) {
		cout << v.nums << ", " << v.k << " => " <<
			solution.maxSubArrayLen(v.nums, v.k) << endl;
	}
	return 0;
}
