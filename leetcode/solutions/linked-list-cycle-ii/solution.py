# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def detectCycle(self, head):
        slow, fast = head, head
        #
        # This is similar to linked-list-cycle,
        # the idea behind is to walk two pointers
        # with p1 = n, p2 = 2n steps. Once p2 reaches
        # a cycle it starts spinning around. Later when
        # p1 reaches the cycle it walks over residue system,
        # say if cycle length is 4 then residue is {0,1,2,3}.
        # 'Case p2 walks with 2n and 2n is less than cycle
        # length, we're guaranteed to intersect the pointers.
        # Next it is always important to start from a list
        # head, so when pointers are get intersected the will
        # be in position which equals to number of steps
        # before entering the cycle.
        #
        # 1    2    3    4
        # +--->+--->+--->+
        #           ^    |
        #           |    v
        #           +---<+
        #           6    5
        #
        # Stage 1: (1,1), (2,3), (3,5), (4,3), (5,5)
        # Stage 2: (1,5), (2,6), (3,3)
        #
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                slow = head
                while slow != fast:
                    slow = slow.next
                    fast = fast.next
                return slow
        return None
