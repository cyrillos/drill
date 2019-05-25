#
# Use accumulator (DP) to count parentheses.
# We've two cases here: either sequence
# of valid pairs is coming one after another
#
#    2 4 6
#    | | |
#   ()()()
#   012345
#
# acc(x) = acc[x] + acc[x-2]
#
# Either they may be nested
#
#     2 4  2 46 => don't forget to accumulate previous => 10
#     | |  | ||
#    ()()(()())
#    0123456789
#
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        res = 0
        acc = [0]*len(s)
        for i in range(1, len(s)):
            if s[i] == ')':
                if s[i-1] == '(':
                    acc[i] = 2 if i < 2 else acc[i-2] + 2
                else:
                    pos = i - acc[i-1] - 1
                    if pos >= 0 and s[pos] == '(':
                        acc[i] = acc[i-1] + 2
                        pos = i - acc[i]
                        if pos >= 0:
                            acc[i] += acc[pos]
            res = max(res, acc[i])
        return res
#
#data = [
#    "()()",
#    "((()))",
#    "(()))())("
#]
#
#for i in range(0, len(data)):
#    print(Solution().longestValidParentheses(data[i]))
