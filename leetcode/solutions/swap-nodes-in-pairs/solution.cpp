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
	ListNode* swapPairs(ListNode* head) {
		ListNode **last = &head, *a, *b;
		//
		// Just swap pairs and don't forget to
		// use pointer to pointer to adjust ->next
		// pointer of the last pair.
		while ((a = *last) && (b = a->next)) {
			a->next = b->next;
			b->next = a;
			*last = b;

			last = &(a->next);
		}
		return head;
	}
};
