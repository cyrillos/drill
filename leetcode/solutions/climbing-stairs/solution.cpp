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
	int climbStairs(int n) {
		int dp[n+1];

		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		if (n == 2)
			return 2;

		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 2;

		// Traditional Fib numbers
		for (int i = 3; i <= n; i++)
			dp[i] = dp[i-1] + dp[i-2];

		return dp[n];
	}
};

int main()
{
	int input[] = {
		2,	// 2 => 1+1, 2
		3,	// 3 => 1+1+1, 1+2, 2+1
	};

	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			solution.climbStairs(nums) << endl;
	}
	return 0;
}
