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
	int stepin(TreeNode* root, int v) {
		if (!root)
			return v;
		return max(stepin(root->left, v+1), stepin(root->right, v+1));
	}
	int maxDepth(TreeNode* root) {
		return stepin(root, 0);
	}
};
