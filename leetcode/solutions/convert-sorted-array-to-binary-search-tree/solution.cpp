class Solution {
	public:
		// Just take a node in a middle of array as
		// a root and build subtrees recursively.
		TreeNode* builder(vector<int> &nums, int l, int r) {
			if (r < l)
				return NULL;
			else if (l == r)
				return new TreeNode(nums[l]);

			int m = (l + r) / 2;
			TreeNode* root = new TreeNode(nums[m]);

			root->left  = builder(nums, l, m - 1);
			root->right = builder(nums, m + 1, r);

			return root;
		}

		TreeNode* sortedArrayToBST(vector<int>& nums) {
			return builder(nums, 0, nums.size() - 1);
		}

};
