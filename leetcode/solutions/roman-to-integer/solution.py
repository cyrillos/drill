class Solution:
    def romanToInt(self, s: str) -> int:
        m = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000,
            'IV': 4,
            'IX': 9,
            'XL': 40,
            'XC': 90,
            'CD': 400,
            'CM': 900,
        }
        res, pos = 0, 0

        while pos < len(s):
            v = m.get(s[pos])
            if pos < len(s) - 1:
                t = m.get(s[pos:pos+2], 0)
                if t != 0:
                    v = t
                    pos += 1
            res += v
            pos += 1

        return res

data = [
    "III",          # -> 3
    "IV",           # -> 4
    "IX",           # -> 9
    "LVIII",        # -> 58
    "MCMXCIV",      # -> 1994
]
for i in range(0, len(data)):
    print(Solution().romanToInt(data[i]))
