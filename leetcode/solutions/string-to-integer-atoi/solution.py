class Solution:
    def myAtoi(self, s: str) -> int:
        INT_MAX_ABS = 2147483647
        INT_MIN_ABS = 2147483648

        max_value = INT_MAX_ABS
        start = 0
        sign = 1
        res = 0

        for i in range(0, len(s)):
            if s[i] != ' ':
                start = i
                break
        else:
            return 0

        if s[start] == '-':
            max_value = INT_MIN_ABS
            sign = -1
            start += 1
        elif s[start] == '+':
            start += 1

        for i in range(start, len(s)):
            v = ord(s[i])
            if v < ord('0') or v > ord('9'):
                break
            v -= ord('0')
            res = res * 10 + v

            if res > max_value:
                return max_value * sign

        return res * sign

data = [
    "",                     # -> 0
    "42",                   # -> 42
    "   -42",               # -> -42
    "4193 with words",      # -> 4193
    "words and 987",        # -> 0
    "-91283472332",         # -> INT_MIN
]

for i in range(0, len(data)):
    print(Solution().myAtoi(data[i]))
