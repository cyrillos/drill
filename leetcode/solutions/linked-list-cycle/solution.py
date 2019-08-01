class Solution(object):
    #
    # Hash table
    def hash_table(self, head):
        visited = set()
        while head:
            if head in visited:
                return True
            visited.add(head)
            head = head.next
        return False

    #
    # Use two pointers: one moves by one
    # step and another by two steps. If there
    # is a cycle, the second pointer get
    # spinning and first one will intersect it.
    def two_pointers(self, head):
        slow, fast = head, head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False

    def hasCycle(self, head):
        return self.two_pointers(head)
