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
	bool is_same(TreeNode* root, TreeNode* sub) {
		if (!root && !sub)
			return true;
		if (!sub || !root)
			return false;
		if (root->val != sub->val)
			return false;
		return is_same(root->left, sub->left) &&
			is_same(root->right, sub->right);
	}

	bool isSubtree(TreeNode* root, TreeNode* subRoot) {
		if (!subRoot)
			return true;
		if (!root)
			return false;
		return is_same(root, subRoot) ||
			isSubtree(root->left, subRoot) ||
			isSubtree(root->right, subRoot);
	}
};
