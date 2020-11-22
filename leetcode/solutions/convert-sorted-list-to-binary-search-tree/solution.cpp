#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	// Lookup for a middle via 2x pointer
	ListNode* middle(ListNode* left, ListNode* right) {
		if (!left || left == right)
			return NULL;

		ListNode* fast = left;
		while (fast != right && fast->next != right) {
			left = left->next;
			fast = fast->next->next;
		}

		return left;
	}

	TreeNode* recursive(ListNode* left, ListNode* right) {
		ListNode* m = middle(left, right);
		if (!m)
			return NULL;
		TreeNode *n = new TreeNode(m->val);
		n->left = recursive(left, m);
		n->right = recursive(m->next, right);
		return n;
	};

	TreeNode* sortedListToBST(ListNode* head) {
		return recursive(head, NULL);
	}
};
