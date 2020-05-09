class Solution {
public:
    bool backspaceCompare(string S, string T) {

	    auto process = [&](string &s) {
		    for (ssize_t i = 0; i < s.size(); i++) {
			    if (s[i] != '#')
				    continue;
			    s[i] = ' ';
			    for (ssize_t j = i-1; j >= 0; j--) {
				    if (s[j] != ' ') {
					    s[j] = ' ';
					    break;
				    }
			    }
		    }
	    };

	    process(S);
	    process(T);

	    ssize_t i = 0, j = 0;
	    while (i < S.size() || j < T.size()) {
		    if (S[i] == ' ') {
			    if (i < S.size()) {
				    i++;
				    continue;
			    }
		    }
		    if (T[j] == ' ') {
			    if (j < T.size()) {
				    j++;
				    continue;
			    }
		    }
		    if (S[i] != T[j])
			    return false;
		    i++, j++;
	    }

	    return true;
    }
};
