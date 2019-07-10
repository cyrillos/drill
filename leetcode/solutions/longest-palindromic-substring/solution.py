class Solution:
    def longestPalindrome(self, s: str) -> str:
        if len(s) < 1:
            return ""

        def longest_palindrome_at(s, l, r):
            i, j, length = l, r, 0
            while i >= 0 and j < len(s):
                if s[i] != s[j]:
                    break
                i, j = i-1, j+1
                length += 2
            return i+1, j-1, length

        left, right, size = 0, 0, 0

        #
        # This is expand around center, O(n^2).
        # Need to use Manaker algo for linear time.
        for i in range(0, len(s)):
            l, r, length = longest_palindrome_at(s, i, i+1)
            if length > size:
                left, right, size = l, r, length
            l, r, length = longest_palindrome_at(s, i-1, i+1)
            if length >= size:
                left, right, size = l, r, length+1
        return s[left:right+1]

data = [
    "ab",           # -> "a"
    "bb",           # -> "bb"
    "babad",        # -> "bab"
    "cbbd",         # -> "bb"
    "ccc",          # -> "cc"
]
for i in range(0, len(data)):
    print(Solution().longestPalindrome(data[i]))
