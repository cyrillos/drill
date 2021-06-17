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
	ListNode* deleteDuplicates(ListNode* head) {
		//
		// Fast exit if needed.
		if (!head)
			return NULL;
		else if (!head->next)
			return head;

		//
		// 1 -> 1 -> 1 -> 2 -> 3 -> 4
		// 1 -> 1 -> 2 -> 2
		// 1 -> 2 -> 2 -> 3
		// 1 -> 2 -> 2 -> 2

		//
		// Just use a fake node which will
		// be collecting elements from original
		// list, we're like moving elements without
		// duplicates from one list to another.
		ListNode fake(0, head);
		auto ptr = &fake;

		while (head) {
			//
			// Skip duplicates
			if (head->next && head->val == head->next->val) {
				do {
					head = head->next;
				} while (head->next && head->val == head->next->val);
				// next is new sequence, if it
				// gonna be a series of duplicates
				// again we will just replace on next
				// iteration the `next` pointer to
				// skip new duplicates
				ptr->next = head->next;
			} else
				ptr = ptr->next;
			head = head->next;
		}

		return fake.next;
	}
};
