#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* newList(const vector<int>& values)
{
	ListNode* head = nullptr;
	for (auto it = values.rbegin(); it != values.rend(); ++it) {
		auto node = new ListNode(*it);
		node->next = head;
		head = node;
	}
	return head;
}

void deleteList(ListNode* head)
{
	while (head) {
		auto next = head->next;
		delete head;
		head = next;
	}
}

ostream& operator<<(ostream& out, const ListNode* head)
{
	out << '[';
	for (auto node = head; node; node = node->next) {
		if (node != head)
			out << ',';
		out << node->val;
	}
	out << ']';
	return out;
}

class Solution {
public:
	ListNode* merge(ListNode *&l, ListNode *&r) {
		ListNode *result;

		if (l == nullptr)
			return r;
		else if (r == nullptr)
			return l;

		if (l->val <= r->val) {
			result = l;
			result->next = merge(l->next, r);
		} else {
			result = r;
			result->next = merge(l, r->next);
		}

		return result;
	};

	ListNode* mergesort(ListNode* head) {
		//
		// Split the list to the two parts
		// and return the second part.
		auto partition = [](ListNode* head) {
			ListNode* tail = head;
			ListNode* fast = head->next;

			while (fast) {
				fast = fast->next;
				if (fast) {
					tail = tail->next;
					fast = fast->next;
				}
			}

			return tail;
		};

		if(head == nullptr || head->next == nullptr)
			return head;

		// Split it
		ListNode *a = partition(head);
		ListNode *b = a->next;
		a->next = nullptr;

		// Sort recursively both (top down)
		a = mergesort(head);
		b = mergesort(b);

		// And merge them
		return merge(a, b);

		// Another approach is to use
		// bottom up merge sort but it
		// will require more code.
	};

	ListNode* sortList(ListNode* head) {
		return mergesort(head);
	}
};

void test(const vector<int>& values)
{
	ListNode* head = newList(values);
	cout << head << " => ";
	head = Solution().sortList(head);
	cout << head << endl;
	deleteList(head);
}

int main()
{
	vector<int> input[] = {
		{},
		{1},
		{1, 2},
		{4,2,1,3},
		{-1,5,3,4,0},
	};
	for (const auto& values: input) {
		ListNode* head = newList(values);
		cout << head << " => ";
		head = Solution().sortList(head);
		cout << head << endl;
		deleteList(head);
	}
	return 0;
}
