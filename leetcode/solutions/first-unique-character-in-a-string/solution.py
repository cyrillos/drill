class Solution:
    def firstUniqChar(self, s: str) -> int:
        d = { }
        for i in range(0, len(s)):
            if not d.get(s[i]):
                d[s[i]] = [i, 1]
            else:
                d[s[i]][1] += 1
        pos = len(s)
        for k,v in d.items():
            if v[1] == 1:
                pos = min(pos, v[0])
        return pos if pos != len(s) else -1

data = [
    "leetcode",         # => 0
    "loveleetcode",     # => 2
]
for i in range(0, len(data)):
    print(Solution().firstUniqChar(data[i]))
