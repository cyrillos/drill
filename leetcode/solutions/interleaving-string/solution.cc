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
	//
	// We need to consider all combinations, greedy algo
	// won't work here because of letters order. Thus we
	// use DP to speedup bruteforce.
	bool helper(vector<vector<int>>& memo, string& s1, int i,
		    string& s2, int j, string& s3) {
		int pos = i + j;

		if (pos >= (int)s3.size())
			return i >= (int)s1.size() && j >= (int)s2.size();

		if (memo[i][j] != -1)
			return memo[i][j];

		bool res = false;
		if (i < (int)s1.size() && s1[i] == s3[pos])
			res |= helper(memo, s1, i+1, s2, j, s3);
		if (j < (int)s2.size() && s2[j] == s3[pos])
			res |= helper(memo, s1, i, s2, j+1, s3);
		memo[i][j] = res;
		return res;
	}

	bool isInterleave(string s1, string s2, string s3) {
		size_t sz1 = s1.size();
		size_t sz2 = s2.size();
		size_t sz3 = s3.size();

		if (sz1 + sz2 != sz3)
			return false;
		if (sz3 == 0)
			return true;

		vector<vector<int>> memo(200, vector<int>(200, -1));
		return helper(memo, s1, 0, s2, 0, s3);
	}
};

int main()
{
	struct {
		string s1;
		string s2;
		string s3;
	} input[] = {
		{
			// true
			.s1 = "aabcc",
			.s2 = "dbbca",
			.s3 = "aadbbcbcac",
		}, {
			// false
			.s1 = "aabcc",
			.s2 = "dbbca",
			.s3 = "aadbbbaccc",
		}, {
			// true
			.s1 = "",
			.s2 = "",
			.s3 = "",
		}, {
			.s1 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa",
			.s2 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab",
			.s3 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab",
		}
	};

	Solution solution;
	for (auto& d: input) {
		cout << "s1 = " << d.s1 << " " <<
			"s2 = " << d.s2 << " " <<
			"s3 = " << d.s3 << " => " <<
			solution.isInterleave(d.s1, d.s2, d.s3) << endl;
	}
	return 0;
}
