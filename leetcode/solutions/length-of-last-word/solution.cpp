class Solution {
public:
	int lengthOfLastWord(string s) {
		if (s.length() == 0)
			return 0;
		int pos = s.length()-1;

		while (pos >= 0 && s[pos] == ' ')
			pos--;
		if (pos < 0)
			return 0;

		int end = pos;
		while (pos > 0 && s[pos] != ' ')
			pos--;
		return end - (s[pos] == ' ' ? pos : pos-1);
	}
};
