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
6   2*  0*  8
   / \
  7*  4
#endif

#if 0
// recursive solution
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
#endif

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		//
		// Iterative approach:
		//  - remember parents until both nodes are found
		//  - traverse one path from @p to @root remembering
		//    nodes visited in a set
		//  - traverse second path bottom up from @q to @root
		//    and once visited node from first path is found
		//    return it as LCA
		unordered_map<TreeNode *, TreeNode* > parents;
		set<TreeNode *> path;
		stack<TreeNode *> st;
		int visited = 0;

		parents[root] = nullptr;
		st.push(root);

		while (!st.empty()) {
			auto node = st.top();
			st.pop();

			if (node == p)
				visited++;
			else if (node == q)
				visited++;

			if (node->right) {
				parents[node->right] = node;
				st.push(node->right);
			}

			if (node->left) {
				parents[node->left] = node;
				st.push(node->left);
			}

			if (visited == 2)
				break;
		}

		auto parent_p = p;
		auto parent_q = q;

		while (parent_p != nullptr) {
			path.insert(parent_p);
			parent_p = parents[parent_p];
		}

		while (parent_q != nullptr) {
			if (path.find(parent_q) != path.end())
				return parent_q;
			parent_q = parents[parent_q];
		}

		return nullptr;
	}
};
