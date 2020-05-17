/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
	Node *flatten(Node *head) {
		Node *nd = head;
		auto last = [](Node *nd) {
			while (nd && nd->next)
				nd = nd->next;
			return nd;
		};

		while (nd) {
			if (nd->child) {
				auto next = nd->next;
				auto next_ptr = &nd->next;
				auto child_prev_ptr = &nd->child->prev;
				auto lst = last(nd->child);

				nd->next = nd->child;
				*child_prev_ptr = nd;
				lst->next = next;
				if (next)
					next->prev = lst;
				nd->child = nullptr;
			}
			nd = nd->next;
		}

		return head;
	}
};
