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
	int minCostClimbingStairs(vector<int>& cost) {
		vector<int> dp(cost.size()+1, 0);
		int i;

		if (cost.size() < 2)
			return 0;

		//
		// Typical DP case: just try to
		// take each possible step and choose
		// best ones.
		dp[0] = cost[0];
		dp[1] = cost[1];

		for (i = 2; i < cost.size(); i++) {
			dp[i] = min(dp[i-2],dp[i-1]) + cost[i];
		}
		dp[cost.size()] = min(dp[i-1],dp[i-2]);

		return dp[cost.size()];
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{1},
		{1, 100},	// 1
		{0, 2, 2, 1},	// 3
		{10, 15, 20},	// 15
		{1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, // 6
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " << endl <<
			solution.minCostClimbingStairs(nums) << endl;
	}
	return 0;
}
