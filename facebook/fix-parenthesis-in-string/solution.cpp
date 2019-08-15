#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
	string FixParenthesis(string &s) {
		stack<size_t> opening;
		stack<size_t> closing;
		string res (s);

		//
		// An idea is simple: we remember
		// '(' and ')' positions of the
		// former string, in a stack. But
		// if we find that there is a balanced
		// pair we simply drop it from the stack.
		// Then simply mark unbalanced braces
		// with '$' and remove them from the
		// string.

		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				opening.push(i);
			} else if (s[i] == ')') {
				if (opening.size() > 0)
					opening.pop();
				else
					closing.push(i);
			}
		}

		while (opening.size() > 0) {
			res[opening.top()] = '$';
			opening.pop();
		}

		while (closing.size() > 0) {
			res[closing.top()] = '$';
			closing.pop();
		}

		res.erase(remove(res.begin(), res.end(), '$'), res.end());
		return res;
	}
};

int main()
{
	string input[] = {
		string ("(((()"),
		string ("))()(())"),
		string ("))()((aaa(bb)(aa))"),
		string (")aabc(c)d"),
	};
	Solution solution;
	for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
		cout << input[i] << " => " <<
			solution.FixParenthesis(input[i]) << endl;
	}
	return 0;
}
