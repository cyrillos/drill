class Solution {
public:
	//
	// Just use a counting sort.
	vector<int> findErrorNums(vector<int>& nums) {
		vector<int> c(nums.size()+1, 0);
		vector<int> r(2);

		for (auto i = 0; i < nums.size(); i++) {
			c[nums[i]]++;
		}

		for (auto i = 1; i < c.size(); i++) {
			if (c[i] == 0)
				r[1] = i;
			else if (c[i] > 1)
				r[0] = i;
		}

		return r;
	}
};
