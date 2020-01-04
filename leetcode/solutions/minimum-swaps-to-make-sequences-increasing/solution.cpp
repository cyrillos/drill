#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>

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
	int minSwap(const vector<int>& a, const vector<int>& b) {
		//
		// @cost_no_swap
		// 	the cost of making i-1 column increasing
		// 	and not swapping ith column
		//
		// @cost_do_swap
		// 	the cost of making i-1 column increasing
		// 	and swapping ith column

		//
		// The first entry has no data before thus
		// we only may swap ith column
		int cost_no_swap = 0;
		int cost_do_swap = 1;

		int ith_no_swap;
		int ith_do_swap;

		for (size_t i = 1; i < a.size(); i++) {
			//
			// In case of hit it means both columns
			// are in natural order, ie increasing.
			// Thus to keep them so we either do not
			// touch them (@cost_no_swap remains the same)
			// or swap ith entry together with all previous
			// (@cost_do_swap increased).
			if (a[i-1] < a[i] && b[i-1] < b[i]) {
				ith_no_swap = cost_no_swap;
				ith_do_swap = cost_do_swap + 1;
			} else {
				ith_no_swap = INT_MAX;
				ith_do_swap = INT_MAX;
			}

			//
			// If ith iteration can be swapped (or must
			// be swapped, in this case previous if() won't
			// hit) then we should consider two subcases:
			//
			// a) The if() above didn't hit and we must
			// swap ith pair, then @ith_no_swap = INT_MAX
			// and @ith_do_swap = INT_MAX which leads to
			// the conclusion
			//
			// @ith_no_swap = @cost_do_swap
			// 	ie if we don't swap ith we have to swap
			// 	all previous entries thus the cost of not
			// 	swapping ith entry is same as swapping all
			// 	previous entries
			//
			//  @ith_do_swap = @cost_no_swap+1
			//	if we swap the entry then it simply increase
			//	the previous swap counter
			//
			// b) The if() above hit and swap of ith pair is
			// optional and we'are allowed to switch one of the
			// column (current or previous [the previous implies
			// all previous where counters are propagated via DP
			// to previous values])
			//
			//  @ith_no_swap = min(cost_no_swap, cost_do_swap)
			//	not swapping is the min between swapping
			//	or not swapping previous column
			//
			//  @ith_do_swap = min(cost_do_swap+1, cost_no_swap+1)
			//	swapping is the min between swapping or
			//	not swapping current column
			//
			if (a[i-1] < b[i] && b[i-1] < a[i]) {
				ith_no_swap = min(ith_no_swap, cost_do_swap);
				ith_do_swap = min(ith_do_swap, cost_no_swap + 1);
			}

			cost_no_swap = ith_no_swap;
			cost_do_swap = ith_do_swap;
		}

		return min(cost_do_swap, cost_no_swap);
	}
};

int main()
{
	struct in_data {
		vector<int> a;
		vector<int> b;
	} input[] = {
		{
			// swap a[3], b[3]
			// 1, 3, 5, 7
			// 1, 2, 3, 4
			.a = {1, 3, 5, 4},
			.b = {1, 2, 3, 7}, // 1
		}, {
			.a = {0, 4, 4, 5, 9},
			.b = {0, 1, 6, 8, 10}, // 1
		}, {
			.a = {0, 4, 4},
			.b = {0, 1, 6},
		},
	};

	Solution solution;
	for (auto& nums: input) {
		cout << nums.a << " " << nums.b << " => "
			<< solution.minSwap(nums.a, nums.b) << endl;
	}
	return 0;
}
