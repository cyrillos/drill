#include <algorithm>
#include <iostream>
#include <unordered_map>
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
	vector<string> letterCombinations(string digits) {
		size_t len = digits.length();
		vector<string> res;

		if (len < 1)
			return res;

		int idx[len] = { 0 };
		int pos[len] = { 0 };

		// digits 2-9 maps to
		const string digits_map[] = {
			"abc",	// 2
			"def",	// 3
			"ghi",	// 4
			"jkl",	// 5
			"mno",	// 6
			"pqrs",	// 7
			"tuv",	// 8
			"wxyz",	// 9
		};

		// Fill indices table, for fast lookup
		// inside digits_map
		for (int i = 0; i < len; i++)
			idx[i] = digits[i] - '2';

		while (true) {
			string s;

			//
			// Current combination
			s.reserve(len);
			for (int i = 0; i < len; i++)
				s.push_back(digits_map[idx[i]][pos[i]]);
			res.push_back(move(s));

			// Find the next one
			bool found = false;
			for (int i = len-1; i >= 0; i--) {
				if (pos[i] < digits_map[idx[i]].length()-1) {
					pos[i]++;
					found = true;
					break;
				}
				pos[i] = 0;
			}

			if (!found)
				break;
		}

		return res;
	}
};

int main()
{
	string input[] = {
		"",
		"2",
		"23",
		"67",
		"234",
	};
	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.letterCombinations(s) << endl;
	}
	return 0;
}
