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
	string reverseWords(string s) {
		int nr = s.size();
		string res;

		res.resize(nr);
		int i = 0, j = nr-1, l, r;
		//
		// skip leading spaces
		while (i < nr && s[i] == ' ')
			i++;

		while (i < nr) {
			// copy the word to the end of
			// result string
			r = j;
			while (s[i] != ' ' && i < nr)
				res[j--] = s[i++];
			while (i < nr && s[i] == ' ')
				i++;
			if (i <= nr) {
				//
				// and then reverse this copied
				// string just in place
				l = j+1;
				while (l < r)
					swap(res[l++], res[r--]);
				if (i < nr)
					res[j--] = ' ';
			}
		}

		//
		// if there were no excessive spaces
		// return the result, otherwise skip
		// leading spaces
		return j == -1 ? res : res.substr(j+1);
	}
};

int main()
{
	vector<string> data = {
		"  the sky is blue",	// blue is sky the
		"  hello world  ",	// world hello
		"a good   example",	// example good a
		"one",			// one
		" asdasd df f",
		"aa a aa a",
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " << "'" <<
			solution.reverseWords(d) << "'" << endl;
	}
	return 0;
}
