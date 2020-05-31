class Solution {
public:
	int findMaxConsecutiveOnes(vector<int>& nums) {
		int best = 0;
		for (int i = 0, j = 0; i < (int)nums.size(); i++) {
			if (nums[i] == 1) {
				best = max(best, i - j + 1);
			} else {
				j = i + 1;
			}
		}
		return best;
	}
};
