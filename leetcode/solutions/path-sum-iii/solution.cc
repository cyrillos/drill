class Solution {
public:
	//
	// Just walk the tree in preorder way considering
	// every node as a root, then jump into DFS with
	// this root an investigate all possible subtrees
	// finding out the matched ones.
	int nr_matches = 0;
	void helper(TreeNode *node, int cur, int sum) {
		if (!node)
			return;

		cur += node->val;
		if (cur == sum)
			nr_matches++;

		helper(node->left, cur, sum);
		helper(node->right, cur, sum);
	}

	int pathSum(TreeNode* root, int targetSum) {
		stack<TreeNode *> st;

		if (root)
			st.push(root);

		while (!st.empty()) {
			auto node = st.top();
			st.pop();

			helper(node, 0, targetSum);

			if (node->right)
				st.push(node->right);

			if (node->left)
				st.push(node->left);
		}

		return nr_matches;
	}
};
