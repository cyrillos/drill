class Solution {
public:
	vector<int> findBuildings(vector<int>& heights) {
		vector<int> res;

		//
		// Simple increasing heights.
		int r = heights.size() - 1;
		res.push_back(r);
		int v = heights[r];

		while (--r >= 0) {
			if (heights[r] > v) {
				res.push_back(r);
				v = heights[r];
			}
		}

		sort(res.begin(), res.end());
		return res;
	}
};
