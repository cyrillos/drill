/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
#if 0
class Solution {
public:
	//
	// Just walk recursively (not interesting
	// solution)
	void recursive_helper(Node* node, Node* next) {
		if (!node)
			return;

		node->next = next;

		helper(node->left, node->right);
		helper(node->right, next ? next->left : NULL);
	}

	Node* connect(Node* root) {
		if (!root)
			return NULL;
		recursive_helper(root, NULL);
		return root;
	}
};
#endif

class Solution {
public:
	//
	// More elegant solution: use two
	// queues and level order traverse.
	// Push into @todo queue entries to
	// be connected and connect them.
	Node* connect(Node* root) {
		if (!root)
			return nullptr;

		queue<Node *> q;
		queue<Node *> todo;

		q.push(root);
		q.push(nullptr); // level mark

		while (!q.empty()) {
			auto node = q.front();
			q.pop();

			if (node == nullptr) {
				if (todo.empty())
					continue;
				auto last = todo.front();
				todo.pop();
				while (!todo.empty()) {
					auto n = todo.front();
					todo.pop();
					last->next = n;
					last = n;
				}
				last->next = nullptr;
				q.push(nullptr);
				continue;
			} else {
				todo.push(node);
			}

			if (node->left) {
				q.push(node->left);
				q.push(node->right);
			}
		}

		return root;
	}
};
