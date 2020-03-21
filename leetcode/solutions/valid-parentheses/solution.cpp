#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

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
	bool isValid(string s) {
		stack<char> c;

		for (int i = 0; i < s.length(); i++) {
			if (s[i] == ')') {
				if (c.size() >= 1 && c.top() == '(') {
					c.pop();
					continue;
				} else
					return false;
			} else if (s[i] == ']') {
				if (c.size() >= 1 && c.top() == '[') {
					c.pop();
					continue;
				} else
					return false;
			} else if (s[i] == '}') {
				if (c.size() >= 1 && c.top() == '{') {
					c.pop();
					continue;
				} else
					return false;
			}
			c.push(s[i]);
		}

		return c.size() == 0;
	}
};

int main()
{
	string input[] = {
		"",
		"[",
		"(]",
		"()",
		"{{}}",
		"({[]})",
		"()[]{}",
	};

	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.isValid(s) << endl;
	}

	return 0;
}
