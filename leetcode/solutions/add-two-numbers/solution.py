# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        c = 0
        tail = head = None
        while l1 or l2:
            if l1 and l2:
                v = l1.val + l2.val + c
                l1 = l1.next
                l2 = l2.next
            elif l1:
                v = l1.val + c
                l1 = l1.next
            elif l2:
                v = l2.val + c
                l2 = l2.next
            a = v % 10
            c = v // 10
            if head == None:
                tail = head = ListNode(a)
            else:
                tail.next = ListNode(a)
                tail = tail.next
        if c != 0:
            tail.next = ListNode(c)

        return head
