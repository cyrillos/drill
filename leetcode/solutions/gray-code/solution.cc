class Solution {
public:
	vector<int> grayCode(int n) {
		//
		// Just use Gray's formula
		// g = g ^ (g - 1)
		int limit = 1 << n;
		vector<int> res((1 << n), 0);

		res[0] = 0;
		for (int i = 1; i < limit; i++)
			res[i] = i ^ (i >> 1);

		return res;
	}
};
