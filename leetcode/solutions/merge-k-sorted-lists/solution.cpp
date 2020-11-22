#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int nr = (int)lists.size();
		if (nr < 1)
			return NULL;

		ListNode *head = NULL, *tail = NULL;

		/*
		 * Find the next candidate. Actually there is
		 * another option - make a helper to merge two
		 * lists, then simply merge first two and continue
		 * merging new generated list with one from lists
		 * but I deside to save memory and simply do a linear
		 * lookup for a candidate then shift found entry out.
		 */
		auto find_next = [&](vector<ListNode*>& lists, int nr) {
			int v = 1000000;
			int pos = -1;
			for (int i = 0; i < nr; i++) {
				if (!lists[i] || lists[i]->val > v)
					continue;
				pos = i;
				v = lists[i]->val;
			}
			return pos;
		};

		int pos = find_next(lists, nr);
		if (pos != -1) {
			head = tail = lists[pos];
			lists[pos] = lists[pos]->next;

			for (pos = find_next(lists, nr);
			     pos != -1;
			     pos = find_next(lists, nr)) {
				tail->next = lists[pos];
				tail = lists[pos];
				lists[pos] = lists[pos]->next;
			}
			tail->next = NULL;
		}

		return head;
	}
};

int main(void)
{
#if 0
	vector<vector<ListNode>> v = {
		{ ListNode(1), ListNode(4), ListNode(5) },
		{ ListNode(1), ListNode(3), ListNode(4) },
		{ ListNode(2), ListNode(6) },
	};
#else
	vector<vector<ListNode>> v = {
		{ },
		{ ListNode(1), ListNode(3), ListNode(4) },
		{ ListNode(2), ListNode(6) },
	};
#endif

	for (int i = 0; i < (int)v.size(); i++) {
		for (int j = 1; j < (int)v[i].size(); j++) {
			v[i][j-1].next = &v[i][j];
		}
	}

	vector<ListNode *> lists(v.size());
	for (int i = 0; i < (int)v.size(); i++) {
		lists[i] = &v[i][0];
	}

	Solution s;
	auto r = s.mergeKLists(lists);
	while (r) {
		printf("%d ", r->val);
		r = r->next;
	}
	printf("\n");
	return 0;
}
