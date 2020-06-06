#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
	int minAddToMakeValid(string s) {
		stack<char> stack;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == ')') {
				if (!stack.empty()) {
					auto t = stack.top();
					if (t == '(') {
						stack.pop();
						continue;
					}
				}
				stack.push(')');
			} else
				stack.push('(');
		}

		return stack.size();
    }
};

int main()
{
	string input[] = {
		"())",		// 1
		"(((",		// 3
		"()",		// 0
		"()))((",	// 4
	};
	Solution solution;
	for (auto s: input) {
		cout << s << " => " << solution.minAddToMakeValid(s) << endl;
	}
	return 0;
}
