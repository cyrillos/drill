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
	int minCameraCover(TreeNode *root) {
		unordered_map<TreeNode *, int> state;
		int accum = 0;
		vector<int> res;

		stack<TreeNode *> stack;
		TreeNode *node = root;
		TreeNode *last = nullptr;

		enum {
			NONE	= 0,
			LIGHT	= 1,
			FIX	= 2,
		};

		const char *__state_str[] = {
			"NONE",
			"LIGHT",
			"FIX",
		};

		if (!root)
			return 0;

		state[root] = NONE;
		if (!root->left && !root->right)
			return 1;

		auto state_str = [&](TreeNode *node) {
			char *buf = new char[128];
			if (node) {
				int idx = state[node];
				sprintf(buf, "%d %s", node->val, __state_str[idx]);
			} else
				buf[0] = '\0';
			return buf;
		};

		auto visit_node = [&](TreeNode *node) {
			if (node->left && node->right) {
				if (state[node->left] == NONE ||
				    state[node->right] == NONE) {
					state[node] = FIX;
					if (state[node->left] == NONE)
						state[node->left] = LIGHT;
					if (state[node->right] == NONE)
						state[node->right] = LIGHT;
					printf("%s %s %s\n",
					       state_str(node),
					       state_str(node->left),
					       state_str(node->right));
				} else {
					if (state[node->left] == FIX ||
					    state[node->right] == FIX)
						state[node] = LIGHT;
					else
						state[node] = NONE;
					printf("%s %s %s\n",
					       state_str(node),
					       state_str(node->left),
					       state_str(node->right));
				}
			} else if (node->left) {
				if (state[node->left] == NONE) {
					state[node] = FIX;
					state[node->left] = LIGHT;
					printf("%s %s\n",
					       state_str(node),
					       state_str(node->left));
				} else if (state[node->left] == LIGHT) {
					state[node] = NONE;
					printf("%s\n",
					       state_str(node));
				} else if (state[node->left] == FIX) {
					state[node] = LIGHT;
					printf("%s %s\n",
					       state_str(node),
					       state_str(node->left));
				}
			} else if (node->right) {
				if (state[node->right] == NONE) {
					state[node] = FIX;
					state[node->right] = LIGHT;
					printf("%s %s\n",
					       state_str(node),
					       state_str(node->right));
				} else if (state[node->right] == LIGHT) {
					state[node] = NONE;
					printf("%s\n",
					       state_str(node));
				} else if (state[node->right] == FIX) {
					state[node] = LIGHT;
					printf("%s %s\n",
					       state_str(node),
					       state_str(node->right));
				}
			} else {
				state[node] = NONE;
				printf("VISIT %s\n", state_str(node));
			}
		};

		while (node || !stack.empty()) {
			if (node) {
				state[node] = 0;
				stack.push(node);
				node = node->left;
			} else {
				auto peek = stack.top();
				if (peek->right && peek->right != last) {
					node = peek->right;
				} else {
					visit_node(peek);
					stack.pop();
					last = peek;
					res.push_back(peek->val);
				}
			}
		}

		if (state[root] == NONE) {
			if (root->left && root->right) {
				if (state[root->left] != FIX &&
				    state[root->right] != FIX) {
					state[root] = FIX;
				}
			} else if (root->left) {
				if (state[root->left] != FIX) {
					state[root] = FIX;
					state[root->left] = LIGHT;
				}
			} else if (root->right) {
				if (state[root->right] != FIX) {
					state[root] = FIX;
					state[root->right] = LIGHT;
				}
			} else {
				state[root] = FIX;
			}
			printf("ROOT %s %s %s\n",
			       state_str(root),
			       state_str(root->left),
			       state_str(root->right));
		}

		for (auto it = state.begin(); it != state.end(); it++) {
			if (it->second == FIX)
				accum++;
		}

		cout << "res " << res << endl;
		return accum;
	}
};

int main()
{
	string input[] = {
		"[1,2,3]", // 1
		"[1,2,null,3,4]", // 1
		"[1,2,null,null,3,4,null,null,5,6]", // 2
		"[1,null,2,null,3,null,4]", // 2
		"[1,2,3,null,null,null,4]", // 2
		"[1,null,2,3,null,4,5,null,null,6]", // 3
		"[1,2,3,null,4,5,null,null,6]", // 2
		"[1,2,3,4,null,null,null,5,6,null,7,null,8]", // 3
	};
	Solution solution;
	for (const auto &values: input) {
		TreeNode *root = stringToTreeNode(values);
		cout << root << " => " << endl << solution.minCameraCover(root) << endl << "---" << endl;
	}
	return 0;
}
