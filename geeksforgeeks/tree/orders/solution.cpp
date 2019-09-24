#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
	int		val;
	TreeNode	*left;
	TreeNode	*right;

	TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

ostream& operator<<(ostream& out, const TreeNode *root)
{
	queue<const TreeNode *> queue_nodes;
	int nr_nils = 0;

	out << '[';
	queue_nodes.push(root);

	while (!queue_nodes.empty()) {
		auto node = queue_nodes.front();
		queue_nodes.pop();
		if (node) {
			queue_nodes.push(node->left);
			queue_nodes.push(node->right);
			if (node != root)
				out << ',';
			while (nr_nils > 0) {
				out << "nil,";
				nr_nils--;
			}
			out << node->val;
		} else {
			nr_nils++;
		}
	}
	out << ']';
	return out;
}

TreeNode *alloc_tree(const vector<int>& values)
{
	queue<TreeNode *> queue_nodes;
	TreeNode *root = nullptr;

	for (auto it = values.begin(); it != values.end(); it++) {
		if (!root) {
			if (*it == 0)
				break;
			root = new TreeNode(*it);
			queue_nodes.push(root);
			continue;
		}

		auto node = queue_nodes.front();
		queue_nodes.pop();

		if (*it != 0) {
			node->left = new TreeNode(*it);
			queue_nodes.push(node->left);
		}

		if (++it != values.end() && *it != 0) {
			node->right = new TreeNode(*it);
			queue_nodes.push(node->right);
		}
	}
	return root;
}

void delete_tree(TreeNode *root)
{
	if (root) {
		delete_tree(root->left);
		delete_tree(root->right);
		delete(root);
	}
}

class Solution {
public:
	void __recursive_preorder_traversal(vector<int>& res, TreeNode* root) {
		if (root) {
			res.push_back(root->val);
			__recursive_preorder_traversal(res, root->left);
			__recursive_preorder_traversal(res, root->right);
		}
	}
	vector<int> recursive_preorder_traversal(TreeNode* root) {
		vector<int> res;
		__recursive_preorder_traversal(res, root);
		return res;
	}

	void __recursive_inorder_traversal(vector<int>& res, TreeNode* root) {
		if (root) {
			__recursive_inorder_traversal(res, root->left);
			res.push_back(root->val);
			__recursive_inorder_traversal(res, root->right);
		}
	}
	vector<int> recursive_inorder_traversal(TreeNode* root) {
		vector<int> res;
		__recursive_inorder_traversal(res, root);
		return res;
	}

	void __recursive_postorder_traversal(vector<int>& res, TreeNode* root) {
		if (root) {
			__recursive_postorder_traversal(res, root->left);
			__recursive_postorder_traversal(res, root->right);
			res.push_back(root->val);
		}
	}
	vector<int> recursive_postorder_traversal(TreeNode* root) {
		vector<int> res;
		__recursive_postorder_traversal(res, root);
		return res;
	}

	vector<int> iterative_inorder_traversal(TreeNode* root) {
		stack<TreeNode*> stack;
		vector<int> res;

		TreeNode* node = root;
		while (node || !stack.empty()) {
			if (node) {
				stack.push(node);
				node = node->left;
			} else {
				node = stack.top();
				stack.pop();

				res.push_back(node->val);
				node = node->right;
			}
		}

		return res;
	}

	vector<int> iterative_preorder_traversal(TreeNode* root) {
		stack<TreeNode*> stack;
		vector<int> res;

		if (!root)
			return res;

		stack.push(root);
		while (!stack.empty()) {
			auto node = stack.top();
			stack.pop();

			res.push_back(node->val);
			if (node->right)
				stack.push(node->right);
			if (node->left)
				stack.push(node->left);
		}

		return res;
	}

	vector<int> iterative_postorder_traversal(TreeNode* root) {
		stack<TreeNode*> stack;
		vector<int> res;

		TreeNode* node = root;
		TreeNode* last = nullptr;

		while (node || !stack.empty()) {
			if (node) {
				stack.push(node);
				node = node->left;
				// walk deep leftmost
			} else {
				// the trick is to remember
				// last processed node to
				// walk in right upward and
				// do not push right nodes which
				// were already printed
				auto peek = stack.top();
				if (peek->right && peek->right != last) {
					node = peek->right;
				} else {
					stack.pop();
					res.push_back(peek->val);
					last = peek;
				}
			}
		}

		return res;
	}
};

int main()
{
	vector<int> input[] = {
		//{ 25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90 },
		//
		//           1
		//     2         3
		//   4   5      6   7
		//         8          9
		//
		{ 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 8, 0, 0, 0, 9 },
	};
	Solution solution;
	for (const auto &values: input) {
		TreeNode *root = alloc_tree(values);
		cout << root << " rec:(  inorder) => " << solution.recursive_inorder_traversal(root) << endl;
		cout << root << " itr:(  inorder) => " << solution.iterative_inorder_traversal(root) << endl;
		cout << root << " rec:( preorder) => " << solution.recursive_preorder_traversal(root) << endl;
		cout << root << " itr:( preorder) => " << solution.iterative_preorder_traversal(root) << endl;
		cout << root << " rec:(postorder) => " << solution.recursive_postorder_traversal(root) << endl;
		cout << root << " itr:(postorder) => " << solution.iterative_postorder_traversal(root) << endl;
		delete_tree(root);
	}
	return 0;
}
