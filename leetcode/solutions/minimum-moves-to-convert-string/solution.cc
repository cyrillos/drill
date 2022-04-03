class Solution {
public:
	int minimumMoves(string s) {
		int count = 0;
		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == 'X') {
				// Just skip this 000
				// seuence we make.
				i += 2;
				count++;
			}
		}
		return count;
	}
};
