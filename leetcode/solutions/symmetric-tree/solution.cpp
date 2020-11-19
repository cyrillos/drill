/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
	//
	// Just walk recursively over left and right nodes
	// which are to be the same uner a pivot.
	bool is_symmetric(TreeNode *left, TreeNode *right) {
		if (!left && !right)
			return true;
		if (!left || !right)
			return false;
		if (left->val != right->val)
			return false;

		// Outside and inside branches to match
		return is_symmetric(left->left, right->right) &&
			is_symmetric(left->right, right->left);
	}

	bool isSymmetric(TreeNode* root) {
		if (!root)
			return true;
		return is_symmetric(root->left, root->right);
	}
};
