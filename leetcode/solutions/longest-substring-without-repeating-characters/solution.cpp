#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#include <cstring>

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

ostream& operator<<(ostream& out, const vector<vector<char>>& v)
{
	out << '[' << endl;
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << endl;
		out << *it;
	}
	out << endl << ']' << endl;
	return out;
}

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		int acc = 0, best = 0;
		int pos[256] = { 0 };

		if (s.size() < 2)
			return s.size();

		for (int i = 0, head = 0; i < s.size(); i++) {
			acc++;
			if (++pos[s[i]] == 1) {
				best = max(best, acc);
				continue;
			}

			// Zap the head, we need a new
			// range of characters
			while (pos[s[i]] > 1) {
				int ch_head = s[head++];
				pos[ch_head]--;
				acc--;
			}
		}
		return best;
	}
};

int main()
{
	string input[] = {
		"abcabcbb",	// 3
		"bbbbb",	// 1
		"pwwkew",	// 3
		"aab",		// 2
		"cdd",		// 2
		"abba",		// 2
	};

	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.lengthOfLongestSubstring(s) << endl;
	}
	return 0;
}
