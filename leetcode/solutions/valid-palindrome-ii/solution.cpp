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
	bool is_palindrome(string &s, ssize_t i, ssize_t j) {
		while (i < j) {
			if (s[i] != s[j])
				return false;
			i++, j--;
		}
		return true;
	}

	bool validPalindrome(string s) {
		ssize_t i = 0, j = (ssize_t)s.size()-1;
		while (i < j) {
			if (s[i] != s[j]) {
				// Just try to skip the letter
				return is_palindrome(s, i+1, j) ||
					is_palindrome(s, i, j-1);
			}
			i++, j--;
		}
		return true;
	}
};

int main()
{
	string input[] = {
		"abc",		// false
		"aba",		// true
		"abca",		// true (remove a)
		"cbbcc",	// true (remove last c)
	};
	Solution solution;
	for (auto s: input) {
		cout << s << " => " << solution.validPalindrome(s) << endl;
	}
	return 0;
}
