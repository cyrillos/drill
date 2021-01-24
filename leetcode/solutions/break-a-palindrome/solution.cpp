class Solution {
public:
	string breakPalindrome(string s) {
		if (s.size() <= 1)
			return "";

		auto is_palindome = [&](string &s) {
			size_t i = 0;
			size_t j = s.size()-1;
			while (i < j) {
				if (s[i++] != s[j--])
					return false;
			}
			return true;
		};

		//
		// Walk forward and try to find lexical
		// smallest nonpalindrome string
		for (auto i = 0; i < s.size(); i++) {
			//
			// No need to deal with 'a' which
			// is low bound of alphabet
			if (s[i] == 'a')
				continue;
			auto v = s[i];
			for (auto c = 'a'; c <= 'z'; c++) {
				if (s[i] == c)
					continue;
				s[i] = c;
				if (!is_palindome(s))
					return s;
			}
			s[i] = v;
		}

		//
		// If we reach this point it means the
		// string was full of "aaa". Lets walk
		// backward and change the last letter
		// like "aaa" -> "aab"
		for (auto i = s.size() - 1; i >= 0; i--) {
			auto v = s[i];
			for (auto c = 'a'; c <= 'z'; c++) {
				if (s[i] == c)
					continue;
				s[i] = c;
				if (!is_palindome(s))
					return s;
			}
			s[i] = v;
		}
		return "";
	}
};
