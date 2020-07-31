class Solution {
public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
		vector<int> res;

		//
		// Plain bruteforce is enough
		for (auto i = 0; i < nums.size(); i++) {
			auto v = 0;
			for (auto j = 0; j < nums.size(); j++) {
				if (i != j && nums[j] < nums[i])
					v++;
			}
			res.push_back(v);
		}

		return res;
	}
};
