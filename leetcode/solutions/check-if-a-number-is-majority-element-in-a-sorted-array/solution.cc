class Solution {
public:
	bool isMajorityElement(vector<int>& nums, int target) {
		auto nr = nums.size() / 2 + 1;
		//
		// We could use binary search to find interval
		// where target sits but lets use plain traverse
		// since it is passes as well. An idea is simply
		// count numbers of @target elements and check
		// if it is not less than @nr.
		for (size_t i = 0; i < nums.size(); i++) {
			if (nums[i] != target)
				continue;
			do {
				if (--nr == 0)
					return true;
				if (nums[i] != target)
					return false;
				i++;
			} while (i < nums.size());
		}
		return false;
	}
};
