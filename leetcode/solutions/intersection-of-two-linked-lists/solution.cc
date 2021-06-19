/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		ListNode *res = NULL;

		if (!headA || !headB)
			return NULL;

		//
		// Simply invert values and to
		// mark list as visited.
		auto a = headA;
		while (a) {
			a->val = -a->val;
			a = a->next;
		}

		auto b = headB;
		while (b) {
			if (b->val < 0) {
				res = b;
				break;
			}
			b->val = -b->val;
			b = b->next;
		}

		//
		// Restore original settings
		a = headA;
		while (a) {
			a->val = -a->val;
			a = a->next;
		}

		b = headB;
		while (b && b->val < 0) {
			b->val = -b->val;
			b = b->next;
		}

		return res;
	}
};
