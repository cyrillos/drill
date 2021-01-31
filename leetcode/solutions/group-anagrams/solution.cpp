#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <map>

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
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		//
		// Trivial hasmap, just use [x,x,x...] as counters
		// for letter occurences.
		map<array<unsigned char, 26>, vector<string>> m;
		for (auto& s : strs) {
			array<unsigned char, 26> chr_map = { };
			for (unsigned char d: s) {
				chr_map[d - 'a']++;
			}
			m[chr_map].push_back(s);
		}
		vector<vector<string>> res;
		for(auto& it : m) {
			res.push_back(it.second);
		}
		return res;
	}
};

int main()
{
	vector<string> input[] = {
		{"eat", "tea", "tan", "ate", "nat", "bat"},
		{""},
		{"a"},
	};
	Solution solution;
	for (auto& s: input) {
		cout << s << " => " <<
			solution.groupAnagrams(s) << endl;
	}
	return 0;
}
