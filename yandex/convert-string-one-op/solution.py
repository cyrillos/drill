class Solution:
    #
    # Solved via min edit distance (known as Levenshtein)
    #
    # Another (more simple soltion) is to walk over both
    # strings and skip "one" mismatched character.

    def min_edit_distance(self, s: str, t: str) -> bool:
        a = [[0 for _ in range(0, len(s) + 1)] for _ in range(0, len(t)+1)]

        for i in range(1, len(s)+1):
            a[0][i] = i
        for i in range(1, len(t)+1):
            a[i][0] = i

        for i in range(0, len(s)):
            for j in range(0, len(t)):
                if s[i] == t[j]:
                    a[j+1][i+1] = a[j][i]
                else:
                    a[j+1][i+1] = min(a[j][i+1],a[j+1][i],a[j][i])+1

        return True if a[-1][-1] == 1 else False

    def skip_char(self, s: str, t: str) -> bool:
        diff = 0
        if len(s) != len(t):
            i, j = 0, 0
            while i < len(s) and j < len(t):
                if s[i] == t[j]:
                    i, j = i+1, j+1
                    continue
                diff += 1
                j += 1          # skip template letter
            while j < len(t):
                diff += 1
                j += 1          # appended words
        else:
            for i in range(0, len(s)):
                if s[i] != t[i]:
                    diff += 1
        return True if diff == 1 else False

    def IsConvertable(self, s: str, t: str) -> bool:
        return self.skip_char(s, t)

data = [
    ["ab",  "acb"],     # insertion: True
    ["ab",  "accb"],    # insertion: 2 times: False
    ["abc", "abc"],     # change: no change: False
    ["abc", "abd"],     # change: 1 change: True
    ["abc", "abcd"],    # insertion: True
    ["abc", "acd"],     # False
    ["ab",  "ba"],      # False
    ["abc", "ac"],      # True
    ["ac",  "bac"],     # True
    ["ac",  "acb"],     # True
]
for i in range(0, len(data)):
    print(data[i][0], data[i][1], "=>", Solution().IsConvertable(data[i][0], data[i][1]))
