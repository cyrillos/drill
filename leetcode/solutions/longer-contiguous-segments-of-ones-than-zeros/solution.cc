class Solution {
public:
	bool checkZeroOnes(string s) {
		int best0 = 0, v0 = 0;
		int best1 = 0, v1 = 0;
		int pos = 0, n = s.size();

		while (pos < n) {
			if (s[pos] == '1') {
				best0 = max(best0, v0);
				v0 = 0;
				while (s[pos] == '1' && pos < n)
					v1++, pos++;
			} else {
				best1 = max(best1, v1);
				v1 = 0;
				while (s[pos] == '0' && pos < n)
					v0++, pos++;
			}
		}

		best0 = max(best0, v0);
		best1 = max(best1, v1);

		return best1 > best0;
	}
};
