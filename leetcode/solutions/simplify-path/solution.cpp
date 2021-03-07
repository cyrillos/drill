#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

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
	string simplifyPath(string s) {
		int len = s.length();
		stack<pair<int,int>> d;
		string res;

		auto process_word = [&](int pos, int len) {
			if (len == 2) {
				if (s[pos] == '.' && s[pos+1] == '.') {
					if (!d.empty())
						d.pop();
				} else
					d.push({pos, 2});
			} else if (len == 1) {
				if (s[pos] != '.')
					d.push({pos, 1});
			} else {
				d.push({pos, len});
			}
		};

		int pos = -1;
		for (int i = 0; i < len; i++) {
			if (s[i] == '/') {
				if (pos == -1)
					continue;
				process_word(pos, i-pos);
				pos = -1;
			} else {
				if (pos == -1)
					pos = i;
			}
		}

		if (pos != -1)
			process_word(pos, len-pos);

		if (d.empty())
			return "/";

		while (!d.empty()) {
			auto &v = d.top();
			res.insert(0, s.substr(v.first, v.second));
			res.insert(0, "/");
			d.pop();
		}
		return res;
	}
};

int main()
{
	string input[] = {
		{"/home/"},			// "/home"
		{"/home"},			// "/home"
		{"/../"},			// "/"
		{"/.."},			// "/"
		{"/home//foo/"},		// "/home/foo"
		{"/a/./b/../../c/"},		// "/c"
		{"/a//b////c/d//././/.."},	// "/a/b/c"
		{"/..."},			// "/..."
		{"/.hidden"},			// "/.hidden
		{"/."},				// "/"
		{"/.../"},			// "/..."
		{"/."},				// "/"
		{"/hello../world"},		// "/hello../world"
	};
	Solution solution;
	for (auto& s: input) {
		cout << s << " => " << solution.simplifyPath(s) << endl;
	}
	return 0;
}
