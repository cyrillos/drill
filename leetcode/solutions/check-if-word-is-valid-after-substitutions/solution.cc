class Solution {
public:
	bool isValid(string s) {
		//
		// Just mark 'a' as '(', and 'c' as ')'
		// so we simply need to check if this is
		// valid parenthesis sequence.
		stack<char> st;
		for (auto i = 0; i < s.size(); i++) {
			if (s[i] == 'a') {
				st.push('(');
			} else if (s[i] == 'b') {
				st.push('b');
			} else {
				// It is 'c'
				if (st.empty())
					return false;
				auto c = st.top();
				if (c == 'b') {
					st.pop();
					if (st.empty())
						return false;
					c = st.top();
					if (c != '(')
						return false;
					st.pop();
				} else
					return false;
			}
		}

		return st.empty() ? true : false;
	}
};
