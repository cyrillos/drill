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
	// Just use recursion and caclulate
	// score via internal calls.
	int score(string& s, int start, int end)
	{
		if (start >= end)
			return 1;

		int v = 0, depth = 0;
		for (auto i = start; i <= end; i++) {
			if (s[i] == '(') {
				depth++;
				continue;
			} else {
				depth--;
				if (depth != 0)
					continue;
			}
			//
			// Either it is () sequence
			// or (AB) sequence, which is
			// handled in recursive calls.
			if (i - start == 1)
				v += 1;
			else
				v += 2 * score(s, start+1, i);
			// next sequcene starts here
			start = i + 1;
		}
		return v;
	}

	int scoreOfParentheses(string s) {
		return score(s, 0, s.size()-1);
	}
};

int main()
{
	vector<string> input = {
		"()",		// 1
		"(())",		// 2
		"()()",		// 2
		"()()()",	// 3
		"((()()))",	// 8
		"(((())))",	// 8
		"()((()))",	// 5
	};
	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.scoreOfParentheses(s) << endl;
	}
	return 0;
}
