#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

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

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

static ostream& operator<<(ostream& out, ListNode *head)
{
       out << '[';
       for (auto it = head; it != nullptr; it = it->next) {
               if (it != head)
                       out << ',';
               out << it->val;
       }
       out << ']';
       return out;
}

static ListNode* gen_ListNode(char *str)
{
	ListNode *head = NULL, *tail = NULL;
	char *tok = NULL;

	tok = strtok(str, ",");
	while (tok) {
		if (*tok == '[')
			tok++;
		size_t len = strlen(tok);
		if (tok[len-1] == ']')
			tok[len-1] = '\0';

		ListNode *node = new ListNode(atoi(tok));
		if (head == NULL) {
			head = tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
		tok = strtok(NULL, ",");
	}

	return head;
}

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode *p, *d = nullptr;

		//
		// Just kip first n entries and remove
		// the element we have to skip.
		for (p = head; p != nullptr; p = p->next) {
			if (n-- == 0) {
				d = head;
			} else {
				if (d != nullptr)
					d = d->next;
			}
		}

		if (d == nullptr) {
			if (head != nullptr)
				return head->next;
			return nullptr;
		}

		d->next = d->next ? d->next->next : nullptr;
		return head;
	}
};

int main(void)
{
	struct {
		char	*str;
		int	n;
	} data[] = {
		{
			// => [1,2,3,5]
			.str = strdup("[1,2,3,4,5]"),
			.n = 2,
		}, {
			// => [2]
			.str = strdup("[1,2]"),
			.n = 2,
		}, {
			// => [1]
			.str = strdup("[1,2]"),
			.n = 1,
		}, {
			// => []
			.str = strdup("[1]"),
			.n = 1,
		},
	};

	for (size_t i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		ListNode *head = gen_ListNode(data[i].str);
		cout << head << " => " << data[i].n << endl;
		ListNode *n = Solution().removeNthFromEnd(head, data[i].n);
		cout << "\t" << n << endl;
	}

	return 0;
}
