#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

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
	int numDecodings(string s) {
		int len = s.size();
		vector<int> dp(len+1);
		dp[len] = 1;

		if (len < 1)
			return 0;

		//
		// Traditional DP task: accumulate
		// number of splits. In case if current
		// number is 1 | 2[<=6] then it means we
		// can split the number into two as one
		// digit combination and two digit.
		for (auto i = len-1; i >= 0; i--) {
			// Unsplittable
			if (s[i] == '0') {
				dp[i] = 0;
				continue;
			}

			// Remember current combination.
			dp[i] = dp[i+1];
			if (i < len-1) {
				//
				// If we're splittable number then
				// augment with combination from
				// previous pair.
				if (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6'))
					dp[i] += dp[i + 2];
			}
		}

		return dp[0];
	}
};

int main()
{
	string input[] = {
		"",		// 0: {},
		"1212",		// 5: {1,2,1,2},{12,1,2},{1,21,2},{1,2,12},{12,12}
		"1010",		// 1: {10,10}
	        "10",		// 1: {10},
		"12120",	// 3: {1,2,1,20},{12,1,20},{1,21,20}
		"00",		// 0: {},
		"22200",	// 0: {},
		"5050",		// 0: {},
		"101011",	// 2: {10,10,1,1},{10,10,11}
		"010",		// 0: {},
		"100",		// 0: {}
		"101",		// 1: {10,1}
		"110",		// 1: {1,10}
		"10",		// 1: {10}
		"1",		// 1: {1},
		"10",		// 1: {10},
		"43",		// 1: {4,3},
		"12",		// 2: {1,2}, {12}
		"226",		// 3: {2,2,6}, {22, 6}, {2, 26}
		"2022",		// 2: {20, 2, 2}, {20, 22}
		"17",		// 2: {1,7}, {17}
		"27",		// 1: {2,7}
		"31",		// 1: {3,1}
		"227",		// 2: {2,2,7}, {22,7}
		"231",		// 2: {2,3,1}, {23,1}
		"1010",		// 1: {10,10}
	};

	Solution solution;
	for (auto& s: input)
		cout << s << " => " << solution.numDecodings(s) << endl;
	return 0;
}
