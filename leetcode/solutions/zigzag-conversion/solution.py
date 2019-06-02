class Solution:
    def convert(self, s: str, n: int) -> str:
        if len(s) == 0: return ""
        if n < 2 or len(s) < n: return s

        res = [""] * len(s)
        d = n + (n - 2)
        p = 2
        pos = 0

        for i in range(0, n):
            for j in range(i, len(s), d):
                res[pos], pos = s[j], pos + 1
                if i > 0 and i < n-1:
                    if (j + d - p < len(s)):
                        res[pos], pos = s[j + d - p], pos + 1
            if i > 0 and i < n:
                p += 2
        return ''.join(res)

#data = [
#    ["PAYPALISHIRING", 1],
#    ["PAYPALISHIRING", 2],
#    ["PAYPALISHIRING", 3],
#    ["PAYPALISHIRING", 4],
#    ["PAYPALISHIRING", 5]
#]
#for i in range(0, len(data)):
#    print(Solution().convert(data[i][0], data[i][1]))
