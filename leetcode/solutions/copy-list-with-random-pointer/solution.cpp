#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#if 1
// Definition for a Node.
class Node {
public:
	int	val;
	Node	*next;
	Node	*random;

	Node() {}

	Node(int _val, Node *_next, Node *_random) {
		val	= _val;
		next	= _next;
		random	= _random;
	}
};
#endif

class Solution {
public:
	Node *copyRandomList(Node *head) {
		unordered_map<Node *, Node *> map;

		Node *new_head = new Node(0, NULL, NULL);
		Node *nd = new_head;
		Node *p = head;
		Node *n;

		for (Node *p = head; p; p = p->next) {
			n = new Node(0, NULL, NULL);
			n->random = p->random;
			n->val = p->val;
			map[p] = n;
			nd->next = n;
			nd = n;
		}

		nd = new_head ? new_head->next : NULL;
		while (nd) {
			if (nd->random) {
				n = map[nd->random];
				nd->random = n;
			}
			nd = nd->next;
		}

		if (new_head) {
			Node *ret = new_head->next;
			delete(new_head);
			return ret;
		}
		return NULL;
	}
};

int main()
{
	Node *nd1, *nd2, *copy;

	nd1		= new Node;
	nd2		= new Node;

	nd1->val	= 1;
	nd1->next	= nd2;
	nd1->random	= nd2;

	nd2->val	= 2;
	nd2->next	= NULL;
	nd2->random	= nd2;

	Solution solution;

	copy = solution.copyRandomList(nd1);
	cout << copy << endl;

	return 0;
}
