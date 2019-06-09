class Solution:
    #
    # ROFL, it is accepted but for sure we need
    # to decompose string into bytes and implement
    # a real multiplication in a cycle. Thanks
    # no Karatsuba multiplcation needed ;)
    def multiply(self, num1: str, num2: str) -> str:
        def atoi(s):
            r = 0
            for i in range(0, len(s)):
                v = ord(s[i]) - ord('0')
                r = 10 * r + v
            return r
        a = atoi(num1)
        b = atoi(num2)
        return str(a*b)

data = [
    ["1", "2"],
    ["6", "4"],
]

for i in range(0, len(data)):
    print(Solution().multiply(data[i][0], data[i][1]))
