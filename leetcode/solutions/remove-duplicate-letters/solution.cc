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
	string removeDuplicateLetters(string s) {
		vector<int> freq(26, 0);
		vector<int> visited(26, 0);
		string res;
		int v;

		auto opcode = [&](const char c) {
			return c - 'a';
		};

		//
		// An idea is following:
		// 1) walk over the whole string and figure
		// out an amount of each letter
		// 2) start collecting char by char, once
		// order is violated test if previous letters
		// can be dropped of (they can if there are more
		// same letters in suffix). Once we put letter
		// in place we should mark it as present in result
		// and skip later occurences.

		for (size_t i = 0; i < s.size(); i++) {
			v = opcode(s[i]);
			freq[v]++;
		}

		for (auto c: s) {
			v = opcode(c);
			freq[v]--;

			if (visited[v])
				continue;

			while (!res.empty() && res.back() > c &&
			       freq[opcode(res.back())] > 0) {
				visited[opcode(res.back())] = false;
				res.pop_back();
			}
			res.push_back(c);
			visited[v] = true;
		}

		return res;
	}
};

int main()
{
	string data[] = {
		"bcabc",	// abc
		"cbacdcbc",	// acdb
		"edebbed",	// bed
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.removeDuplicateLetters(d) << endl;
	}
	return 0;
}
