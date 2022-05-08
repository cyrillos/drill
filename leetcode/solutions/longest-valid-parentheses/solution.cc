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
	int longestValidParentheses(string s) {
		int left, right;
		int nr = s.size();
		int res = 0;
		//
		// Walk left and right and count
		// parentheses. We need to make
		// two walks for imbalances like
		//
		// "())" -> accounted from left to right walk
		// "(()" -> accounted from right to left walk
		//
		left = right = 0;
		for (ssize_t i = 0; i < nr; i++) {
			if (s[i] == '(')
				left++;
			else
				right++;
			if (left == right)
				res = max(res, left * 2);
			else if (right >= left)
				left = right = 0;
		}
		left = right = 0;
		for (ssize_t i = nr-1; i >= 0; i--) {
			if (s[i] == '(')
				left++;
			else
				right++;
			if (left == right)
				res = max(res, right * 2);
			else if (left >= right)
				left = right = 0;
		}
		return res;
	}
};

int main()
{
	string data[] = {
		"(()",		// 2
		")()())",	// 4
	};
	Solution solution;
	for (auto& d: data) {
		cout << d << " => " <<
			solution.longestValidParentheses(d) << endl;
	}
	return 0;
}
