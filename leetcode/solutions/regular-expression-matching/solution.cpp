#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	bool isMatch(string s, string t) {
		vector<vector<bool>> dp(s.size()+1, vector<bool>(t.size()+1, false));

		// both strings are empty
		dp[0][0] = true;

		//
		// Lets use DP approach. Here is an example
		//
		//  text = xaabyc (name it s)
		//  patt = xa*b.c (name it t)
		//
		//       0 | x | . | * | b |
		//     +===+===+===+===+===+
		//   0 | t | f | f | f | f |
		//   --+--------------------
		//   x | f | t | f |-2t| f |
		//   --+--------------------
		//   a | f | f | t |-1t| f |
		//   --+--------------------
		//   x | f | f | f |-1t| f |
		//   --+--------------------
		//   b | f | f | f |-1t| t |
		//   --+--------------------
		//
		//   a) 0/0 - matches empty text and pattern,
		//      for this sake we count them from index 1 (!!!)
		//
		//   b) when s[i] = t[j] it is the same as removing
		//      this entry from s and from t, thus we need
		//      to propagate diagonal dp[i][j] = dp[i-1][j-1]
		//
		//   c) when t[j] = '.' it is the same as b)
		//
		//   d) when t[i] = '*' we should consider cases
		//
		//      1) can we drop '*' and previous letter, ie
		//         zero occurance
		//
		//         dp[i][j] = d[i][j-2]
		//
		//         this should be applied to zero source length
		//         as initial cycle
		//
		//      2) can we propagate previous letter, ie one
		//         an more occurences
		//
		//         dp[i][j] = dp[i-1][j]
		//
		//      3) if previous letter in template is '.' it
		//         is the same as 2)
		//

		// Mark table for zero column where we could
		// remove (w*) which would match to empty string.
		for (size_t j = 0; j < t.size(); j++) {
			if (t[j] == '*')
				dp[0][j+1] = dp[0][j-1];
		}

		for (size_t i = 0; i < s.size(); i++) {
			size_t ii = i+1;
			for (size_t j = 0; j < t.size(); j++) {
				size_t jj = j+1;
				if (s[i] == t[j] || t[j] == '.') {
					dp[ii][jj] = dp[ii-1][jj-1];
				} else if (t[j] == '*') {
					if (dp[ii][jj-2] == true) {
						dp[ii][jj] = true;
					} else if (s[i] == t[j-1] || t[j-1] == '.') {
						dp[ii][jj] = dp[ii-1][jj];
					} else
						dp[ii][jj] = false;
				} else {
					// mismatch
					dp[ii][jj] = false;
				}
			}
		}

		return dp[s.size()][t.size()];
	}
};

int main()
{
	string input[][2] = {
		{"", ""},			// true
		{"a", ""},			// false
		{"", ".*"},			// true
		{"aa", "a*"},			// true
		{"abcd", "a.c."},		// true
		{"abbbcb", "ab.*" },		// true
		{"12345", "12.*345"},		// true
		{"12345", "12.*6"},		// false
		{"12345", "12.*5"},		// true
		{"aaabc", "a*bc"},		// true
		{"aab", "c*a*b"},		// true
		{"mississippi", "mis*is*p*."},	// false
		{"aaa", "a*a"},			// true
		{"a", ".*a"},
		{"a", ".*b"},
		{"aaa", ".*a"},			// true
	};
	Solution solution;
	for (auto& s: input) {
		cout << s[0] << " , " << s[1] << " " << " => " <<
			solution.isMatch(s[0], s[1]) << endl;
	}
	return 0;
}
