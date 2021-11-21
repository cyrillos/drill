class Solution {
public:
	bool backtrack(vector<int>& matchsticks, vector<int>& sides,
		       size_t side_len, size_t nr, size_t pos) {
		if (pos == nr)
			return true;
		for (auto i = 0; i < 4; i++) {
			sides[i] += matchsticks[pos];
			if (sides[i] <= side_len)
				if (backtrack(matchsticks, sides,
					      side_len, nr, pos + 1))
					return true;
			sides[i] -= matchsticks[pos];
		}
		return false;
	}

	bool makesquare(vector<int>& matchsticks) {
		int nr = matchsticks.size();
		//
		// First make sure the summary length is
		// 4 multiplier since it is squate with
		// four sides
		size_t sum = 0;
		for (auto v: matchsticks)
			sum += v;
		if (sum % 4)
			return false;
		size_t side_len = sum / 4;

		// use DP and consider each possible construction
		vector<int> sides(4, 0);
		// we sort the data for faster lookup in revers
		// order, ie descedent
		sort(matchsticks.rbegin(), matchsticks.rend());

		return backtrack(matchsticks, sides, side_len, nr, 0);
	}
};
