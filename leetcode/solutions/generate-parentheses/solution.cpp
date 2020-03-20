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
	vector<string> generateParenthesis(int n) {
		vector<string> res;

		if (n == 0)
			return res;

		// Summay size (opening and closing parentheses)
		int size = n * 2;
		// Number of opening braces
		int depth = n;
		int pos = 0;

		string s;
		s.resize(size+1);

		do {
			// Make a permutation. Say n=3 we consider
			// ((())) as first permutation in lexicographic
			// order. Consider it as having zero prefix
			// and longest suffix.
			//
			// Now we gonna walk from last position and
			// find the first opening brace
			//
			// ((()))
			//   ^
			//
			// We can invert it but to keep the series
			// balanced we try to keep the suffix with
			// minimal changes, ie put after the inversion
			// opened and closing parenthesis as
			//
			// (()())
			//   ^---
			//
			// Then we simply continue: find the rightmost
			// opening brace wich doesn't form a balancing
			// braces in the suffix, ie
			//
			// (()())
			//    ^--
			//
			// and invert it appending balanced suffix
			//
			// (())()
			//    ^--
			//
			// then so on, here is the whole permutations
			// for n = 3
			// 
			// 012345
			// ((())) -> 2
			// (()()) -> 3
			// (())() -> 1 (last two braces are () and balanced!)
			// ()(()) -> 3
			// ()()()

			// fill the suffix
			for (int i = pos; i < size; i++) {
				if (depth-- > 0)
					s[i] = '(';
				else
					s[i] = ')';
			}

			res.push_back(s);
			pos = 0;

			int opened = 0, closed = 0;
			for (int i = size-1; i >= 0; i--) {
				if (s[i] == ')') {
					closed++;
				} else {
					opened++;
					if (opened < closed) {
						s[i] = ')';
						pos = i+1;
						depth = opened;
						break;
					}
				}
			}

			if (pos == 0)
				break;
		} while (true);

		return res;
	}
};

int main()
{
	int input[] = {
		1,
		2,
		3,
		4,
		5,
	};
	Solution solution;
	for (auto& n: input) {
		cout << n << " => " << solution.generateParenthesis(n) << endl;
	}
	return 0;
}
