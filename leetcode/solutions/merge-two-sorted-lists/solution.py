# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        p = [ListNode(0)]
        while l1 or l2:
            if not l1:
                p[-1].next = l2
                p.append(l2)
                l2 = l2.next
            elif not l2:
                p[-1].next = l1
                p.append(l1)
                l1 = l1.next
            else:
                if l1.val <= l2.val:
                    p[-1].next = l1
                    p.append(l1)
                    l1 = l1.next
                else:
                    p[-1].next = l2
                    p.append(l2)
                    l2 = l2.next
        if len(p) == 1:
            return None
        return p[1]
