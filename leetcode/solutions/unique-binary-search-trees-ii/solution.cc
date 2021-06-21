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
	vector<TreeNode*> recursive(int pos, int n) {
		//
		// Number of possible trees is Catalan number.
		// If we consider BST with root at i, then
		// it will have [1...i-1] left nodes and
		// [i+1 ... n] right nodes.
		//
		// For n = 3 we will have
		//
		//      1       1       root 1
		//       \       \
		//        2       3
		//         \     /
		//          3   2
		//
		//            2         root 2
		//           / \
		//          1   3
		//
		//       3      3       root 3
		//      /      /
		//     2      1
		//    /        \
		//   1          2
		//
		//
		// Thus we take each @pos in [1, n] sequence
		// as a root and generate subtrees in a recursive
		// way.
		vector<TreeNode*> res;

		if (pos > n)
			return {{}}; // End of tree

		for (auto i = pos; i <= n; i++) {
			auto left_subtree = recursive(pos, i - 1);
			auto right_subtree = recursive(i + 1, n);

			for (auto left_node: left_subtree) {
				for (auto right_node: right_subtree) {
					auto nd = new TreeNode(i, left_node, right_node);
					res.push_back(nd);
				}
			}
		}

		return res;
	}

	vector<TreeNode *> generateTrees(int n) {
		return recursive(1, n);
	}
};
