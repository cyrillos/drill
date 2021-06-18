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
	ListNode* partition(ListNode* head, int x) {
		ListNode fake_lt(0, NULL);
		ListNode fake_ge(0, NULL);

		/*
		 * Simply gather elements into
		 * two disjoint lists and join
		 * them at the end.
		 */
		auto fake_lt_ptr = &fake_lt;
		auto fake_ge_ptr = &fake_ge;

		while (head) {
			if (head->val < x) {
				fake_lt_ptr->next = head;
				fake_lt_ptr = head;
			} else {
				fake_ge_ptr->next = head;
				fake_ge_ptr = head;
			}
			head = head->next;
		}

		fake_ge_ptr->next = NULL;
		fake_lt_ptr->next = fake_ge.next;

		return fake_lt.next;
	}
};
