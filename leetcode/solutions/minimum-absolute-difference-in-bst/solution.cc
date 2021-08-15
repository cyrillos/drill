class Solution {
public:
	//
	// Inorder (left, node, right) traverse generate
	// a sorted array
	//
	//      4
	//     / \
	//    2   6
	//   / \
	//  1   3
	//
	// [1,2,3,4,6] => 1
	// 
	int getMinimumDifference(TreeNode* root) {
		stack<TreeNode *> st;
		TreeNode *node = root;
		TreeNode *prev = nullptr;
		int res = 1000000;

		while (node || !st.empty()) {
			if (node) {
				while (node) {
					st.push(node);
					node = node->left;
				}
			} else {
				auto top = st.top();
				st.pop();

				if (prev != nullptr)
					res = min(res, abs(prev->val - top->val));
				prev = top;

				if (top->right)
					node = top->right;
			}
		}

		return res;
	}
};
