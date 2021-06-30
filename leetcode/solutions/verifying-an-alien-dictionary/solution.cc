class Solution {
public:
	bool isAlienSorted(vector<string>& w, string order) {
		if (w.size() < 2)
			return true;

		//
		// Simply compare the words for
		// lexicographic order.
		auto opcode = [&](char v) {
			return v - 'a';
		};

		int map[26];
		for (size_t i = 0; i < order.size(); i++)
			map[opcode(order[i])] = i;

		for (auto i = 1; i < w.size(); i++) {
			for (size_t j = 0; j < w[i].size(); j++) {
				if (w[i-1].size() <= j)
					goto next;
				int res = map[opcode(w[i][j])];
				res -= map[opcode(w[i-1][j])];
				if (res < 0)
					return false;
				else if (res > 0)
					goto next;
			}
			if (w[i-1].size() > w[i].size())
				return false;
next:
			/* nothing */;
		}

		return true;
	}
};
