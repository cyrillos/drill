class Solution:
    def findAnagrams(self, s: str, p: str) -> [int]:
        if len(s) < len(p): return []
        if len(s) == 0: return []
        if len(p) == 0: return []

        res = []

        def op(v):
            return ord(v) - ord('a')

        hash_p = 0
        hash_s = 0

        for i in range(0, len(p)):
            hash_p |= (1 << op(p[i]))
            hash_s |= (1 << op(s[i]))

        for i in range(0, len(s) - len(p)):
            if hash_s == hash_p: res.append(i)
            hash_s &= ~(1 << op(s[i]))
            hash_s |=  (1 << op(s[i+len(p)]))
        else:
            if hash_s == hash_p: res.append(len(s)-len(p))
        return res

    def findAnagramsHashed(self, s: str, p: str) -> [int]:
        if len(s) < len(p): return []
        if len(s) == 0: return []
        if len(p) == 0: return []

        res = []

        def op(v):
            return ord(v) - ord('a')

        hash_p = 0
        hash_s = 0

        for i in range(0, len(p)):
            hash_p += (1 << op(p[i]))
            hash_s += (1 << op(s[i]))

        for i in range(0, len(s) - len(p)):
            if hash_s == hash_p: res.append(i)
            hash_s -=  (1 << op(s[i]))
            hash_s +=  (1 << op(s[i+len(p)]))
        else:
            if hash_s == hash_p: res.append(len(s)-len(p))
        return res
#
#data = [
#    ["cbaebabacd", "abc"]
#]
#
#for i in range(0, len(data)):
#    print(data[i][0], data[i][1], Solution().findAnagrams(data[i][0], data[i][1]))
