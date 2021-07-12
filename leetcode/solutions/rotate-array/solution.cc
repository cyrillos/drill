class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		size_t n = nums.size();

		if (k < 1 || n <= 1)
			return;

		//
		// Ecxlude identity shifts,
		// basically it is a permutation
		// moving each element to the same
		// position.
		k %= n;
		if (k == 0)
			return;

		//
		// [1,2,3,4, | 5,6,7], k = 3
		// [5,6,7, | 1,2,3,4]

		//
		// Note that if we walk reverse
		// we have
		//
		// 7,6,5,4,3,2,1
		//
		// then we reverse each group
		//
		// 5,6,7 | 1,2,3,4
		//
		// Thus the algo is:
		//  - reverse the whole array
		//  - reverse subgroups

		size_t i = 0, j = n-1;
		while (i < j)
			swap(nums[i++], nums[j--]);
		i = 0, j = k-1;
		while (i < j)
			swap(nums[i++], nums[j--]);
		i = k, j = n-1;
		while (i < j)
			swap(nums[i++], nums[j--]);
	}
};
