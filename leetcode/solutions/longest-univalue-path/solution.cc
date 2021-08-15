class Solution {
public:
	/*
	 * Simply use dfs to try each value of the tree
	 * and figure out the max repetitions.
	 */
	int dfs(TreeNode *node, int& res) {
		if (!node)
			return 0;

		//
		// Count left and right subtrees
		int l = dfs(node->left, res);
		int r = dfs(node->right, res);

		//
		// The counter itself, make sure
		// to set zero if not matched
		if (node->left && node->val == node->left->val)
			l += 1;
		else
			l = 0;
		if (node->right && node->val == node->right->val)
			r += 1;
		else
			r = 0;

		// Accumulate max found (left and right)
		res = max(res, l + r);

		// Return max value, since we accumulate
		// left and right subtrees in separate
		// variables
		return max(l, r);
	}

	int longestUnivaluePath(TreeNode* root) {
		if (!root)
			return 0;
		int res = 0;
		dfs(root, res);
		return res;
	}
};
