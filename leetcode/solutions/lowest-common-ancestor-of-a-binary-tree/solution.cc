/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#if 0
      3
     / \
    /   \
   /     \
  5       1
 / \     / \
6   2   0   8
   / \
  7   4
#endif

class Solution {
public:
	TreeNode *parent = nullptr;
	bool dfs(TreeNode *node, TreeNode *p, TreeNode *q) {
		if (!node)
			return false;
		/*
		 * An idea is to walk nodes left and right
		 * until both nodes needed are found. Since
		 * we need to find least common accessor the
		 * parent node will be updated to be "closer"
		 * to @p and @q on each iteration.
		 */
		auto left = dfs(node->left, p, q);
		auto right = dfs(node->right, p, q);
		auto exact = node == p || node == q;
		/* We update the parent once we're closer */
		if (left + right + exact >= 2)
			parent = node;
		/* Continue execution until no nodes found */
		return left || right || exact;
	}

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		dfs(root, p, q);
		return parent;
	}
};
