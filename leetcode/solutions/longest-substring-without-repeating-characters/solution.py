#
# This is a sliding window algo:
# we start at @head = 0 and counting
# numbers of chars at current position.
# If we get a duplicated char, we need
# to reset all char positions before it,
# move head forward to a new iteration,
# and repeat. Corner cases: there were
# repeatable chars but the last part
# we're scanning exited the loop; no
# repeatable chars at all.
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) == 0:
            return 0
        elif len(s) == 1:
            return 1
        m = head = 0
        d = { }
        for i in range(0, len(s)):
            pos = d.get(s[i], None)
            if pos != None:
                m = max(m, i - head)
                for j in range(head, pos):
                    d[s[j]] = None
                head = pos + 1
            d[s[i]] = i
        if head == 0: m = len(s)
        m = max(m, len(s)-head)
        return m
#data = [
#    "abba",     # => 2
#    "aab",      # => 2
#    "au",       # => 2
#    " ",        # => 1
#    "abcabcbb", # => 3
#    "abcabcbb", # => 3
#    "bbbbb",    # => 1
#    "pwwkew",   # => 3
#    "tmmzuxt"   # => 5
#]
#
#for i in range(0, len(data)):
#    print(Solution().lengthOfLongestSubstring(data[i]))
