#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <sstream>

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

void trimLeftTrailingSpaces(string &input) {
	input.erase(input.begin(), find_if(input.begin(), input.end(),
					   [](int ch) {
					   return !isspace(ch);
					   }));
}

void trimRightTrailingSpaces(string &input) {
	input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
			    return !isspace(ch);
			    }).base(), input.end());
}

TreeNode* stringToTreeNode(string input) {
	trimLeftTrailingSpaces(input);
	trimRightTrailingSpaces(input);
	input = input.substr(1, input.length() - 2);
	if (!input.size()) {
		return nullptr;
	}

	string item;
	stringstream ss;
	ss.str(input);

	getline(ss, item, ',');
	TreeNode* root = new TreeNode(stoi(item));
	queue<TreeNode*> nodeQueue;
	nodeQueue.push(root);

	while (true) {
		TreeNode* node = nodeQueue.front();
		nodeQueue.pop();

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int leftNumber = stoi(item);
			node->left = new TreeNode(leftNumber);
			nodeQueue.push(node->left);
		}

		if (!getline(ss, item, ',')) {
			break;
		}

		trimLeftTrailingSpaces(item);
		if (item != "null") {
			int rightNumber = stoi(item);
			node->right = new TreeNode(rightNumber);
			nodeQueue.push(node->right);
		}
	}
	return root;
}

class Solution {
public:
	int dfs(TreeNode *node, int& ans) {
		if (!node)
			return 0;
		auto left = dfs(node->left, ans);
		auto right = dfs(node->right, ans);

		ans += abs(left) + abs(right);
		return node->val + left + right - 1;
	}

	int distributeCoins(TreeNode *root) {
		int ans = 0;
		dfs(root, ans);
		return ans;
	}
};

int main()
{
	string input[] = {
		"[3,0,0]",		// 2
		"[0,3,0]",		// 3
		"[1,0,2]",		// 2
		"[1,0,0,null,3]",	// 4
	};
	Solution solution;
	for (const auto &values: input) {
		TreeNode *root = stringToTreeNode(values);
		cout << root << " => " << endl << solution.distributeCoins(root) << endl;
	}
	return 0;
}
