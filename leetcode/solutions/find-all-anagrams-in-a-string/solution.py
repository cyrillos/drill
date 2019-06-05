class Solution:
    def findAnagrams(self, s: str, p: str) -> [int]:
        if len(s) < len(p): return []
        if len(s) == 0: return []
        if len(p) == 0: return []

        res = []

        cnt_p = [0] * 26
        cnt_s = [0] * 26

        def op(v):
            return ord(v) - ord('a')

        def same(a, b):
            for i in range(0, len(a)):
                if a[i] != b[i]: return False
            return True

        for i in range(0, len(p)):
            cnt_p[op(p[i])] += 1
            cnt_s[op(s[i])] += 1

        for i in range(0, len(s) - len(p)):
            if same(cnt_s, cnt_p): res.append(i)
            cnt_s[op(s[i])] -= 1
            cnt_s[op(s[i+len(p)])] += 1
        else:
            if same(cnt_s, cnt_p): res.append(len(s)-len(p))
        return res
#
#data = [
#    ["cbaebabacd", "abc"]
#]
#
#for i in range(0, len(data)):
#    print(data[i][0], data[i][1], Solution().findAnagrams(data[i][0], data[i][1]))
