class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        ds = {}
        dt = {}
        for i in range(0, len(s)):
            if s[i] not in ds:
                ds[s[i]] = t[i]
            if t[i] not in dt:
                dt[t[i]] = s[i]
            if ds[s[i]] != t[i] or dt[t[i]] != s[i]:
                return False
        return True

data = [
    ["egg", "add"],         # => true
    ["foo", "bar"],         # => false
    ["paper", "title"],     # => true
]
for i in range(0, len(data)):
    print(Solution().isIsomorphic(data[i][0], data[i][1]))
