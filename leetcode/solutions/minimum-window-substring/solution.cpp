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
	string minWindow(string s, string t) {
		// The overall idea is to find
		// first window matching the
		// template, then simply shrink
		// it left until we hit first
		// letter from the template.
		//
		// Then unmark this letter and
		// move right bound finding new
		// window which matches, then
		// simply shrink this window again.
		vector<int> map(256, 0);

		if (s.length() == 0 || t.length() == 0)
			return "";

		for (char c : t)
			map[c]++;

		int l = 0, pos = 0, r = s.length();
		int found_pos = -1, min_len = 1000000;
		int covered = t.length();

		while (pos < r) {
			if (--map[s[pos++]] >= 0)
				covered--;

			while (covered == 0) {
				//
				// Everything is covered,
				// update the minimum.
				if (pos - l < min_len) {
					min_len = pos - l;
					found_pos = l;
				}
				//
				// Shift left bound right,
				// if it touches letter from
				// the template then mark it
				// as to cover on next iterations.
				if (++map[s[l++]] > 0)
					covered++;
			}
		}

		if (found_pos == -1)
			return "";

		return s.substr(found_pos, min_len);
	}
};

int main()
{
	string input[][2] = {
		{"ADOBECODEBANC", "ABC"}, // "BANC"
		{"a", "a"}, // "a"
	};

	Solution solution;
	for (auto& s: input) {
		cout << s[0] << ", " << s[1] << " => " <<
			solution.minWindow(s[0], s[1]) << endl;
	}
	return 0;
}
