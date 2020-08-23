struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	bool lookup(TreeNode *nd, TreeNode *self, int need) {
		if (!nd)
			return false;
		if (nd->val == need && nd != self)
			return true;
		return lookup(need >= nd->val ?
			      nd->right : nd->left,
			      self, need);
	}

	// Simply iterate over each node and find
	// an appropriate target.
	bool dfs(TreeNode *root, TreeNode *nd, int k) {
		if (!nd)
			return false;

		auto v = k - nd->val;
		if (lookup(root, nd, v))
			return true;

		return dfs(root, nd->left, k) ||
			dfs(root, nd->right, k);
	}

	bool findTarget(TreeNode *root, int k) {
		if (!root)
			return false;
		return dfs(root, root, k);
	}
};
