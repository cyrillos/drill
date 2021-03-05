/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		ListNode* index[500] = { NULL, };
		ListNode *n = head;
		int nr = 0, pos = 0;

		if (!head || head->next == NULL)
			return head;

		while (n) {
			index[pos++] = n;
			n = n->next;
		}

		int off = k % pos;
		if (off > 0) {
			auto head = index[pos-off];
			auto pre_head = index[pos-off-1];
			pre_head->next = NULL;
			index[pos-1]->next = index[0];
			return head;
		}

		return index[0];
	}
};
