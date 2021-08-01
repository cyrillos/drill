class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res;
		if (numRows == 1)
			return {{1}};
		else if (numRows == 2)
			return {{1},{1,1}};

		res.push_back({1});
		res.push_back({1,1});

		for (auto i = 3; i <= numRows; i++) {
			vector<int> r(i);
			r[0] = r[i-1] = 1;

			auto last = res.back();
			for (auto j = 1; j < i-1; j++)
				r[j] = last[j-1] + last[j];

			res.push_back(r);
		}

		return res;
	}
};
