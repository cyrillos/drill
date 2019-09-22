#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

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
	int minDepth(TreeNode* root) {
		queue<TreeNode *> queue_nodes;
		int level = 0;

		if (!root)
			return 0;

		queue_nodes.push(nullptr);
		queue_nodes.push(root);
		while (true) {
			auto node = queue_nodes.front();
			queue_nodes.pop();

			if (!node) {
				if (queue_nodes.empty())
					break;
				queue_nodes.push(nullptr);
				level++;
				continue;
			}

			if (!node->left && !node->right)
				return level;

			if (node->left)
				queue_nodes.push(node->left);
			if (node->right)
				queue_nodes.push(node->right);
		}

		return level;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 1 },
		{ 3, 9, 20, 0, 0, 15, 7 },
	};
	Solution solution;
	for (const auto &values: input) {
		TreeNode *root = alloc_tree(values);
		cout << root << " => " << solution.minDepth(root) << endl;
		delete_tree(root);
	}
	return 0;
}
