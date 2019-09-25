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
	vector<int> preorderTraversal(TreeNode* root) {
		stack<TreeNode *> stack;
		vector<int> res;

		//
		// Preorder: root/left/right

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
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 1 },
		{ 1, 2, 3, 4, 5, 0, 0, 0, 0, 0, 0 },
		{ 1, 4, 3, 2, 0, 0, 0 },	// [1,4,2,3]
		{ 1, 0, 2, 3, 0 },
		{ 3, 9, 20, 0, 0, 15, 7 },
		{ 25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90 },
	};
	Solution solution;
	for (const auto &values: input) {
		TreeNode *root = alloc_tree(values);
		cout << root << " => " << solution.preorderTraversal(root) << endl;
		delete_tree(root);
	}
	return 0;
}
