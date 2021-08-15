class Solution {
public:
	int depth(TreeNode* nd) {
		if (nd == NULL)
			return 0;
		return max(depth(nd->left), depth(nd->right)) + 1;
	}

	bool isBalanced(TreeNode* root) {
		if (!root)
			return true;

		int left = depth(root->left);
		int right = depth(root->right);

		return abs(left - right) <= 1 &&
			isBalanced(root->left) &&
			isBalanced(root->right);
	}
};
